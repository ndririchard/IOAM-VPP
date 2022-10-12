#ifndef __IOAM_CRYPTO_CRYPTOUTIL_H__
#define __IOAM_CRYPTO_CRYPTOUTIL_H__

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char u8;
typedef unsigned int u32;

#define MAX_BUFFER_SIZE 1024

u8 key[32] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

u8 iv[16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};

char data[62] = {
    'l', 'm', 'n', 'o', 'A', 'B','w', 'x', 'y', 'z', '0', '1', 
    '2', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'Q', 'R', 'S', 'T', 'U', 'V', 'p', 'q', 'r', 's', 't',  
    'N', 'O', 'P',  'W', 'X', '3', '4', '5', '6', '7', 'u', 'v', 
    '8', '9' 
};

char* generateWord(size_t len)
{
    time_t t;
    srand( (unsigned) time(&t));
    char * wrd = (char*) malloc( sizeof(char) * len);
    for (int i=0; i<len; i++){
        int index = rand() % 62;
        sprintf(&wrd[i], "%c", data[index]);
    }
    return wrd;
}

void str_to_bytes(char *str, u8 *bytes){
  int str_len = strlen(str);
  int i;
  for(i = 0; i < str_len; i++){
    bytes[i] = str[i];
  }
}

char* bytes_to_hexstr(u8 *bytes, u32 length){
  static char buffer[ (u32) MAX_BUFFER_SIZE * 2];
  memset(buffer, 0, strlen(buffer));
  int i;
  for(i = 0; i < length; i++){
    sprintf(buffer + strlen(buffer), "%02x", bytes[i]);
    if((i + 1) % 16 == 0){
      sprintf(buffer + strlen(buffer),"\n");
    }
  }
  if(length % 16 != 0)
    sprintf(buffer + strlen(buffer),"\n");
  return buffer;
}

char* bytes_to_str(u8 *bytes, u32 length){
  static char buffer[ (u32) MAX_BUFFER_SIZE];
  memset(buffer, 0, strlen(buffer));
  int i;
  for(i = 0; i < length; i++){
    if(bytes[i] == 0 || 32 <= bytes[i] && bytes[i] <= 126)
      sprintf(buffer + strlen(buffer), "%c", bytes[i]);
    else
      sprintf(buffer + strlen(buffer), "%c", '_');
  }
  return buffer;
}

void parse_02X(u8 *key, char *arg, int bytes){
  int iter;
  for(iter = 0; iter < bytes; iter ++){
    u8 tempbit;
    char temp[2] = "";
    temp[0] = arg[iter*2];
    temp[1] = arg[iter*2+1];
    sscanf(temp, "%02hhX", &tempbit);
    key[iter] = tempbit;
  }
}
#endif