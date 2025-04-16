#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX 1000

void formatPlaintext(char plaintext[], char formatted[]);
void encryptPlayfair(char formatted[], char keyTable[SIZE][SIZE], char encrypted[]);
void decryptPlayfair(char encrypted[], char keyTable[SIZE][SIZE], char decrypted[]);
void getLetterPosition(char keyTable[SIZE][SIZE], char letter, int *row, int *col);

int main() {
    char plaintext[MAX], formatted[MAX] = "";
    char encrypted[MAX] = "", decrypted[MAX] = "";

    char keyTable[SIZE][SIZE] = {
        {'A','B','C','D','E'},
        {'F','G','H','I','K'},
        {'L','M','N','O','P'},
        {'Q','R','S','T','U'},
        {'V','W','X','Y','Z'}
    };
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    formatPlaintext(plaintext, formatted);

    encryptPlayfair(formatted, keyTable, encrypted);
    printf("Encrypted Text: %s\n", encrypted);

    decryptPlayfair(encrypted, keyTable, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}

void formatPlaintext(char plaintext[], char formatted[]) {
    char temp[MAX] = "";
    int len = strlen(plaintext);
    int idx = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            if (ch == 'J')
                ch = 'I';
            temp[idx++] = ch;
        }
    }
    temp[idx] = '\0';

    int i = 0, j = 0;
    int tempLen = strlen(temp);
    while (i < tempLen) { 
        formatted[j++] = temp[i];
        if (i == tempLen - 1) {
            formatted[j++] = 'X';
            i++;
        } else {
            if (temp[i] == temp[i + 1]) {
                formatted[j++] = 'X';
                i++;  
            } else {       
                formatted[j++] = temp[i + 1];
                i += 2; 
            }
        }
    }
    formatted[j] = '\0';
}

void getLetterPosition(char keyTable[SIZE][SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPlayfair(char formatted[], char keyTable[SIZE][SIZE], char encrypted[]) {
    int len = strlen(formatted);
    int idx = 0;

    for (int i = 0; i < len; i += 2) {
        char a = formatted[i];
        char b = formatted[i+1];
        int row1, col1, row2, col2;
        getLetterPosition(keyTable, a, &row1, &col1);
        getLetterPosition(keyTable, b, &row2, &col2);

        if (row1 == row2) {
            encrypted[idx++] = keyTable[row1][(col1 + 1) % SIZE];
            encrypted[idx++] = keyTable[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encrypted[idx++] = keyTable[(row1 + 1) % SIZE][col1];
            encrypted[idx++] = keyTable[(row2 + 1) % SIZE][col2];
        } else {
            encrypted[idx++] = keyTable[row1][col2];
            encrypted[idx++] = keyTable[row2][col1];
        }
    }
    encrypted[idx] = '\0';
}

void decryptPlayfair(char encrypted[], char keyTable[SIZE][SIZE], char decrypted[]) {
    int len = strlen(encrypted);
    int idx = 0;

    for (int i = 0; i < len; i += 2) {
        char a = encrypted[i];
        char b = encrypted[i+1];
        int row1, col1, row2, col2;
        getLetterPosition(keyTable, a, &row1, &col1);
        getLetterPosition(keyTable, b, &row2, &col2);

        if (row1 == row2) {
            decrypted[idx++] = keyTable[row1][(col1 + SIZE - 1) % SIZE];
            decrypted[idx++] = keyTable[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            decrypted[idx++] = keyTable[(row1 + SIZE - 1) % SIZE][col1];
            decrypted[idx++] = keyTable[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            decrypted[idx++] = keyTable[row1][col2];
            decrypted[idx++] = keyTable[row2][col1];
        }
    }
    decrypted[idx] = '\0';
}
