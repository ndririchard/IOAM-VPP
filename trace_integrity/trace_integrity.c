#include "trace_integrity.h"


u8* __generateNonce__(void){

}

u8* __genarateEASKey__(void){
    u8 key[64];

    return key;
}

void __initAES__(void){
    eas256_pk = __genarateEASKey__();
}

void __initECDSAP__(void){
    // initilize the keys
}

static clib_error_t * __initIntegrityProtection__(void){
    if ( ioam_trace_hdr_t->signature_suite == 0x01 )
        encr_type = 1;
    else if ( ioam_trace_hdr_t->signature_suite == 0x02 )
        encr_type = 2;
    
    else

}