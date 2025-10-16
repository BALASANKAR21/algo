#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char a[1000], b[1000], c[1000], k[1000];
    int i, j, l;
    int keylen;

    printf("Enter message to encrypt: ");
    scanf("%[^\n]", a);
    getchar(); // clear newline

    printf("Enter encryption key (alphabetic only): ");
    scanf("%[^\n]", k);

    // Check key validity
    for (i = 0; k[i] != '\0'; i++) {
        if (!isalpha(k[i])) {
            printf("Error: Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    keylen = strlen(k);

    // Encryption
    l = 0;
    for (i = 0; a[i] != '\0'; i++) {
        if (isupper(a[i])) {
            j = k[l % keylen];
            j = isupper(j) ? j - 'A' : j - 'a';
            b[i] = (a[i] - 'A' + j) % 26 + 'A';
            l++;
        } else if (islower(a[i])) {
            j = k[l % keylen];
            j = isupper(j) ? j - 'A' : j - 'a';
            b[i] = (a[i] - 'a' + j) % 26 + 'a';
            l++;
        } else {
            b[i] = a[i];
        }
    }
    b[i] = '\0';

    // Decryption
    l = 0;
    for (i = 0; b[i] != '\0'; i++) {
        if (isupper(b[i])) {
            j = k[l % keylen];
            j = isupper(j) ? j - 'A' : j - 'a';
            c[i] = (b[i] - 'A' - j + 26) % 26 + 'A';
            l++;
        } else if (islower(b[i])) {
            j = k[l % keylen];
            j = isupper(j) ? j - 'A' : j - 'a';
            c[i] = (b[i] - 'a' - j + 26) % 26 + 'a';
            l++;
        } else {
            c[i] = b[i];
        }
    }
    c[i] = '\0';

    // Output results
    printf("\nOriginal : %s\n", a);
    printf("Key       : %s\n", k);
    printf("Encrypted : %s\n", b);
    printf("Decrypted : %s\n", c);

    return 0;
}
