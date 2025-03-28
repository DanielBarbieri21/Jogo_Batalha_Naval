#include <stdio.h>

#define TAM 10

// Inicializa o tabuleiro com água ('~')
void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for(int i = 0; i < TAM; i++) {
        for(int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = '~';
        }
    }
}

// Exibe o tabuleiro com índices alinhados
void imprimirTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("   ");
    for(int i = 0; i < TAM; i++) {
        printf("%2d ", i);
    }
    printf("\n");
    for(int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for(int j = 0; j < TAM; j++) {
            printf("%c  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Aplica a habilidade Cone (triângulo à direita)
void aplicarHabilidadeCone(char tabuleiro[TAM][TAM], int linha, int coluna) {
    for(int i = -1; i <= 1; i++) {
        for(int j = 0; j <= 2; j++) {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;
            if(novaLinha >= 0 && novaLinha < TAM && novaColuna >= 0 && novaColuna < TAM) {
                if(i == 0 || (i == -1 && j >= 1) || (i == 1 && j >= 1)) {
                    tabuleiro[novaLinha][novaColuna] = 'X';
                }
            }
        }
    }
}

// Aplica a habilidade Cruz (linhas horizontal e vertical)
void aplicarHabilidadeCruz(char tabuleiro[TAM][TAM], int linha, int coluna) {
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 || j == 0) {
                int novaLinha = linha + i;
                int novaColuna = coluna + j;
                if(novaLinha >= 0 && novaLinha < TAM && novaColuna >= 0 && novaColuna < TAM) {
                    tabuleiro[novaLinha][novaColuna] = 'X';
                }
            }
        }
    }
}

// Aplica a habilidade Octaedro (losango ao redor)
void aplicarHabilidadeOctaedro(char tabuleiro[TAM][TAM], int linha, int coluna) {
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(abs(i) + abs(j) <= 1) {
                int novaLinha = linha + i;
                int novaColuna = coluna + j;
                if(novaLinha >= 0 && novaLinha < TAM && novaColuna >= 0 && novaColuna < TAM) {
                    tabuleiro[novaLinha][novaColuna] = 'X';
                }
            }
        }
    }
}

int main() {
    char tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);
    
    char habilidade;
    int linha, coluna;
    printf("Escolha a habilidade (C para Cone, R para Cruz, O para Octaedro): ");
    scanf(" %c", &habilidade);
    printf("Digite a linha e a coluna para aplicar a habilidade: ");
    scanf("%d %d", &linha, &coluna);
    
    if(habilidade == 'C') {
        aplicarHabilidadeCone(tabuleiro, linha, coluna);
    } else if(habilidade == 'R') {
        aplicarHabilidadeCruz(tabuleiro, linha, coluna);
    } else if(habilidade == 'O') {
        aplicarHabilidadeOctaedro(tabuleiro, linha, coluna);
    } else {
        printf("Habilidade inválida!\n");
        return 1;
    }
    
    printf("Tabuleiro após a habilidade:\n");
    imprimirTabuleiro(tabuleiro);
    
    return 0;
}