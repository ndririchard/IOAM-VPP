#ifndef TRACE_INTEGRITY_H
#define TRACE_INTEGRITY_H

// add vpp library
#include "../src/vlib"
#include "../aes256/eas256.h"
#include "../sha256/sha256.h"
#include "../keys/Keys.h"
#include "../crypto/utility/convert.h"

typedef struct {
    char* eas256_pk;
    char* ecdsap256_pk;
    char* ecdsap256_sk;
    long encr_type;
} trace_integrity_main_;

extern trace_integrity_main_ trace_integrity_main_t;
static clib_error_t * initTraceIntegrity(void);
char* hashing(char* data);
char* signature(char* hash, char* prev_sign);
static clib_error_t * verify();


#endif