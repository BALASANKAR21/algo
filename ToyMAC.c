//Ex:8 Toy MAC
#include<stdio.h>
#include<string.h>
int main() {
 char t[100], k[100], m[100];
 int i, j, l, h, v;
 printf("Toy MAC\n");
 printf("Enter message: ");
 scanf("%s", t);
 printf("Enter sender key: ");
 scanf("%s", k);
 l = strlen(k);
 for(i = 0; i < strlen(t); i++) {
 m[i] = t[i];
 }
 m[i] = '\0';
 h = 0;
 for(i = 0; i < l; i++) {
 h += ((k[i] - 'A') * (i+1));
 }
 for(i = 0; i < strlen(t); i++) {
 h += ((t[i] - 'A') * (l+i+1));
 }
 h = h % 26;
 printf("Transmitted: %s%c\n", m, h + 'A');
 printf("Enter receiver key: ");
 scanf("%s", k);
 v = 0;
 l = strlen(k);
 for(i = 0; i < l; i++) {
 v += ((k[i] - 'A') * (i+1));
 }
 for(i = 0; i < strlen(t); i++) {
 v += ((t[i] - 'A') * (l+i+1));
 }
 v = v % 26;
 if(v == h) {
 printf("Accepted\n");
 }
 else {
 printf("Rejected\n");
 }
 return 0;
}

//Toy Nested MAC
#include<stdio.h>
#include<string.h>
int main() {
 char t[100], k[100], m[100];
 int i, j, l, h1, h2, v1, v2;
 printf("Toy Nested MAC\n");
 printf("Enter message: ");
 scanf("%s", t);
 printf("Enter key: ");
 scanf("%s", k);
 l = strlen(k);
 h1 = 0;
 for(i = 0; i < l; i++) {
 h1 += ((k[i] - 'A') * (i+1));
 }
 for(i = 0; i < strlen(t); i++) {
 h1 += ((t[i] - 'A') * (l+i+1));
 }
 h1 = h1 % 26;
 printf("Inner MAC: %c\n", h1 + 'A');
 h2 = 0;
 for(i = 0; i < l; i++) {
 h2 += ((k[i] - 'A') * (i+1));
 }
 h2 += ((h1) * (l+1));
 h2 = h2 % 26;
 printf("Outer MAC: %c\n", h2 + 'A');
 printf("Transmitted: %s%c\n", t, h2 + 'A');
 v1 = 0;
 for(i = 0; i < l; i++) {
 v1 += ((k[i] - 'A') * (i+1));
 }
 for(i = 0; i < strlen(t); i++) {
 v1 += ((t[i] - 'A') * (l+i+1));
 }
 v1 = v1 % 26;
 printf("Receiver Inner MAC: %c\n", v1 + 'A');
 v2 = 0;
 for(i = 0; i < l; i++) {
 v2 += ((k[i] - 'A') * (i+1));
 }
 v2 += ((v1) * (l+1));
 v2 = v2 % 26;
 printf("Receiver Outer MAC: %c\n", v2 + 'A');

 if(v2 == h2) printf("Accepted\n");
 else printf("Rejected\n");

 return 0;
}

//Ex:9 Hashing – SHA 512
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define ROTR(x,n) (((x) >> (n)) | ((x) << (64 - (n))))
static const uint64_t K[80] = {
 0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL,
0xe9b5dba58189dbbcULL,
 0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL,
0xab1c5ed5da6d8118ULL,
 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL,
0x550c7dc3d5ffb4e2ULL,
 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL,
0xc19bf174cf692694ULL,
 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL,
0x240ca1cc77ac9c65ULL,
 0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL,
0x76f988da831153b5ULL,
 0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL,
0xbf597fc7beef0ee4ULL,
 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL,
0x142929670a0e6e70ULL,
 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL,
0x53380d139d95b3dfULL,
 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL,
0x92722c851482353bULL,
 0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL,
0xc76c51a30654be30ULL,
 0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL,
0x106aa07032bbd1b8ULL,
 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL,
0x34b0bcb5e19b48a8ULL,
 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL,
0x682e6ff3d6b2b8a3ULL,
 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL,
0x8cc702081a6439ecULL,
 0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL,
0xc67178f2e372532bULL,
 0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL,
0xf57d4f7fee6ed178ULL,
 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL,
0x1b710b35131c471bULL,
 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL,
0x431d67c49c100d4cULL,
 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL,
0x6c44198c4a475817ULL
};
static const uint64_t H0[8] = {
 0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL,
0xa54ff53a5f1d36f1ULL,
 0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL,
0x5be0cd19137e2179ULL
};
static uint64_t be64(const unsigned char *p) {
 return ((uint64_t)p[0] << 56) | ((uint64_t)p[1] << 48) | ((uint64_t)p[2] << 40) |
 ((uint64_t)p[3] << 32) | ((uint64_t)p[4] << 24) | ((uint64_t)p[5] << 16) |
 ((uint64_t)p[6] << 8) | ((uint64_t)p[7]);
}
void sha512(const unsigned char *msg, size_t len, unsigned char out[64]) {
 uint64_t H[8];
 memcpy(H, H0, sizeof(H));
 uint64_t ml = (uint64_t)len * 8ULL;
 size_t total = len + 1 + 16; // original + 0x80 + 128-bit length
 size_t blocks = (total + 127) / 128;
 size_t padded_len = blocks * 128;
 unsigned char *buf = calloc(1, padded_len);
 if (!buf) { fprintf(stderr,"malloc failed\n"); exit(1); }
 memcpy(buf, msg, len);
 buf[len] = 0x80;
 for (int i = 0; i < 8; ++i) buf[padded_len - 16 + i] = 0;
 for (int i = 0; i < 8; ++i) buf[padded_len - 8 + i] = (unsigned char)(ml >> (56 -
8*i));
 uint64_t w[80];
 for (size_t b = 0; b < blocks; ++b) {
 unsigned char *block = buf + b*128;
 for (int t = 0; t < 16; ++t) {
 w[t] = be64(block + t*8);
 }
 for (int t = 16; t < 80; ++t) {
 uint64_t s0 = ROTR(w[t-15], 1) ^ ROTR(w[t-15], 8) ^ (w[t-15] >> 7);
 uint64_t s1 = ROTR(w[t-2], 19) ^ ROTR(w[t-2], 61) ^ (w[t-2] >> 6);
 w[t] = w[t-16] + s0 + w[t-7] + s1;
 }
 uint64_t a = H[0], b_ = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6],
h = H[7];
 for (int t = 0; t < 80; ++t) {
 uint64_t S1 = ROTR(e,14) ^ ROTR(e,18) ^ ROTR(e,41);
 uint64_t ch = (e & f) ^ ((~e) & g);
 uint64_t temp1 = h + S1 + ch + K[t] + w[t];
 uint64_t S0 = ROTR(a,28) ^ ROTR(a,34) ^ ROTR(a,39);
 uint64_t maj = (a & b_) ^ (a & c) ^ (b_ & c);
 uint64_t temp2 = S0 + maj;
 h = g; g = f; f = e; e = d + temp1; d = c; c = b_; b_ = a; a = temp1 +
temp2;
 }
 H[0] += a; H[1] += b_; H[2] += c; H[3] += d;
 H[4] += e; H[5] += f; H[6] += g; H[7] += h;
 }
 free(buf);
 for (int i = 0; i < 8; ++i) {
 uint64_t x = H[i];
 out[i*8 + 0] = (unsigned char)(x >> 56);
 out[i*8 + 1] = (unsigned char)(x >> 48);
 out[i*8 + 2] = (unsigned char)(x >> 40);
 out[i*8 + 3] = (unsigned char)(x >> 32);
 out[i*8 + 4] = (unsigned char)(x >> 24);
 out[i*8 + 5] = (unsigned char)(x >> 16);
 out[i*8 + 6] = (unsigned char)(x >> 8);
 out[i*8 + 7] = (unsigned char)x;
 }
}
int main(void) {
 char input[1000];
 printf("Enter string: ");
 if (!fgets(input, sizeof input, stdin)) return 0;
 input[strcspn(input, "\n")] = '\0';
 unsigned char digest[64];
 sha512((unsigned char*)input, strlen(input), digest);
 printf("SHA-512: ");
 for (int i = 0; i < 64; ++i) printf("%02x", digest[i]);
 printf("\n");
 return 0;
}
