//
//  main.c
//  LCS
//
#include <stdio.h>
#include <stdlib.h>

// Definicion de funciones
int LCSFuerzaBruta(char A[], char B[], int i, int j);
int Max(int a, int b);
char* LCSDinamico(char A[], int n, char B[], int m);

int main(int argc, const char * argv[]) {
    
    char A[3] = {'b', 'd', '\0'};
    int n = 2;
    char B[5] = {'a', 'b', 'c', 'd', '\0'};
    int m = 4;
    
    int longitud;
    
    // Por fuerza bruta
    longitud = LCSFuerzaBruta(A, B, 0, 0);
    printf("Longitud %d\n", longitud);
    
    // Por programacion dinamica
    char *LCS = LCSDinamico(A, n, B, m);
    printf("LCS: %s\n", LCS);
    
    
    return 0;
}

// regresa la longitud del LCS
// Complejidad: O(2^n)
int LCSFuerzaBruta(char A[], char B[], int i, int j) {
    if(A[i] == '\0' || B[j] == '\0')
        return 0;
    else if(A[i] == A[j])
        return 1 + LCSFuerzaBruta(A, B, i + 1, j + 1);
    else
        return Max(LCSFuerzaBruta(A, B, i + 1, j), LCSFuerzaBruta(A, B, i, j + 1));
}

// regresa una cadena con el LCS
// Complejidad: O(n*m)
char* LCSDinamico(char A[], int n, char B[], int m) {
    int c[m+1][n+1]; // Arreglo que guarda las operaciones ya hechas
    int i,j;
    
    for(i = 0; i <= m; i++) {
        for(j = 0; j <= n; j++) {
            if(i == 0 || j == 0) {
                c[i][j] = 0;
            }else if(B[i-1] == A[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
            } else {
                c[i][j] = Max(c[i-1][j], c[i][j-1]);
            }
        }
    }
    
    
    // Longitud maxima del LCS
    printf("Longitud: %d\n", c[m][n]);
    
    // Obtiene LCS
    int col = m;
    int ren = n;
    int l = c[col][ren];
    
    //char LCS[l+1];
    char *LCS = (char*) malloc(sizeof(char)*(l+1));
    LCS[l] = '\0';
    
    while(col > 0 && ren > 0) {
        if(B[col - 1] == A[ren - 1]) {
            LCS[l-1] = B[col-1];
            
            l--;
            col --;
            ren --;
        } else if(c[col-1][ren] > c[col][ren-1]) {
            col --;
        } else {
            ren --;
        }
    }
    
    //printf("B: %s\n", B);
    //printf("A: %s\n", A);
    //printf("LCS: %s\n", LCS);
    
    return LCS;
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}


