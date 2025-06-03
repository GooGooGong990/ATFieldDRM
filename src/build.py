from setuptools import setup, Extension

module = Extension(
    "ATFieldDRM",
    sources=["main.c", "decrypt.c", "sha256.c"]
)

setup(
    name="ATFieldDRM",
    version="9.9.0",
    ext_modules=[module]
)