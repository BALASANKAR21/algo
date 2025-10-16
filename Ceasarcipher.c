#include <stdio.h>
#include <string.h>

int main(void) {
    char a[100], b[100], c[100];
    int i;
    int k = 3; /* change shift amount here */

    printf("Enter message: ");
    if (!fgets(a, sizeof a, stdin)) return 0;

    /* remove trailing newline if present */
    size_t n = strlen(a);
    if (n > 0 && a[n-1] == '\n') a[n-1] = '\0';

    /* Encrypt -> b */
    for (i = 0; a[i] != '\0'; i++) {
        if (a[i] >= 'A' && a[i] <= 'Z') {
            b[i] = ((a[i] - 'A' + k) % 26 + 26) % 26 + 'A';
        } else if (a[i] >= 'a' && a[i] <= 'z') {
            b[i] = ((a[i] - 'a' + k) % 26 + 26) % 26 + 'a';
        } else if (a[i] >= '0' && a[i] <= '9') {
            b[i] = ((a[i] - '0' + k) % 10 + 10) % 10 + '0';
        } else {
            b[i] = a[i];
        }
    }
    b[i] = '\0';
    /* Decrypt -> c (reverse shift) */
    for (i = 0; b[i] != '\0'; i++) {
        if (b[i] >= 'A' && b[i] <= 'Z') {
            c[i] = ((b[i] - 'A' - k) % 26 + 26) % 26 + 'A';
        } else if (b[i] >= 'a' && b[i] <= 'z') {
            c[i] = ((b[i] - 'a' - k) % 26 + 26) % 26 + 'a';
        } else if (b[i] >= '0' && b[i] <= '9') {
            c[i] = ((b[i] - '0' - k) % 10 + 10) % 10 + '0';
        } else {
            c[i] = b[i];
        }
    }
    c[i] = '\0';

    printf("Original:  %s\n", a);
    printf("Encrypted: %s\n", b);
    printf("Decrypted: %s\n", c);

    return 0;
}
