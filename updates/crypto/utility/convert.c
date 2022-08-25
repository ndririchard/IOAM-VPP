#include "convert.h"

void str_to_bytes(char *str, uint8_t *bytes){
  int str_len = strlen(str);
  int i;
  for(i = 0; i < str_len; i++){
    bytes[i] = str[i];
  }
}

char* bytes_to_hexstr(uint8_t *bytes, uint32_t length){
  static char buffer[(uint32_t)MAX_MSG_LGTH * 2];
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

char* bytes_to_str(uint8_t *bytes, uint32_t length){
  static char buffer[(uint32_t)MAX_MSG_LGTH];
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

void parse_02X(uint8_t *key, char *arg, int bytes){
  int iter;
  for(iter = 0; iter < bytes; iter ++){
    uint8_t tempbit;
    char temp[2] = "";
    temp[0] = (char*)arg[iter*2];
    temp[1] = (char*)arg[iter*2+1];
    sscanf(temp, "%02hhX", &tempbit);
    key[iter] = tempbit;
  }
}