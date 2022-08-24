#ifndef TRACE_INTEGRITY_H
#define TRACE_INTEGRITY_H

#include "./lib-trace/trace_util.h"
#include "./crypto/sha256/sha256.h"
#include "./crypto/eas256/eas256.h"

typedef struct{
    u8 *eas256_pk;
    u8 *ecdsap256_pk;
    u8 *ecdsap256_sk;
    u32 encr_type = -1;
} trace_integrity_main;

u8* __generateNonce__(void);
u8* __genarateEASKey__(void);

void __initAES__(void);
void __initECDSAP__(void);
static clib_error_t * __initIntegrityProtection__(void);
void __resetParameters__(void);

u8* integrityHashFucntion(u8* data);
u8* integrityEASFunction(u8* hash, u8* prev_sign);

void integrityMainProcess(void);



#endif

