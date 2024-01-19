import torch
import torch.nn as nn
from panoflow.core.op.my_conv import MyConv2d

inc = 3
outc = 4
img_shaspe = (50, 50)

# device_name = 'cuda:0'
device_name = 'cpu'
open_bias = True


def test_one():
    ts = torch.ones([1, 1, 3, 3]).to(device_name)
    layer = nn.Conv2d(1, 1, 3, 1, 1, bias=open_bias).to(device_name)
    gt = layer(ts)
    my_layer = MyConv2d(1, 1, 3, 1, 1).to(device_name)
    my_layer.load_state_dict(layer.state_dict(), strict=False)
    res = my_layer(ts)
    res = res.to('cpu')
    gt = gt.to('cpu')
    assert torch.allclose(res, gt, 1e-3, 1e-5)


def test_two():
    ts = torch.rand([1, inc, *img_shaspe]).to(device_name)
    layer = nn.Conv2d(inc, outc, 3, 1, 1, bias=open_bias).to(device_name)
    gt = layer(ts)
    my_layer = MyConv2d(inc, outc, 3, 1, 1).to(device_name)
    my_layer.load_state_dict(layer.state_dict(), strict=False)
    res = my_layer(ts)
    res = res.to('cpu')
    gt = gt.to('cpu')
    assert torch.allclose(res, gt, 1e-3, 1e-5)


if __name__ == '__main__':
    test_one()
    test_two()