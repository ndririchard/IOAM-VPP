#ifndef CONVERT_H
#define CONVERT_H

#include <stdio.h>
#include <unistd.h>
#include "aes256.h"

#define MAX_MSG_LGTH 10000

void str_to_bytes(char *str, uint8_t *bytes);
char* bytes_to_hexstr(uint8_t *bytes, uint32_t length);
char* bytes_to_str(uint8_t *bytes, uint32_t length);
void parse_02X(uint8_t *key, char *arg, int bytes);

#endif