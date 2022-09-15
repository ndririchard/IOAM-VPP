#include "ioam_trace_integrity_protected.h"

char data[][10]= {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
    "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
    "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" 
};


int lenHelper(unsigned x) {
    if (x >= 10000000000) return 11;
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}

void ioam_trace_integrity_protected_create_pk(ioam_trace_integrity_hdr_t *hdr){
    u8 d = (u8) hdr->nonce;
    clib_sha256(&d, strlen(d), &public_key);
}

u8 ioam_trace_integrity_find_pk(ioam_trace_integrity_hdr_t *hdr){
    if (public_key == NULL)
        ioam_trace_integrity_protected_create_pk(hdr);
    return public_key;
}

void ioam_trace_integrity_create_iv(){
    time_t t;
    char *v = malloc(sizeof(char) * 32);
    srand((unsigned) time(&t));
    for (int i=0; i<32; i++){
        int index = rand() % 58;
        strcpy(&v[i], data[index]);
    }
    iv = (u8) *v;
}

u8 ioam_trace_integrity_find_iv(){
    if (iv == NULL)
        ioam_trace_integrity_create_iv(hdr);
    return iv;
}

void ioam_trace_integrity_set_ss(ioam_trace_integrity_hdr_t *hdr){
    // In a first time, i deal only with symetric encryption
    hdr->ss = 0x01;
}

void ioam_trace_integrity_set_nonce(ioam_trace_integrity_hdr_t *hdr){
    time_t t;
    srand((unsigned) &t);
    u32 nn = (rand() + 1) * (rand() + 1); 
    hdr->nonce = nn;
    hdr->nn_len = (u8) lenHelper(nn);
}

void ioam_trace_integrity_AES256_handler(ioam_trace_integrity_hdr_t *hdr, u32 d, u32 rb, u32 rl){
    u8 pk = ioam_trace_integrity_find_pk(hdr);
    u8 iv = ioam_trace_integrity_find_iv();

    parse_02X(key_vect, key, 32);
    parse_02X(iv_vect, iv, 16);

    u32 returnlen = 0;
    u8 *byteBuffer = (u8*) malloc( (u32) strlen(data) );
    u8 *returnBuffer = (u8*) malloc( (u32) strlen(data) );

    u8 data = (u8) d;
    u8 hash_d;
    clib_sha256(&data, strlen(data), &hash_d);
    str_to_bytes(hash_d, byteBuffer);
    AES256_ENC_ALGO(&pk, byteBuffer, &iv, strlen(hash_d), returnBuffer, &returnlen, true);

    rb = (u32) *returnBuffer;
    rl = returnlen;
}

void ioam_trace_integrity_get_node_data(u32 node_type, ioam_trace_hdr_t *hdr,u32 pos, trace_profile *profile, u32 *returnAddr){
    int start = pos * (fetch_trace_data_size(profile)/4);
    int end = start + fetch_trace_data_size(profile)/4;
    if(node_type == IOAM_ENCAP_NODE){
        *returnAddr = hdr->integrity_hdr.nonce + (u32) nn_len;
    }
    for (int i=start; i<end; i++){
        *returnAddr += hdr->app_data[i];
    }
}

int ioam_trace_check_integrity_protection(ioam_trace_hdr_t *hdr, trace_profile * profile){
    int nb_of_node = profile->num_elts;
    for (int i=0; i<nb_of_node-1; i++){
        u32* data;
        u32* signa;
        u32 sl;
        if (i == 0){
            // check integrity of the encap node
            ioam_trace_integrity_get_node_data(IOAM_ENCAP_NODE, hdr, i; profile, data);
            ioam_trace_integrity_AES256_handler(&(hdr->integrity_dr), *data, *signa, sl);
        }
        else {
            ioam_trace_integrity_get_node_data(IOAM_TRANSIT_NODE, hdr, i; profile, data);
            ioam_trace_integrity_AES256_handler(&(hdr->integrity_dr), *data, *signa, sl);
        }
        if (signa != hdr->integrity_hdr.signature[i])
            return (-1);
        
    }
    return 0;
}







