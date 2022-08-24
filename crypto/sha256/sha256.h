#ifndef SHA256_H
#define SHA256_H

#include "../src/vppinfra"
#define SHA256_BLOCK_SIZE 32

typedef struct{
    u8 data[64];
    u32 datalen;
    u32 bitlen;
    u32 state[8];
} SHA256_CTX;

void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, u8 data[], u32 len);
void sha256_final(SHA256_CTX *ctx, u8 hash[]);


#endif