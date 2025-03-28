/*
Módulo 2 – Aventureiro
Jogo de Batalha Naval utilizando matriz (2D) para posicionar vários navios, inclusive em posições diagonais.
Biblioteca gráfica: SDL2
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define LARGURA_TELA 600
#define ALTURA_TELA 600
#define LINHAS 10
#define COLUNAS 10

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Batalha Naval - Módulo Aventureiro",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          LARGURA_TELA, ALTURA_TELA,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Matriz representando o tabuleiro
    // 0 = vazio; 1 = navio
    int tabuleiro[LINHAS][COLUNAS] = {0};
    
    // Posiciona alguns navios:
    // Navio horizontal
    tabuleiro[2][2] = 1;
    tabuleiro[2][3] = 1;
    tabuleiro[2][4] = 1;
    
    // Navio vertical
    tabuleiro[5][7] = 1;
    tabuleiro[6][7] = 1;
    tabuleiro[7][7] = 1;
    
    // Navio diagonal (cima-esquerda para baixo-direita)
    tabuleiro[0][0] = 1;
    tabuleiro[1][1] = 1;
    tabuleiro[2][2] = 1; // Pode sobrepor o já existente
    
    bool rodando = true;
    SDL_Event evento;
    
    while (rodando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT)
                rodando = false;
        }
        
        // Limpa a tela (fundo branco)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        int cellWidth = LARGURA_TELA / COLUNAS;
        int cellHeight = ALTURA_TELA / LINHAS;
        
        // Desenha o grid
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i <= LINHAS; i++) {
            SDL_RenderDrawLine(renderer, 0, i * cellHeight, LARGURA_TELA, i * cellHeight);
        }
        for (int j = 0; j <= COLUNAS; j++) {
            SDL_RenderDrawLine(renderer, j * cellWidth, 0, j * cellWidth, ALTURA_TELA);
        }
        
        // Desenha os navios (células coloridas em azul)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                if (tabuleiro[i][j] == 1) {
                    SDL_Rect rect = { j * cellWidth, i * cellHeight, cellWidth, cellHeight };
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
