#ifndef IOAM_TRACE_INTEGRITY_PROTECTED_H
#define IOAM_TRACE_INTEGRITY_PROTECTED_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vlib/sh2.h>
#include <trace_util.h>
#include <aes256.h>

typedef struct {
    u8 ss;
    u8 nn_len;
    u32 nonce;
    u32 sign_data[0];
} ioam_trace_integrity_hdr_t;

int lenHelper(unsigned x);
void ioam_trace_integrity_create_iv();
u8 ioam_trace_integrity_find_iv();
void ioam_trace_integrity_protected_create_pk(ioam_trace_integrity_hdr_t *hdr);
u8 ioam_trace_integrity_find_pk(ioam_trace_integrity_hdr_t *hdr);
void ioam_trace_integrity_set_ss(ioam_trace_integrity_hdr_t *hdr);
void ioam_trace_integrity_set_nonce(ioam_trace_integrity_hdr_t *hdr);
void ioam_trace_integrity_AES256_handler(ioam_trace_integrity_hdr_t *hdr, u32 d, u32 rb, u32 rl);



#endif