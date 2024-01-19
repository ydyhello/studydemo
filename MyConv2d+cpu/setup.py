from setuptools import setup
from torch.utils import cpp_extension
import os

src_root = 'panoflow/core/op/'
cpp_src = ['my_conv.cpp']

if __name__ == '__main__':
    include_dirs = ['panoflow/core/op/']
    cpp_path = [os.path.join(src_root, src) for src in cpp_src]

    setup(
        name='panoflow',
        ext_modules=[
            cpp_extension.CppExtension(
                'my_ops', cpp_path, include_dirs=include_dirs)
        ],
        cmdclass={'build_ext': cpp_extension.BuildExtension})