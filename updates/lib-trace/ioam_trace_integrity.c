#include "ioam_trace_integrity.h"

int findFreeIndex(u32* list){
    int res = MAX_NODE;
    for (int i=0; i<MAX_NODE; i++){
        if (list[i] == NULL)
            res = i;
    }
    return res;
}

void checkForInterity(ioam_trace_option_t *hdr, int* rv){
    for (int i=0; i<MAX_NODE; i++){
        u32* buf = malloc (10000);
        u32 data = hdr->integrity_hdr->cp_data[i];
        if (i == 0){
            // encap node
            AES256_ENC(data, buf);
            if (buf != hdr->integrity_hdr->signature[i])
                rv = (-1);
        }
        else{
            u32 wrd = data + hdr->integrity_hdr->signature[i-1];
            AES256_ENC(wrd, buf);
            if (buf != hdr->integrity_hdr->signature[i])
                rv = (-1);
        }
    }
}