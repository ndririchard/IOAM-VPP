#include "crypto.h"

void AES256_ENC(u32* word, u32* buffer){
    uint32_t returnlen = 0;
    char* bitbuf = malloc( sizeof(char) * 100000);
    char* buf = malloc( sizeof(char) * 100000);
    char * wrd = (char*) word;
    char* key = findAES256Key();
    char* iv = generateNonce();
    parse_02X("key", key, 32);
    parse_02X("iv", iv, 16);
    str_to_bytes(wrd, bitbuf);
    ES256MainCBC(key, bitbuf, iv, strlen(wrd), buf, &returnlen, true);
    buffer = (u32*) buf;
}