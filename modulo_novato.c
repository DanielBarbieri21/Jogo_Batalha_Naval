#include <stdio.h>

#define TAM 5

// Inicializa o tabuleiro com água ('~')
void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for(int i = 0; i < TAM; i++) {
        for(int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = '~';
        }
    }
}

// Exibe o tabuleiro com índices de linhas e colunas
void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("  ");
    for(int i = 0; i < TAM; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for(int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for(int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona um navio em uma coordenada específica
void posicionarNavio(char tabuleiro[TAM][TAM], int linha, int coluna) {
    if(linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
        if(tabuleiro[linha][coluna] == '~') {
            tabuleiro[linha][coluna] = 'N';
            printf("Navio posicionado em (%d, %d)\n", linha, coluna);
        } else {
            printf("Posição já ocupada!\n");
        }
    } else {
        printf("Posição inválida!\n");
    }
}

int main() {
    char tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);
    
    // Posiciona 3 navios
    for(int i = 0; i < 3; i++) {
        int linha, coluna;
        printf("Digite a linha e a coluna para posicionar o navio %d: ", i+1);
        scanf("%d %d", &linha, &coluna);
        posicionarNavio(tabuleiro, linha, coluna);
        imprimirTabuleiro(tabuleiro);
    }
    
    return 0;
}