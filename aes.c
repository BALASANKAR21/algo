#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

static const uint8_t sbox[256] = {
  /* 0x00 - 0x0f */ 0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
  /* 0x10 - 0x1f */ 0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
  /* 0x20 - 0x2f */ 0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
  /* 0x30 - 0x3f */ 0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
  /* 0x40 - 0x4f */ 0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
  /* 0x50 - 0x5f */ 0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
  /* 0x60 - 0x6f */ 0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
  /* 0x70 - 0x7f */ 0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
  /* 0x80 - 0x8f */ 0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
  /* 0x90 - 0x9f */ 0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
  /* 0xa0 - 0xaf */ 0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
  /* 0xb0 - 0xbf */ 0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
  /* 0xc0 - 0xcf */ 0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
  /* 0xd0 - 0xdf */ 0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
  /* 0xe0 - 0xef */ 0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
  /* 0xf0 - 0xff */ 0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

static const uint8_t inv_sbox[256] = {
  /* precomputed inverse S-box */ 
  0x52,0x09,0x6A,0xD5,0x30,0x36,0xA5,0x38,0xBF,0x40,0xA3,0x9E,0x81,0xF3,0xD7,0xFB,
  0x7C,0xE3,0x39,0x82,0x9B,0x2F,0xFF,0x87,0x34,0x8E,0x43,0x44,0xC4,0xDE,0xE9,0xCB,
  0x54,0x7B,0x94,0x32,0xA6,0xC2,0x23,0x3D,0xEE,0x4C,0x95,0x0B,0x42,0xFA,0xC3,0x4E,
  0x08,0x2E,0xA1,0x66,0x28,0xD9,0x24,0xB2,0x76,0x5B,0xA2,0x49,0x6D,0x8B,0xD1,0x25,
  0x72,0xF8,0xF6,0x64,0x86,0x68,0x98,0x16,0xD4,0xA4,0x5C,0xCC,0x5D,0x65,0xB6,0x92,
  0x6C,0x70,0x48,0x50,0xFD,0xED,0xB9,0xDA,0x5E,0x15,0x46,0x57,0xA7,0x8D,0x9D,0x84,
  0x90,0xD8,0xAB,0x00,0x8C,0xBC,0xD3,0x0A,0xF7,0xE4,0x58,0x05,0xB8,0xB3,0x45,0x06,
  0xD0,0x2C,0x1E,0x8F,0xCA,0x3F,0x0F,0x02,0xC1,0xAF,0xBD,0x03,0x01,0x13,0x8A,0x6B,
  0x3A,0x91,0x11,0x41,0x4F,0x67,0xDC,0xEA,0x97,0xF2,0xCF,0xCE,0xF0,0xB4,0xE6,0x73,
  0x96,0xAC,0x74,0x22,0xE7,0xAD,0x35,0x85,0xE2,0xF9,0x37,0xE8,0x1C,0x75,0xDF,0x6E,
  0x47,0xF1,0x1A,0x71,0x1D,0x29,0xC5,0x89,0x6F,0xB7,0x62,0x0E,0xAA,0x18,0xBE,0x1B,
  0xFC,0x56,0x3E,0x4B,0xC6,0xD2,0x79,0x20,0x9A,0xDB,0xC0,0xFE,0x78,0xCD,0x5A,0xF4,
  0x1F,0xDD,0xA8,0x33,0x88,0x07,0xC7,0x31,0xB1,0x12,0x10,0x59,0x27,0x80,0xEC,0x5F,
  0x60,0x51,0x7F,0xA9,0x19,0xB5,0x4A,0x0D,0x2D,0xE5,0x7A,0x9F,0x93,0xC9,0x9C,0xEF,
  0xA0,0xE0,0x3B,0x4D,0xAE,0x2A,0xF5,0xB0,0xC8,0xEB,0xBB,0x3C,0x83,0x53,0x99,0x61,
  0x17,0x2B,0x04,0x7E,0xBA,0x77,0xD6,0x26,0xE1,0x69,0x14,0x63,0x55,0x21,0x0C,0x7D
};

/* Rcon for KeyExpansion */
static const uint8_t Rcon[11] = {
    0x00, /* not used 0 */
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36
};

/* helper: multiply by x in GF(2^8) */
static inline uint8_t xtime(uint8_t x) {
    return (uint8_t)((x << 1) ^ ((x & 0x80) ? 0x1B : 0x00));
}

/* multiply in GF(2^8) by fixed constants used in MixColumns */
static uint8_t mul(uint8_t a, uint8_t b) {
    uint8_t res = 0;
    while (b) {
        if (b & 1) res ^= a;
        a = xtime(a);
        b >>= 1;
    }
    return res;
}

/* -- AES core functions operating on a 16-byte state (column-major by convention) -- */

/* AddRoundKey: XOR state with round key (16 bytes) */
static void AddRoundKey(uint8_t state[16], const uint8_t roundKey[16]) {
    for (int i = 0; i < 16; ++i) state[i] ^= roundKey[i];
}

/* SubBytes using S-box */
static void SubBytes(uint8_t state[16]) {
    for (int i = 0; i < 16; ++i) state[i] = sbox[state[i]];
}

/* InvSubBytes */
static void InvSubBytes(uint8_t state[16]) {
    for (int i = 0; i < 16; ++i) state[i] = inv_sbox[state[i]];
}

/* ShiftRows (left rotation per row: row 0=0, row1=1, row2=2, row3=3) */
static void ShiftRows(uint8_t state[16]) {
    uint8_t tmp[16];
    /* row 0 */
    tmp[0]  = state[0];
    tmp[4]  = state[4];
    tmp[8]  = state[8];
    tmp[12] = state[12];
    /* row 1 */
    tmp[1]  = state[5];
    tmp[5]  = state[9];
    tmp[9]  = state[13];
    tmp[13] = state[1];
    /* row 2 */
    tmp[2]  = state[10];
    tmp[6]  = state[14];
    tmp[10] = state[2];
    tmp[14] = state[6];
    /* row 3 */
    tmp[3]  = state[15];
    tmp[7]  = state[3];
    tmp[11] = state[7];
    tmp[15] = state[11];

    memcpy(state, tmp, 16);
}

/* InvShiftRows */
static void InvShiftRows(uint8_t state[16]) {
    uint8_t tmp[16];
    /* row0 */
    tmp[0]  = state[0];
    tmp[4]  = state[4];
    tmp[8]  = state[8];
    tmp[12] = state[12];
    /* row1 (right rotate 1) */
    tmp[1]  = state[13];
    tmp[5]  = state[1];
    tmp[9]  = state[5];
    tmp[13] = state[9];
    /* row2 (right rotate 2) */
    tmp[2]  = state[10];
    tmp[6]  = state[14];
    tmp[10] = state[2];
    tmp[14] = state[6];
    /* row3 (right rotate 3) */
    tmp[3]  = state[7];
    tmp[7]  = state[11];
    tmp[11] = state[15];
    tmp[15] = state[3];

    memcpy(state, tmp, 16);
}

/* MixColumns */
static void MixColumns(uint8_t state[16]) {
    for (int c = 0; c < 4; ++c) {
        int col = c * 4;
        uint8_t a0 = state[col + 0];
        uint8_t a1 = state[col + 1];
        uint8_t a2 = state[col + 2];
        uint8_t a3 = state[col + 3];
        uint8_t r0 = (uint8_t)(mul(0x02, a0) ^ mul(0x03, a1) ^ a2 ^ a3);
        uint8_t r1 = (uint8_t)(a0 ^ mul(0x02, a1) ^ mul(0x03, a2) ^ a3);
        uint8_t r2 = (uint8_t)(a0 ^ a1 ^ mul(0x02, a2) ^ mul(0x03, a3));
        uint8_t r3 = (uint8_t)(mul(0x03, a0) ^ a1 ^ a2 ^ mul(0x02, a3));
        state[col+0] = r0; state[col+1] = r1; state[col+2] = r2; state[col+3] = r3;
    }
}

/* InvMixColumns */
static void InvMixColumns(uint8_t state[16]) {
    for (int c = 0; c < 4; ++c) {
        int col = c * 4;
        uint8_t a0 = state[col + 0];
        uint8_t a1 = state[col + 1];
        uint8_t a2 = state[col + 2];
        uint8_t a3 = state[col + 3];
        uint8_t r0 = (uint8_t)(mul(0x0e, a0) ^ mul(0x0b, a1) ^ mul(0x0d, a2) ^ mul(0x09, a3));
        uint8_t r1 = (uint8_t)(mul(0x09, a0) ^ mul(0x0e, a1) ^ mul(0x0b, a2) ^ mul(0x0d, a3));
        uint8_t r2 = (uint8_t)(mul(0x0d, a0) ^ mul(0x09, a1) ^ mul(0x0e, a2) ^ mul(0x0b, a3));
        uint8_t r3 = (uint8_t)(mul(0x0b, a0) ^ mul(0x0d, a1) ^ mul(0x09, a2) ^ mul(0x0e, a3));
        state[col+0] = r0; state[col+1] = r1; state[col+2] = r2; state[col+3] = r3;
    }
}

/* -- Key expansion for AES-128 (Nk=4, Nr=10, Nb=4) -- */
/* Expanded key size: 176 bytes (11 round keys * 16 bytes) */
static void KeyExpansion(const uint8_t key[16], uint8_t roundKeys[176]) {
    /* first round key is the key itself */
    memcpy(roundKeys, key, 16);

    uint8_t temp[4];
    int bytesGenerated = 16;
    int rconIter = 1;
    uint8_t k;

    while (bytesGenerated < 176) {
        /* last 4 bytes */
        for (int i = 0; i < 4; ++i)
            temp[i] = roundKeys[bytesGenerated - 4 + i];

        if (bytesGenerated % 16 == 0) {
            /* rotate */
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;
            /* sub bytes */
            temp[0] = sbox[temp[0]];
            temp[1] = sbox[temp[1]];
            temp[2] = sbox[temp[2]];
            temp[3] = sbox[temp[3]];
            /* Rcon */
            temp[0] ^= Rcon[rconIter];
            rconIter++;
        }

        for (int i = 0; i < 4; ++i) {
            roundKeys[bytesGenerated] = roundKeys[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
}

/* Helper to get pointer to round key number `round` (0..10) */
static const uint8_t* RoundKey(const uint8_t roundKeys[176], int round) {
    return &roundKeys[round * 16];
}

/* AES-128 encrypt single 16-byte block (in place) */
static void AES128_EncryptBlock(const uint8_t in[16], uint8_t out[16], const uint8_t roundKeys[176]) {
    uint8_t state[16];
    memcpy(state, in, 16);

    AddRoundKey(state, RoundKey(roundKeys, 0));

    for (int round = 1; round <= 9; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, RoundKey(roundKeys, round));
    }

    /* final round */
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, RoundKey(roundKeys, 10));

    memcpy(out, state, 16);
}

/* AES-128 decrypt single 16-byte block (in place) */
static void AES128_DecryptBlock(const uint8_t in[16], uint8_t out[16], const uint8_t roundKeys[176]) {
    uint8_t state[16];
    memcpy(state, in, 16);

    AddRoundKey(state, RoundKey(roundKeys, 10));
    for (int round = 9; round >= 1; --round) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, RoundKey(roundKeys, round));
        InvMixColumns(state);
    }
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, RoundKey(roundKeys, 0));

    memcpy(out, state, 16);
}

/* PKCS#7 padding for block size 16.
 * Returns padded length on success; buff must have space for padded bytes.
 */
static size_t pkcs7_pad(uint8_t *buff, size_t len) {
    size_t pad = 16 - (len % 16);
    for (size_t i = 0; i < pad; ++i) buff[len + i] = (uint8_t)pad;
    return len + pad;
}

/* remove PKCS#7 padding; returns new length or (size_t)-1 on error */
static size_t pkcs7_unpad(uint8_t *buff, size_t len) {
    if (len == 0 || (len % 16) != 0) return (size_t)-1;
    uint8_t last = buff[len - 1];
    if (last == 0 || last > 16) return (size_t)-1;
    for (size_t i = 0; i < last; ++i) {
        if (buff[len - 1 - i] != last) return (size_t)-1;
    }
    return len - last;
}

/* CBC encrypt: plaintext -> ciphertext. cipher buffer must be large enough.
 * key: 16 bytes, iv: 16 bytes.
 * Returns ciphertext length (multiple of 16) or 0 on error.
 */
size_t AES128_CBC_encrypt(const uint8_t *plaintext, size_t plen,
                          const uint8_t key[16], const uint8_t iv[16],
                          uint8_t **cipher_out) {
    uint8_t roundKeys[176];
    KeyExpansion(key, roundKeys);

    /* copy plaintext into a modifiable buffer to pad */
    size_t bufsize = ((plen / 16) + 1) * 16;
    uint8_t *buf = malloc(bufsize);
    if (!buf) return 0;
    memcpy(buf, plaintext, plen);
    size_t padded = pkcs7_pad(buf, plen); /* now padded <= bufsize */

    uint8_t *cipher = malloc(padded);
    if (!cipher) { free(buf); return 0; }

    uint8_t chain[16];
    memcpy(chain, iv, 16);

    for (size_t off = 0; off < padded; off += 16) {
        uint8_t block[16];
        for (int i = 0; i < 16; ++i) block[i] = buf[off + i] ^ chain[i];
        AES128_EncryptBlock(block, &cipher[off], roundKeys);
        memcpy(chain, &cipher[off], 16);
    }

    free(buf);
    *cipher_out = cipher;
    return padded;
}

/* CBC decrypt:
 * ciphertext length must be multiple of 16.
 * Returns plaintext length, *plain_out allocated (must be freed), or 0 on error.
 */
size_t AES128_CBC_decrypt(const uint8_t *ciphertext, size_t clen,
                          const uint8_t key[16], const uint8_t iv[16],
                          uint8_t **plain_out) {
    if (clen == 0 || (clen % 16) != 0) return 0;

    uint8_t roundKeys[176];
    KeyExpansion(key, roundKeys);

    uint8_t *plain = malloc(clen);
    if (!plain) return 0;

    uint8_t chain[16], prev[16];
    memcpy(chain, iv, 16);

    for (size_t off = 0; off < clen; off += 16) {
        AES128_DecryptBlock(&ciphertext[off], prev, roundKeys);
        for (int i = 0; i < 16; ++i) plain[off + i] = prev[i] ^ chain[i];
        memcpy(chain, &ciphertext[off], 16);
    }

    /* unpad */
    size_t plen = pkcs7_unpad(plain, clen);
    if (plen == (size_t)-1) { free(plain); return 0; }

    *plain_out = plain;
    return plen;
}

/* helper: print hex */
static void print_hex(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) printf("%02x", buf[i]);
    printf("\n");
}

/* -- Example usage in main() -- */
int main(void) {
    const char *plaintext = "The quick brown fox jumps over the lazy dog.";
    /* 16-byte key and IV (for demo only) */
    const uint8_t key[16] = {
        0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c
    };
    const uint8_t iv[16] = {
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
    };

    printf("Plaintext: %s\n", plaintext);

    uint8_t *cipher;
    size_t clen = AES128_CBC_encrypt((const uint8_t*)plaintext, strlen(plaintext), key, iv, &cipher);
    if (clen == 0) { fprintf(stderr, "Encryption failed\n"); return 1; }

    printf("Ciphertext (hex): ");
    print_hex(cipher, clen);

    uint8_t *decrypted;
    size_t plen = AES128_CBC_decrypt(cipher, clen, key, iv, &decrypted);
    if (plen == 0) { fprintf(stderr, "Decryption failed\n"); free(cipher); return 1; }

    printf("Decrypted: %.*s\n", (int)plen, decrypted);

    free(cipher);
    free(decrypted);
    return 0;
}
