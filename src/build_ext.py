import shutil
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

encrypt = lambda plaintext, key : [ord(c) ^ key for c in plaintext]

def xorEncrypt(encrypted, length, key):
    array = ", ".join(f"0x{b:02X}" for b in encrypted)
    return f"char key[] = {{{array}, 0x00}};\n    xorDecrypt(key, {length}, 0x{key:02X});"

class CustomBuildExt(build_ext):
    user_options = build_ext.user_options + [
        ("key=", None, "Encryption key"),
        ("kek=", None, "Key encryption key")
    ]

    def initialize_options(self):
        super().initialize_options()
        self.key = None
        self.kek = None

    def finalize_options(self):
        super().finalize_options()
        if self.key is None or self.kek is None:
            raise RuntimeError('Usage: python setup.py build_ext --key="Hello World!" --kek=0x22')
        try:
            self.kek = int(self.kek, 0)
        except ValueError:
            raise RuntimeError("[error] Invalid kek value")

    def run(self):
        shutil.copyfile("main.c", "main.c.bak")

        encrypted = encrypt(self.key, self.kek)
        patched = xorEncrypt(encrypted, len(self.key), self.kek)

        with open("main.c", "r", encoding="utf-8") as f:
            content = f.read()

        placeholder = 'char* key = "Hello World!";'
        if placeholder not in content:
            raise RuntimeError(f"[error] Placeholder not found. {placeholder}")

        content = content.replace(placeholder, patched)

        with open("main.c", "w", encoding="utf-8") as f:
            f.write(content)

        super().run()

        shutil.move("main.c.bak", "main.c")

module = Extension(
    "ATFieldDRM",
    sources=["main.c", "decrypt.c", "sha256.c"]
)

setup(
    name="ATFieldDRM",
    version="9.9.0",
    ext_modules=[module],
    cmdclass={
        "build_ext": CustomBuildExt,
    }
)