import sys
import base64
import hashlib

KEY = "Hello World!"

def encrypt(plaintext, key):
    stretchedKey = hashlib.sha256(key.encode()).digest()
    return base64.b64encode(bytes([b ^ stretchedKey[i % len(stretchedKey)] for i, b in enumerate(plaintext.encode())])).decode()

filename = sys.argv[1]

with open(filename, "r", encoding="utf-8") as f:
    content = f.read()

with open(filename[:-3]+"-obfuscated.py", "w", encoding="utf-8") as f:
    code = f"""import ATFieldDRM\nATFieldDRM.run("{encrypt(content, KEY)}")"""

    f.write(code)