#ifndef CRYPTO_H
#define CRYPTO_H

#include "./aes256/aes256.h"
#include "./utility/ioam_crypto_util.h"

void AES256_ENC(u32* word, u32* buffer);

#endif