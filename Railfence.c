#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* railFenceEncrypt(const char *text, int rails) {
    int len = strlen(text);

    char **rail = malloc(rails * sizeof(char *));
    for (int i = 0; i < rails; i++) {
        rail[i] = malloc(len * sizeof(char));
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\n';
        }
    }

    int row = 0, dir = 1; 
    for (int col = 0; col < len; col++) {
        rail[row][col] = text[col];
        if (row == 0)
            dir = 1;
        else if (row == rails - 1)
            dir = -1;
        row += dir;
    }

    char *encrypted = malloc((len + 1) * sizeof(char));
    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                encrypted[index++] = rail[i][j];
    encrypted[index] = '\0';

    for (int i = 0; i < rails; i++)
        free(rail[i]);
    free(rail);
    
    return encrypted;
}

char* railFenceDecrypt(const char *cipher, int rails) {
    int len = strlen(cipher);

    char **rail = malloc(rails * sizeof(char *));
    for (int i = 0; i < rails; i++) {
        rail[i] = malloc(len * sizeof(char));
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\n'; 
        }
    }

    int row = 0, dir = 1;
    for (int col = 0; col < len; col++) {
        rail[row][col] = '*';
        if (row == 0)
            dir = 1;
        else if (row == rails - 1)
            dir = -1;
        row += dir;
    }

    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*' && index < len)
                rail[i][j] = cipher[index++];
    
    char *decrypted = malloc((len + 1) * sizeof(char));
    row = 0, dir = 1;
    index = 0;
    for (int col = 0; col < len; col++) {
        decrypted[index++] = rail[row][col];
        if (row == 0)
            dir = 1;
        else if (row == rails - 1)
            dir = -1;
        row += dir;
    }
    decrypted[index] = '\0';

    for (int i = 0; i < rails; i++)
        free(rail[i]);
    free(rail);
    
    return decrypted;
}

int main() {
    int rails;
    char message[1024];

    printf("Enter the number of rails: ");
    scanf("%d", &rails);
    getchar(); 

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n')
        message[len - 1] = '\0';

    char *encrypted = railFenceEncrypt(message, rails);
    printf("Encrypted message: %s\n", encrypted);

    char *decrypted = railFenceDecrypt(encrypted, rails);
    printf("Decrypted message: %s\n", decrypted);

    free(encrypted);
    free(decrypted);

    return 0;
}
