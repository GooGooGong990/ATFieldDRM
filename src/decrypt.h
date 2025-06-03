#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#define SHA256_BLOCK_SIZE 32

#ifdef __cplusplus
extern "C" {
#endif

char* decrypt(const char* encoded, const char* key);

void xorDecrypt(char* str, int len, char key);

#ifdef __cplusplus
}
#endif

#endif