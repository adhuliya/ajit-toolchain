#ifndef AES_UTILS_H
#define AES_UTILS_H

#include <stdint.h>

#define STATE_ROWS 4
#define STATE_COLS 4

extern const uint8_t sbox[16][16];
extern const uint32_t RCon[10];
extern const uint8_t inverse_sbox[16][16];
uint32_t RotWord(uint32_t word);
uint32_t SubRows(uint32_t word);
uint32_t TempWord(uint32_t word, int round_number);
void MurmurHash3_x64_128(const void *key, const int len, const uint32_t seed, uint64_t *out);
void AddRoundKey(uint64_t rk_msb, uint64_t rk_lsb, uint8_t state_matrix[STATE_ROWS][STATE_COLS], uint8_t transform_matrix[STATE_ROWS][STATE_COLS]);
void SubBytes(uint8_t state_matrix[STATE_ROWS][STATE_COLS], uint8_t transform_matrix[STATE_ROWS][STATE_COLS]);
void InverseSubBytes(uint8_t state_matrix[STATE_ROWS][STATE_COLS], uint8_t transform_matrix[STATE_ROWS][STATE_COLS]);
void ShiftRows(uint8_t matrix[STATE_ROWS][STATE_COLS]);
void InverseShiftRows(uint8_t matrix[STATE_ROWS][STATE_COLS]);
void MixColumns(uint8_t state[STATE_ROWS][STATE_COLS]);
void InverseMixColumns(uint8_t state[STATE_ROWS][STATE_COLS]);
#endif
