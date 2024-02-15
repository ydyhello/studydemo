from setuptools import setup
from torch.utils import cpp_extension
import os

src_root = 'panoflow_cuda/core/op/'
cpp_src = ['my_conv.cpp', 'my_conv_cuda.cu']

if __name__ == '__main__':
    include_dirs = ['panoflow_cuda/core/op/']
    cpp_path = [os.path.join(src_root, src) for src in cpp_src]

    setup(
        name='panoflow_cuda',
        ext_modules=[
            cpp_extension.CUDAExtension(
                'my_ops', cpp_path, include_dirs=include_dirs)
        ],
        cmdclass={'build_ext': cpp_extension.BuildExtension})