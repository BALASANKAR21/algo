#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXMSG 1000

/* Find position of character x in matrix m; sets *r and *c */
void pos(char m[5][5], char x, int *r, int *c) {
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (m[i][j] == x) { *r = i; *c = j; return; }
}

/* Build 5x5 key matrix from key string k (letters only). J is merged with I. */
void mat(const char k[], char m[5][5]) {
    int seen[26] = {0};
    int i, j = 0;
    char ch;

    /* place key letters first */
    for (i = 0; k[i] != '\0'; i++) {
        if (!isalpha((unsigned char)k[i])) continue;
        ch = toupper((unsigned char)k[i]);
        if (ch == 'J') ch = 'I';
        if (!seen[ch - 'A']) {
            seen[ch - 'A'] = 1;
            m[j / 5][j % 5] = ch;
            j++;
            if (j == 25) return;
        }
    }

    /* place remaining letters A-Z (skip J) */
    for (ch = 'A'; ch <= 'Z' && j < 25; ch++) {
        if (ch == 'J') continue;
        if (!seen[ch - 'A']) {
            m[j / 5][j % 5] = ch;
            j++;
        }
    }
}

/* Prepare the message into digraphs:
   - remove non-alpha
   - uppercase
   - replace J with I
   - insert 'X' between duplicate letters in a digraph
   - pad with 'X' if final length is odd
*/
void prep(const char in[], char out[]) {
    int i = 0, o = 0;
    char a, b;

    while (in[i] != '\0') {
        /* find next letter for a */
        while (in[i] != '\0' && !isalpha((unsigned char)in[i])) i++;
        if (in[i] == '\0') break;
        a = toupper((unsigned char)in[i++]);
        if (a == 'J') a = 'I';

        /* find next letter for b (lookahead, but may be same as a) */
        int look = i;
        while (in[look] != '\0' && !isalpha((unsigned char)in[look])) look++;
        if (in[look] == '\0') {
            /* no b available, pair a with 'X' */
            out[o++] = a;
            out[o++] = 'X';
            break;
        }
        b = toupper((unsigned char)in[look]);
        if (b == 'J') b = 'I';

        if (a == b) {
            /* insert X between identical letters (playfair rule) */
            out[o++] = a;
            out[o++] = 'X';
            /* i remains at current position so next loop uses same lookahead letter */
        } else {
            /* use the pair a and b; advance i to consume b */
            out[o++] = a;
            out[o++] = b;
            i = look + 1;
        }
    }

    if (o % 2 != 0) { /* pad with X if odd length (shouldn't normally happen) */
        out[o++] = 'X';
    }
    out[o] = '\0';
}

/* Encrypt prepared digraphs b[] using matrix m into c[] */
void enc(const char b[], char m[5][5], char c[]) {
    int i, r1, c1, r2, c2;
    for (i = 0; b[i] != '\0'; i += 2) {
        pos(m, b[i], &r1, &c1);
        pos(m, b[i+1], &r2, &c2);
        if (r1 == r2) {
            /* same row -> shift right */
            c[i]   = m[r1][(c1 + 1) % 5];
            c[i+1] = m[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            /* same column -> shift down */
            c[i]   = m[(r1 + 1) % 5][c1];
            c[i+1] = m[(r2 + 1) % 5][c2];
        } else {
            /* rectangle -> swap columns */
            c[i]   = m[r1][c2];
            c[i+1] = m[r2][c1];
        }
    }
    c[i] = '\0';
}

/* Decrypt prepared digraphs b[] using matrix m into c[] */
void dec(const char b[], char m[5][5], char c[]) {
    int i, r1, c1, r2, c2;
    for (i = 0; b[i] != '\0'; i += 2) {
        pos(m, b[i], &r1, &c1);
        pos(m, b[i+1], &r2, &c2);
        if (r1 == r2) {
            /* same row -> shift left */
            c[i]   = m[r1][(c1 + 4) % 5];
            c[i+1] = m[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            /* same column -> shift up */
            c[i]   = m[(r1 + 4) % 5][c1];
            c[i+1] = m[(r2 + 4) % 5][c2];
        } else {
            /* rectangle -> swap columns */
            c[i]   = m[r1][c2];
            c[i+1] = m[r2][c1];
        }
    }
    c[i] = '\0';
}

int main(void) {
    char a[MAXMSG], k[MAXMSG];
    char mk[5][5];
    char prepmsg[MAXMSG];
    char encmsg[MAXMSG];
    char decmsg[MAXMSG];

    printf("Enter message: ");
    if (!fgets(a, sizeof a, stdin)) return 0;
    /* remove trailing newline */
    a[strcspn(a, "\n")] = '\0';

    printf("Enter key: ");
    if (!fgets(k, sizeof k, stdin)) return 0;
    k[strcspn(k, "\n")] = '\0';

    mat(k, mk);
    prep(a, prepmsg);
    enc(prepmsg, mk, encmsg);
    dec(encmsg, mk, decmsg);

    printf("\nOriginal  : %s\n", a);
    printf("Key       : %s\n", k);
    printf("Prepared  : %s\n", prepmsg);

    /* print matrix for clarity */
    printf("\n5x5 Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", mk[i][j]);
        }
        printf("\n");
    }

    printf("\nEncrypted : %s\n", encmsg);
    printf("Decrypted : %s\n", decmsg);

    return 0;
}
