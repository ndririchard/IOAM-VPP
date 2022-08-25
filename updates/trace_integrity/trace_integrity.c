#include "trace_integrity.h"

trace_integrity_main_ trace_integrity_main_t;

static clib_error_t * initTraceIntegrity(void){
    if ( ioam_trace_hdr_t->signature_suite == 0x01)
        trace_integrity_main_t->encr_type = 1;

    else if ( ioam_trace_hdr_t->signature_suite == 0x02)
        trace_integrity_main_t->encr_type = 2; 
    
    switch (trace_integrity_main_t->encr_type)
    {
    case 1:
        trace_integrity_main_t->eas256_pk = generatEAS256Keys();
        break;
    
    case 2:
        // to implement
        break;
    }
    return 0;
}

char* hashing(char* data){
    char buffer[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(&ctx, data, strlen(data));
    sha256_final(&ctx, buffer);

    return buffer;
}

uint8_t* signature(char* hash, char* prev_sign){
    uint32_t returnlen = 0;
    uint8_t *byteBuffer = (uint8_t*)malloc((uint32_t)MAX_MSG_LGTH);
    uint8_t *returnBuffer = (uint8_t*)malloc((uint32_t)MAX_MSG_LGTH);

    char* msg = strcat(hash, prev_sign);
    str_to_bytes(msg, byteBuffer);
    AES256MainECB(key, byteBuffer, strlen(message), returnBuffer, &returnlen, true);

    return returnBuffer;
}

