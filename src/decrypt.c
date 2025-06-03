#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "sha256.h"

#define SHA256_BLOCK_SIZE 32

int base64index(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

unsigned char* base64decode(const char* input, int* out_len) {
    size_t len = strlen(input);
    size_t out_size = len * 3 / 4;
    unsigned char* out = malloc(out_size);
    int val = 0, valb = -8;
    int i = 0;

    for (size_t j = 0; j < len; j++) {
        int idx = base64index(input[j]);
        if (idx == -1) continue;
        val = (val << 6) + idx;
        valb += 6;
        if (valb >= 0) {
            out[i++] = (val >> valb) & 0xFF;
            valb -= 8;
        }
    }
    *out_len = i;
    return out;
}

char* decrypt(const char* encoded, const char* key) {
    uint8_t stratchedKey[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(&ctx, (const BYTE*)key, strlen(key));
    sha256_final(&ctx, stratchedKey);

    int length;
    unsigned char* encrypted = base64decode(encoded, &length);
    if (!encrypted) return NULL;

    char* decrypted = malloc(length + 1);
    if (!decrypted) {
        free(encrypted);
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        decrypted[i] = encrypted[i] ^ stratchedKey[i % SHA256_BLOCK_SIZE];
    }
    decrypted[length] = '\0';

    free(encrypted);
    return decrypted;
}

void xorDecrypt(char* str, int len, char key) {
    for (int i = 0; i < len; i++) {
        str[i] ^= key;
    }
}