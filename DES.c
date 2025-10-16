#include <stdio.h>
#include <stdint.h>
//des
void p48(uint64_t v) {
printf("0x%012llX\n", v & 0xFFFFFFFFFFFFULL);
}
int main() {
uint64_t a = 0x0080008000850001ULL;
uint64_t b = 0x0000000000000180ULL;
uint32_t c = (uint32_t)(a >> 32);
uint32_t d = (uint32_t)(a & 0xFFFFFFFF);
printf("L0 = 0x%08X\n", c);
printf("R0 = 0x%08X\n", d);
uint64_t e = 0;
e |= ((uint64_t)((d >> 26) & 0x3F)) << 42;
e |= ((uint64_t)((d >> 20) & 0x3F)) << 36;
e |= ((uint64_t)((d >> 14) & 0x3F)) << 30;
e |= ((uint64_t)((d >> 8) & 0x3F)) << 24;
e |= ((uint64_t)((d >> 2) & 0x3F)) << 18;
e |= ((uint64_t)((d << 4) & 0x3F)) << 12;
e |= ((uint64_t)((d << 10) & 0x3F)) << 6;
e |= (uint64_t)(d & 0x3F);
printf("Expanded R0 (R1) = ");
p48(e);
uint64_t f = e ^ b;
printf("R2 (after XOR with key) = ");
p48(f);
uint32_t g = 0x43164CE2;
printf("S-box output = 0x%08X\n", g);
uint32_t h = 0x5456D409;
printf("Straight P-box output = 0x%08X\n", h);
uint32_t i = h ^ c;
printf("XOR with L0 = 0x%08X\n", i);
uint64_t j = ((uint64_t)d << 32) | i;
printf("Swapped output (64 bits) = 0x%016llX\n", j);
uint64_t k = 0x0011000011000000ULL;
uint64_t l = 0x0000000800000000ULL;
printf("Key Generation Input = 0x%016llX\n", k);
printf("Generated 48-bit Round Key = 0x%012llX\n", l >> 16);
return 0;
}
