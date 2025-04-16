#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

void preprocessText(char text[], char processed[]);
void encryptHill(char processed[], char cipher[]);
void decryptHill(char cipher[], char decrypted[]);

int main() {
    char text[MAX], processed[MAX] = "";
    char cipher[MAX] = "", decrypted[MAX] = "";
    
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  

    preprocessText(text, processed);

    encryptHill(processed, cipher);
    printf("Encrypted Text: %s\n", cipher);

    decryptHill(cipher, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}

void preprocessText(char text[], char processed[]) {
    int j = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            processed[j++] = toupper(text[i]);
        }
    }
    processed[j] = '\0';
    
    if (j % 2 != 0) {
        processed[j++] = 'X';
        processed[j] = '\0';
    }
}

void encryptHill(char processed[], char cipher[]) {
    int key[2][2] = { {3, 3}, {2, 5} };
    int len = strlen(processed);
    int index = 0;
    for (int i = 0; i < len; i += 2) {
        int x1 = processed[i] - 'A';
        int x2 = processed[i+1] - 'A';

        int y1 = (key[0][0] * x1 + key[0][1] * x2) % 26;
        int y2 = (key[1][0] * x1 + key[1][1] * x2) % 26;

        cipher[index++] = y1 + 'A';
        cipher[index++] = y2 + 'A';
    }
    cipher[index] = '\0';
}

void decryptHill(char cipher[], char decrypted[]) {
    int invKey[2][2] = { {15, 17}, {20, 9} };
    int len = strlen(cipher);
    int index = 0;
    for (int i = 0; i < len; i += 2) {
        int y1 = cipher[i] - 'A';
        int y2 = cipher[i+1] - 'A';

        int x1 = (invKey[0][0] * y1 + invKey[0][1] * y2) % 26;
        int x2 = (invKey[1][0] * y1 + invKey[1][1] * y2) % 26;
        
        x1 = (x1 + 26) % 26;
        x2 = (x2 + 26) % 26;

        decrypted[index++] = x1 + 'A';
        decrypted[index++] = x2 + 'A';
    }
    decrypted[index] = '\0';
}
