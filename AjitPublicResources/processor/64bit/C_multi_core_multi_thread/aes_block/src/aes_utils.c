#include "aes_utils.h"

const uint32_t RCon[10] = {
    0x01000000, // Round 1
    0x02000000, // Round 2
    0x04000000, // Round 3
    0x08000000, // Round 4
    0x10000000, // Round 5
    0x20000000, // Round 6
    0x40000000, // Round 7
    0x80000000, // Round 8
    0x1B000000, // Round 9
    0x36000000  // Round 10
};

const uint8_t sbox[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}
};

const uint8_t inverse_sbox[16][16] = {
    {0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},
    {0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},
    {0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},
    {0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},
    {0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},
    {0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},
    {0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},
    {0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},
    {0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},
    {0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},
    {0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},
    {0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},
    {0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},
    {0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},
    {0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}
};


uint32_t RotWord(uint32_t word) {
    int shift = 8;
    return (word << shift) | (word >> (32 - shift));
}

uint32_t SubRows(uint32_t word) {
    uint8_t RowElements[4];
    uint8_t SubByteRes[4];

    // Split the 32-bit word into 4 bytes
    RowElements[0] = (word >> 24) & 0xFF; // Most significant 8 bits
    RowElements[1] = (word >> 16) & 0xFF;
    RowElements[2] = (word >> 8) & 0xFF;
    RowElements[3] = word & 0xFF;         // Least significant 8 bits

    // Apply the S-box substitution for each byte
    SubByteRes[0] = sbox[(RowElements[0] >> 4) & 0x0F][RowElements[0] & 0x0F];
    SubByteRes[1] = sbox[(RowElements[1] >> 4) & 0x0F][RowElements[1] & 0x0F];
    SubByteRes[2] = sbox[(RowElements[2] >> 4) & 0x0F][RowElements[2] & 0x0F];
    SubByteRes[3] = sbox[(RowElements[3] >> 4) & 0x0F][RowElements[3] & 0x0F];

    // Combine the substituted bytes back into a single 32-bit word
    uint32_t result = (SubByteRes[0] << 24) | (SubByteRes[1] << 16) |
                      (SubByteRes[2] << 8) | SubByteRes[3];

    return result;
    
}

uint32_t TempWord(uint32_t word, int round_number){
    uint32_t temp = 0;
    temp = RotWord(word);
    temp = SubRows(temp);
    temp = temp ^ RCon[round_number-1];
    return temp;
} 

void MurmurHash3_x64_128(const void *key, const int len, const uint32_t seed, uint64_t *out) {
    const uint8_t *data = (const uint8_t *)key;
    const int nblocks = len / 16;

    uint64_t h1 = seed;
    uint64_t h2 = seed;

    const uint64_t c1 = 0x87c37b91114253d5ULL;
    const uint64_t c2 = 0x4cf5ad432745937fULL;

    // Body
    const uint64_t *blocks = (const uint64_t *)(data);
    for (int i = 0; i < nblocks; i++) {
        uint64_t k1 = blocks[i * 2 + 0];
        uint64_t k2 = blocks[i * 2 + 1];

        k1 *= c1; k1 = (k1 << 31) | (k1 >> (64 - 31)); k1 *= c2; h1 ^= k1;
        h1 = (h1 << 27) | (h1 >> (64 - 27)); h1 += h2; h1 = h1 * 5 + 0x52dce729;

        k2 *= c2; k2 = (k2 << 33) | (k2 >> (64 - 33)); k2 *= c1; h2 ^= k2;
        h2 = (h2 << 31) | (h2 >> (64 - 31)); h2 += h1; h2 = h2 * 5 + 0x38495ab5;
    }

    // Tail
    const uint8_t *tail = (const uint8_t *)(data + nblocks * 16);
    uint64_t k1 = 0;
    uint64_t k2 = 0;

    switch (len & 15) {
        case 15: k2 ^= ((uint64_t)tail[14]) << 48;
        case 14: k2 ^= ((uint64_t)tail[13]) << 40;
        case 13: k2 ^= ((uint64_t)tail[12]) << 32;
        case 12: k2 ^= ((uint64_t)tail[11]) << 24;
        case 11: k2 ^= ((uint64_t)tail[10]) << 16;
        case 10: k2 ^= ((uint64_t)tail[ 9]) << 8;
        case  9: k2 ^= ((uint64_t)tail[ 8]) << 0;
                 k2 *= c2; k2 = (k2 << 33) | (k2 >> (64 - 33)); k2 *= c1; h2 ^= k2;

        case  8: k1 ^= ((uint64_t)tail[ 7]) << 56;
        case  7: k1 ^= ((uint64_t)tail[ 6]) << 48;
        case  6: k1 ^= ((uint64_t)tail[ 5]) << 40;
        case  5: k1 ^= ((uint64_t)tail[ 4]) << 32;
        case  4: k1 ^= ((uint64_t)tail[ 3]) << 24;
        case  3: k1 ^= ((uint64_t)tail[ 2]) << 16;
        case  2: k1 ^= ((uint64_t)tail[ 1]) << 8;
        case  1: k1 ^= ((uint64_t)tail[ 0]) << 0;
                 k1 *= c1; k1 = (k1 << 31) | (k1 >> (64 - 31)); k1 *= c2; h1 ^= k1;
    }

    // Finalization
    h1 ^= len;
    h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 ^= h1 >> 33;
    h1 *= 0xff51afd7ed558ccdULL;
    h1 ^= h1 >> 33;
    h1 *= 0xc4ceb9fe1a85ec53ULL;
    h1 ^= h1 >> 33;

    h2 ^= h2 >> 33;
    h2 *= 0xff51afd7ed558ccdULL;
    h2 ^= h2 >> 33;
    h2 *= 0xc4ceb9fe1a85ec53ULL;
    h2 ^= h2 >> 33;

    h1 += h2;
    h2 += h1;

    out[0] = h1;
    out[1] = h2;
        
}

void AddRoundKey(uint64_t rk_msb, uint64_t rk_lsb, uint8_t state_matrix[STATE_ROWS][STATE_COLS], uint8_t transform_matrix[STATE_ROWS][STATE_COLS]){
    //Any Round key basically, just a namesake
    uint8_t root_matrix[STATE_ROWS][STATE_COLS];
    for (int i = 0; i < 8; i++) {
        root_matrix[i % STATE_ROWS][i / STATE_ROWS] = (rk_msb >> (56 - 8 * i)) & 0xFF;
        root_matrix[(i + 8) % STATE_ROWS][(i + 8) / STATE_ROWS] = (rk_lsb >> (56 - 8 * i)) & 0xFF;
    }
    

    for (int row = 0; row < STATE_ROWS; row++) {
        for (int col = 0; col < STATE_COLS; col++) {
            transform_matrix[row][col] = state_matrix[row][col]^root_matrix[row][col];
        }
    }
}

// Function to apply S-box transformation (SubBytes)
void SubBytes(uint8_t state_matrix[STATE_ROWS][STATE_COLS], uint8_t transform_matrix[STATE_ROWS][STATE_COLS]){
    for (int row = 0; row < STATE_ROWS; row++) {
        for (int col = 0; col < STATE_COLS; col++) {
            uint8_t byte = state_matrix[row][col];
            transform_matrix[row][col] = sbox[(byte >> 4) & 0x0F][byte & 0x0F];
        }
    }
}

void InverseSubBytes(uint8_t state_matrix[STATE_ROWS][STATE_COLS], uint8_t transform_matrix[STATE_ROWS][STATE_COLS]) {
    for (int row = 0; row < STATE_ROWS; row++) {
        for (int col = 0; col < STATE_COLS; col++) {
            uint8_t byte = state_matrix[row][col];
            transform_matrix[row][col] = inverse_sbox[(byte >> 4) & 0x0F][byte & 0x0F];
        }
    }
}



void ShiftRows(uint8_t matrix[STATE_ROWS][STATE_COLS]) {
    uint8_t temp = 0;

    // Row 1: Shift left by 1
    temp = matrix[1][0];
    matrix[1][0] = matrix[1][1];
    matrix[1][1] = matrix[1][2];
    matrix[1][2] = matrix[1][3];
    matrix[1][3] = temp;

    // Row 2: Shift left by 2
    temp = matrix[2][0];
    matrix[2][0] = matrix[2][2];
    matrix[2][2] = temp;
    temp = matrix[2][1];
    matrix[2][1] = matrix[2][3];
    matrix[2][3] = temp;

    // Row 3: Shift left by 3
    temp = matrix[3][3];
    matrix[3][3] = matrix[3][2];
    matrix[3][2] = matrix[3][1];
    matrix[3][1] = matrix[3][0];
    matrix[3][0] = temp;
}

void InverseShiftRows(uint8_t matrix[STATE_ROWS][STATE_COLS]) {
    uint8_t temp = 0;

    // Row 1: Shift right by 1
    temp = matrix[1][3];
    matrix[1][3] = matrix[1][2];
    matrix[1][2] = matrix[1][1];
    matrix[1][1] = matrix[1][0];
    matrix[1][0] = temp;

    // Row 2: Shift right by 2
    temp = matrix[2][0];
    matrix[2][0] = matrix[2][2];
    matrix[2][2] = temp;
    temp = matrix[2][1];
    matrix[2][1] = matrix[2][3];
    matrix[2][3] = temp;

    // Row 3: Shift right by 3
    temp = matrix[3][0];
    matrix[3][0] = matrix[3][1];
    matrix[3][1] = matrix[3][2];
    matrix[3][2] = matrix[3][3];
    matrix[3][3] = temp;
}

void MixColumns(uint8_t state[STATE_ROWS][STATE_COLS]) {
    
    //GF2    
    uint8_t gf_mul_2(uint8_t x) {
    return (x << 1) ^ ((x & 0x80) ? 0x1b : 0x00);
    }

    //GF3
    uint8_t gf_mul_3(uint8_t x) {
    return gf_mul_2(x) ^ x;
    }
    
    for (int col = 0; col < STATE_COLS; col++) {
        uint8_t s0 = state[0][col];
        uint8_t s1 = state[1][col];
        uint8_t s2 = state[2][col];
        uint8_t s3 = state[3][col];

        state[0][col] = gf_mul_2(s0) ^ gf_mul_3(s1) ^ s2 ^ s3;
        state[1][col] = s0 ^ gf_mul_2(s1) ^ gf_mul_3(s2) ^ s3;
        state[2][col] = s0 ^ s1 ^ gf_mul_2(s2) ^ gf_mul_3(s3);
        state[3][col] = gf_mul_3(s0) ^ s1 ^ s2 ^ gf_mul_2(s3);
    }
}

void InverseMixColumns(uint8_t state[STATE_ROWS][STATE_COLS]) {
  
    //GF2    
    uint8_t gf_mul_2(uint8_t x) {
    return (x << 1) ^ ((x & 0x80) ? 0x1b : 0x00);
    }

    //GF3
    uint8_t gf_mul_3(uint8_t x) {
    return gf_mul_2(x) ^ x;
    }
    
    // Galois Field multiplication by 9
    uint8_t gf_mul_9(uint8_t x) {
        return gf_mul_2(gf_mul_2(gf_mul_2(x))) ^ x;
    }

    // Galois Field multiplication by 11
    uint8_t gf_mul_11(uint8_t x) {
        return gf_mul_2(gf_mul_2(gf_mul_2(x)) ^ x) ^ x;
    }

    // Galois Field multiplication by 13
    uint8_t gf_mul_13(uint8_t x) {
        return gf_mul_2(gf_mul_2(gf_mul_2(x) ^ x)) ^ x;
    }

    // Galois Field multiplication by 14
    uint8_t gf_mul_14(uint8_t x) {
        return gf_mul_2(gf_mul_2(gf_mul_2(x) ^ x) ^ x);
    }

    for (int col = 0; col < STATE_COLS; col++) {
        uint8_t s0 = state[0][col];
        uint8_t s1 = state[1][col];
        uint8_t s2 = state[2][col];
        uint8_t s3 = state[3][col];

        state[0][col] = gf_mul_14(s0) ^ gf_mul_11(s1) ^ gf_mul_13(s2) ^ gf_mul_9(s3);
        state[1][col] = gf_mul_9(s0) ^ gf_mul_14(s1) ^ gf_mul_11(s2) ^ gf_mul_13(s3);
        state[2][col] = gf_mul_13(s0) ^ gf_mul_9(s1) ^ gf_mul_14(s2) ^ gf_mul_11(s3);
        state[3][col] = gf_mul_11(s0) ^ gf_mul_13(s1) ^ gf_mul_9(s2) ^ gf_mul_14(s3);
    }
}


