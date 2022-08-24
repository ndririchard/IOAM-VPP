#ifndef AES256_H
#define AES256_H

#include <stdint.h>
#include <math.h>

typedef enum { false, true } bool;
typedef struct AES256_Word { u8 x[4]; } AES256_Word; //4 bytes
typedef struct AES256_State { AES256_Word x[4]; } AES256_State; //16 bytes

AES256_State IncState(AES256_State);

AES256_State AES256Encrypt(AES256_State, u8*);
AES256_State AES256Decrypt(AES256_State, u8*);
void AES256MainECB(u8*, u8*, u32, u8*, u32*, bool);
void AES256MainCBC(u8*, u8*, u8*, u32, u8*, u32*, bool);
void AES256MainCTR(u8*, u8*, u8*, u32, u8*, u32*, bool);
u8 * _Print_Word(AES256_Word);
u8 * _Print_State(AES256_State);
AES256_Word SubWord(AES256_Word, bool);
AES256_Word RotWord(AES256_Word, u8);
AES256_Word XorRcon(AES256_Word, u8);
AES256_Word XorWord(AES256_Word, AES256_Word);
void KeyExpansion(u8[], AES256_Word[]);
AES256_State AddRoundKey(AES256_State, AES256_Word*, u8);
AES256_State SubBytes(AES256_State, bool);
AES256_State ShiftRows(AES256_State);
AES256_Word InvMixColumn(AES256_Word);
AES256_Word MixColumn(AES256_Word);
AES256_State MixColumns(AES256_State, bool);
AES256_State InvShiftRows(AES256_State);
AES256_State XorState(AES256_State, AES256_State);

#endif