# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup
from glob import glob

__version__ = "0.0.1"

ext_modules = [
    Pybind11Extension(
        "Kobuki",
        sorted(glob("src/**/*.cpp", recursive=True)),
        # Example: passing in the version to the compiled code
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

setup(
    name="Kobuki",
    version=__version__,
    author="Danil Zlobin",
    author_email="xzlobin@stuba.sk",
    url="~",
    description="Kobuki robot python module",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
)
