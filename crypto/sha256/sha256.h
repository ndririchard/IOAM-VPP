#ifndef SHA256_H
#define SHA256_H


#include <stddef.h>
#include <stdlib.h>
#include <memory.h>


#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 u8 digest

typedef struct {
	u8 data[64];
	u32 datalen;
	u32 bitlen;
	u32 state[8];
} SHA256_CTX;


void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const u8 data[], size_t len);
void sha256_final(SHA256_CTX *ctx, u8 hash[]);

#endif  