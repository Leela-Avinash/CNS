#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[], char result[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            char keyOffset = isupper(key[j % keyLen]) ? 'A' : 'a';

            // (plaintext_char - offset + (key_char - keyOffset)) mod 26 + offset
            result[i] = ((text[i] - offset + (key[j % keyLen] - keyOffset)) % 26) + offset;
            j++;
        } else {
            result[i] = text[i];
        }
    }
    result[textLen] = '\0'; 
}

void decrypt(char text[], char key[], char result[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            char keyOffset = isupper(key[j % keyLen]) ? 'A' : 'a';

            // (ciphertext_char - offset - (key_char - keyOffset) + 26) mod 26 + offset
            result[i] = (((text[i] - offset) - (key[j % keyLen] - keyOffset) + 26) % 26) + offset;
            j++;
        } else {
            result[i] = text[i];
        }
    }
    result[textLen] = '\0';
}

int main() {
    char text[1000], key[100];
    char encrypted[1000], decrypted[1000];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    encrypt(text, key, encrypted);
    printf("Encrypted Text: %s\n", encrypted);

    decrypt(encrypted, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
