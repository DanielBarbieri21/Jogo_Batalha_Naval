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

// Verifica se o navio pode ser posicionado
int podePosicionar(char tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char orientacao) {
    if(orientacao == 'H') {
        if(coluna + tamanho > TAM) return 0;
        for(int i = 0; i < tamanho; i++) {
            if(tabuleiro[linha][coluna + i] != '~') return 0;
        }
    } else if(orientacao == 'V') {
        if(linha + tamanho > TAM) return 0;
        for(int i = 0; i < tamanho; i++) {
            if(tabuleiro[linha + i][coluna] != '~') return 0;
        }
    } else if(orientacao == 'D') {
        if(linha + tamanho > TAM || coluna + tamanho > TAM) return 0;
        for(int i = 0; i < tamanho; i++) {
            if(tabuleiro[linha + i][coluna + i] != '~') return 0;
        }
    }
    return 1;
}

// Posiciona o navio conforme a orientação
void posicionarNavio(char tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char orientacao) {
    if(podePosicionar(tabuleiro, linha, coluna, tamanho, orientacao)) {
        if(orientacao == 'H') {
            for(int i = 0; i < tamanho; i++) {
                tabuleiro[linha][coluna + i] = 'N';
            }
        } else if(orientacao == 'V') {
            for(int i = 0; i < tamanho; i++) {
                tabuleiro[linha + i][coluna] = 'N';
            }
        } else if(orientacao == 'D') {
            for(int i = 0; i < tamanho; i++) {
                tabuleiro[linha + i][coluna + i] = 'N';
            }
        }
        printf("Navio posicionado com sucesso!\n");
    } else {
        printf("Não é possível posicionar o navio nessa posição!\n");
    }
}

int main() {
    char tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);
    printf("Tabuleiro inicial:\n");
    imprimirTabuleiro(tabuleiro);
    
    // Posiciona 2 navios de tamanho 3
    for(int i = 0; i < 2; i++) {
        int linha, coluna, tamanho = 3;
        char orientacao;
        printf("Digite a linha, coluna e orientação (H, V, D) para o navio %d: ", i+1);
        scanf("%d %d %c", &linha, &coluna, &orientacao);
        posicionarNavio(tabuleiro, linha, coluna, tamanho, orientacao);
        imprimirTabuleiro(tabuleiro);
    }
    
    return 0;
}