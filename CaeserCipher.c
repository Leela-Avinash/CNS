#include <stdio.h>
#include <ctype.h>

void caesarCipher(char *text, int shift) {
    for(int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if(isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift + 26) % 26 + base;
        }
        text[i] = c;
    }
}

int main( ) {
    char message[100];
    int shift;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the shift value: ");
    scanf("%d", &shift);

    printf("Original message: %s", message);

    caesarCipher(message, shift);
    printf("Encrypted message: %s", message);

    caesarCipher(message, -shift);
    printf("Decrypted message : %s", message);

    return 0;
}