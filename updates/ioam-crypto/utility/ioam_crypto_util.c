#include "ioam_crypto_util.h"

static char* nonce;
static char* key;

uint8_t key[32] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

uint8_t iv[16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
};

char data[][10]= {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
    "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
    "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" 
};

void generateWord(char* wrd, int len){
    time_t t;
    wrd = malloc(sizeof(char) * len);
    srand((unsigned) time(&t));
    for (int i=0; i<len; i++){
        int index = rand() % 58;
        strcpy(&wrd[i], data[index]);
    }
}

char* findAES256Key(){
    if (key == NULL)
        generateWord(key, EAS256_KEY_SIZE);
    return key;
}

char* generateNonce(){
    if (nonce == NULL){
        generateWord(nonce, Nonce_LENGTH);
    }
    return nonce;
}

void str_to_bytes(char *str, uint8_t *bytes){
  int str_len = strlen(str);
  int i;
  for(i = 0; i < str_len; i++){
    bytes[i] = str[i];
  }
}

char* bytes_to_hexstr(uint8_t *bytes, uint32_t length){
  static char buffer[(uint32_t) MAX_MSG_LGTH * 2];
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
  static char buffer[(uint32_t) MAX_MSG_LGTH];
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

void parse_02X(const char key, char *arg, int bytes){
  char* key;
  if (strcmp(key, "key") == 0) 
    key = key;
  else if (strcmp(key, "iv") == 0) 
    key = iv;
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