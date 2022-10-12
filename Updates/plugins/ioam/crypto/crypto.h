#ifndef __IOAM_CRYPTO_H__
#define __IOAM_CRYPTO_H__

#include "crypto_util.h"

#define IV_SIZE 16
#define AES256_KEY_SIZE 32

typedef struct ioam_crypto_ecdsa_key_{
    u8 *pk; // public key
    u8 *sK; // secrete key
} ioam_crypto_ecdsa_key_t;

typedef struct ioam_crypto_main_{
    u8 *iv;
    u8 *aesk;
    char *aeskString;
    char *ivString;
    ioam_crypto_ecdsa_key_t ecdsa_keys[0];
} ioam_crypto_main_t;

extern ioam_crypto_main_t ioam_crypto_main; // define it as a global variable
ioam_crypto_main_t ioam_crypto_main;

void __ioam_crypto_key_init__(){
    ioam_crypto_main.aeskString = generateWord(AES256_KEY_SIZE);
    ioam_crypto_main.ivString = generateWord(IV_SIZE);
    parse_02X(key, ioam_crypto_main.aeskString, AES256_KEY_SIZE);
    parse_02X(iv, ioam_crypto_main.ivString, IV_SIZE);
    ioam_crypto_main.aesk = key;
    ioam_crypto_main.iv = iv;
}
#endif