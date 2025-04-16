#include <stdio.h>

int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;  
    while (exp > 0) {
        if (exp % 2 == 1)  
            result = (result * base) % mod;
        exp = exp >> 1;    
        base = (base * base) % mod; 
    }
    return result;
}

int main() {
    int p = 23;  
    int g = 5;   

    int a, b;    

    printf("Enter Alice's private key (a): ");
    scanf("%d", &a);
    printf("Enter Bob's private key (b): ");
    scanf("%d", &b);

    int A = mod_exp(g, a, p);  
    int B = mod_exp(g, b, p); 
\
    int secretA = mod_exp(B, a, p);  
    int secretB = mod_exp(A, b, p);

    printf("\nPublic parameters: p = %d, g = %d\n", p, g);
    printf("Alice's private key: %d\n", a);
    printf("Bob's private key: %d\n", b);
    printf("Alice's public key (A): %d\n", A);
    printf("Bob's public key (B): %d\n", B);
    printf("Alice's computed shared secret: %d\n", secretA);
    printf("Bob's computed shared secret: %d\n", secretB);

    if (secretA == secretB) {
        printf("Shared secret established successfully: %d\n", secretA);
    } else {
        printf("Error: Shared secrets do not match!\n");
    }

    return 0;
}
