#include<stdio.h>
#include<math.h>
int main(){
 int c;
 printf("Enter 1 for E11(1,1) or 2 for E23(1,1): ");
 scanf("%d", &c);
 if (c == 1)
 {
 int a = 1, b = 1, p = 11;
 printf("Points: ");
 for (int x = 0; x < p; x++){
 int y2 = (x*x*x + a*x + b) % p;
 for (int y = 0; y < p; y++)
 { if ((y*y) % p == y2)
 {
 printf("(%d,%d) ", x, y);
 }}}
 printf("\n");
 }
 else if (c == 2) {
 int a = 1, b = 1, p = 23;
 int d = (4*a*a*a + 27*b*b) % p;
 if (d != 0)
 {
 printf("Valid curve\n");
 }
 int x1 = 6, y1 = 4, x2 = 12, y2 = 9;
 int s;
 if (x1 == x2 && y1 == y2)
 {
 s = (3*x1*x1 + a) * (int)pow(2*y1, p-2);
 }
 else
 {
 s = (y2 - y1) * (int)pow(x2 - x1, p-2);
 }
 s %= p;
 int x3 = (s*s - x1 - x2) % p;
 int y3 = (s*(x1 - x3) - y1) % p;
 if (x3 < 0) x3 += p;
 if (y3 < 0) y3 += p;
 printf("P+Q= (%d,%d)\n", x3, y3);
 int x4 = 7, y4 = 11;
 int y5 = (-y4) % p;
 if (y5 < 0) y5 += p;
 printf("-P= (%d,%d)\n", x4, y5);
 int x6 = 0, y6 = 1;
 int s2 = (3*x6*x6 + a) * (int)pow(2*y6, p-2) % p;
 int x7 = (s2*s2 - 2*x6) % p;
 int y7 = (s2*(x6 - x7) - y6) % p;
 if (x7 < 0) x7 += p;
 if (y7 < 0) y7 += p;
 s2 = (y7 - y6) * (int)pow(x7 - x6, p-2) % p;
 int x8 = (s2*s2 - x6 - x7) % p;
 int y8 = (s2*(x6 - x8) - y6) % p;
 if (x8 < 0) x8 += p;
 if (y8 < 0) y8 += p;
 printf("3P= (%d,%d)\n", x8, y8);
 }

 return 0;
}
