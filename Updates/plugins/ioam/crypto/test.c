#include "./crypto.h"
#include "./aes/aes.h"

int main(){
    __ioam_crypto_key_init__();
    u32 d = 3759450660;
    u8 *data = (u8*) &d;
    u32 dlen;
    u32 dilen;
    dlen = strlen((char*)data);
    u8 *digest = (u8*) malloc (sizeof(u8) * 1000);
    ioam_crypto_aes_cbc_encr(data, dlen, digest, dilen);
    printf("%lu\n", (u32*)digest);
    return 0;
}