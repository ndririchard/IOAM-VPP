#include <string.h>
#include <stdio.h>

#define EAS256_KEY_SIZE 64

const char data[58] = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
    "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
    "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" 
};

char* generatEAS256Keys(){
    char *key;
    time_t t;
    key = malloc(sizeof(char) * EAS256_KEY_SIZE);
    srand((unsigned) time(&t));
    for (int i=0; i<EAS256_KEY_SIZE; i++){
        int index = rand() % 58;
        strcpy(key[i], data[index]);
    }
    return key;
}