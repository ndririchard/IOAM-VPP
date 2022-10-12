#ifndef __IOAM_CRYPTO_AES_H__
#define __IOAM_CRYPTO_AES_H__


#include "aes_ops.h"
#include "../crypto.h"

#define IOAM_CRYPTO_AES_ECB 1
#define IOAM_CRYPTO_AES_CBC 2
#define IOAM_CRYPTO_AES_CTR 3

int ioam_crypto_aes_encrypt_(int mode, u8 *data, u32 len, u8 *digest, u32 dlen){
    u8 *buffer = (u8*) malloc( sizeof(u8) * len);
    if (buffer == NULL)
        return (-1);
    str_to_bytes((char*)data, buffer);
    if (mode == IOAM_CRYPTO_AES_ECB)
        AES256MainECB(ioam_crypto_main.aesk, buffer, len, digest, &dlen, true);
    else if (mode == IOAM_CRYPTO_AES_CBC)
        AES256MainCBC(ioam_crypto_main.aesk, buffer, ioam_crypto_main.iv, len, digest, &dlen, true);
    else if (mode == IOAM_CRYPTO_AES_CTR)
        AES256MainCTR(ioam_crypto_main.aesk, buffer, ioam_crypto_main.iv, len, digest, &dlen, true);
    return 0;
}

int ioam_crypto_aes_decrypt_(int mode, u8 *data, u32 len, u8 *digest, u32 dlen){
    u8 *buffer = (u8*) malloc( sizeof(u8) * dlen);
    if (buffer == NULL)
        return (-1);
    str_to_bytes((char*)digest, buffer);
    if (mode == IOAM_CRYPTO_AES_ECB)
        AES256MainECB(ioam_crypto_main.aesk, buffer, dlen, digest, &len, true);
    else if (mode == IOAM_CRYPTO_AES_CBC)
        AES256MainCBC(ioam_crypto_main.aesk, buffer, ioam_crypto_main.iv, dlen, digest, &len, true);
    else if (mode == IOAM_CRYPTO_AES_CTR)
        AES256MainCTR(ioam_crypto_main.aesk, buffer, ioam_crypto_main.iv, dlen, digest, &len, true);
    return 0;
}


#define ioam_crypto_aes_ecb_encr(...) ioam_crypto_aes_encrypt_(IOAM_CRYPTO_AES_ECB, __VA_ARGS__)
#define ioam_crypto_aes_cbc_encr(...) ioam_crypto_aes_encrypt_(IOAM_CRYPTO_AES_CBC, __VA_ARGS__)
#define ioam_crypto_aes_ctr_encr(...) ioam_crypto_aes_encrypt_(IOAM_CRYPTO_AES_CTR, __VA_ARGS__)

#define ioam_crypto_aes_ecb_decr(...) ioam_crypto_aes_decrypt_(IOAM_CRYPTO_AES_ECB, __VA_ARGS__)
#define ioam_crypto_aes_cbc_decr(...) ioam_crypto_aes_decrypt_(IOAM_CRYPTO_AES_CBC, __VA_ARGS__)
#define ioam_crypto_aes_ctr_decr(...) ioam_crypto_aes_decrypt_(IOAM_CRYPTO_AES_CTR, __VA_ARGS__)

#endif