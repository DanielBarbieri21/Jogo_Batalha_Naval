/*
Módulo 1 – Novato
Jogo de Batalha Naval simples utilizando vetor unidimensional.
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

    SDL_Window* window = SDL_CreateWindow("Batalha Naval - Módulo Novato",
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

    // Vetor unidimensional representando o tabuleiro (100 células)
    // 0 = vazio; 1 = navio
    int tabuleiro[LINHAS * COLUNAS] = {0};
    // Posiciona um navio na célula (linha 4, coluna 5)
    int pos_navio = 4 * COLUNAS + 5;
    tabuleiro[pos_navio] = 1;

    bool rodando = true;
    SDL_Event evento;

    while (rodando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT)
                rodando = false;
        }
        
        // Limpa a tela com fundo branco
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Calcula tamanho de cada célula
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

        // Desenha o navio (célula colorida de azul)
        for (int i = 0; i < LINHAS * COLUNAS; i++) {
            if (tabuleiro[i] == 1) {
                int linha = i / COLUNAS;
                int coluna = i % COLUNAS;
                SDL_Rect rect = { coluna * cellWidth, linha * cellHeight, cellWidth, cellHeight };
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
