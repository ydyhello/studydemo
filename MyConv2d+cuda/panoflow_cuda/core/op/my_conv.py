import torch
from torch.autograd import Function
import torch.nn as nn
from torch import Tensor
from torch.nn.modules.utils import _pair
from torch.nn.parameter import Parameter

import my_ops


class MyConvF(Function):


    def forward(ctx,
                input: torch.Tensor,
                weight,
                bias,
                stride=1,
                padding=0,
                dilation=1,
                groups=1,
                im2col_step=32):
        if input is not None and input.dim() != 4:
            raise ValueError(
                f'Expected 4D tensor as input, got {input.dim()}D tensor \
                  instead.')
        ctx.stride = _pair(stride)
        ctx.padding = _pair(padding)
        ctx.dilation = _pair(dilation)
        ctx.groups = groups
        ctx.im2col_step = im2col_step

        weight = weight.type_as(input)
        ctx.save_for_backward(input, weight)

        output = input.new_empty(MyConvF._output_size(ctx, input, weight))

        ctx.bufs_ = [input.new_empty(0), input.new_empty(0)]  # columns, ones

        cur_im2col_step = min(ctx.im2col_step, input.size(0))
        assert (input.size(0) % cur_im2col_step
                ) == 0, 'batch size must be divisible by im2col_step'

        my_ops.my_conv_forward(
            input,
            weight,
            bias,
            output,
            ctx.bufs_[0],
            kW=weight.size(3),
            kH=weight.size(2),
            dW=ctx.stride[1],
            dH=ctx.stride[0],
            padW=ctx.padding[1],
            padH=ctx.padding[0],
            dilationW=ctx.dilation[1],
            dilationH=ctx.dilation[0],
            group=ctx.groups,
            im2col_step=cur_im2col_step)
        return output


    def _output_size(ctx, input, weight):
        channels = weight.size(0)
        output_size = (input.size(0), channels)
        for d in range(input.dim() - 2):
            in_size = input.size(d + 2)
            pad = ctx.padding[d]
            kernel = ctx.dilation[d] * (weight.size(d + 2) - 1) + 1
            stride_ = ctx.stride[d]
            output_size += ((in_size + (2 * pad) - kernel) // stride_ + 1, )
        if not all(map(lambda s: s > 0, output_size)):
            raise ValueError(
                'convolution input is too small (output would be ' +
                'x'.join(map(str, output_size)) + ')')
        return output_size


my_conv = MyConvF.apply


class MyConv2d(nn.Module):

    def __init__(self,
                 in_channels: int,
                 out_channels: int,
                 kernel_size,
                 stride=1,
                 padding=0,
                 dilation=1,
                 groups: int = 1,
                 bias: bool = True):
        super().__init__()
        kernel_size_ = _pair(kernel_size)
        stride_ = _pair(stride)
        padding_ = _pair(padding)
        dilation_ = _pair(dilation)
        self.in_channels = in_channels
        self.out_channels = out_channels
        self.kernel_size = kernel_size_
        self.stride = stride_
        self.padding = padding_
        self.dilation = dilation_
        self.groups = groups
        self.weight = Parameter(
            torch.Tensor(out_channels, in_channels // groups, *kernel_size_))
        self.bias = Parameter(torch.Tensor(out_channels))

        # Useless attributes
        self.transposed = None
        self.output_padding = None
        self.padding_mode = None

    def forward(self, input: Tensor) -> Tensor:
        return my_conv(input, self.weight, self.bias, self.stride,
                       self.padding, self.dilation, self.groups)