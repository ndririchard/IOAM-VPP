#ifndef IOAM_CRYPTO_UTIL_H
#define IOAM_CRYPTO_UTIL_H

#include "./aes256/aes256.h"

#define Nonce_LENGTH 16
#define EAS256_KEY_SIZE 64

void generateWord(char* wrd, int len);
char* findAES256Key();
char* generateNonce();
void str_to_bytes(char *str, uint8_t *bytes);
char* bytes_to_hexstr(uint8_t *bytes, uint32_t length);
char* bytes_to_str(uint8_t *bytes, uint32_t length);
void parse_02X(const char key, char *arg, int bytes);

#endif