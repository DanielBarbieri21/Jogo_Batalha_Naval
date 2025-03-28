/*
Módulo 3 – Mestre
Jogo de Batalha Naval com habilidades especiais.
Habilidades:
  1 - Cone (ex.: afeta células a partir do centro em forma de cone)
  2 - Cruz (ex.: afeta células vertical e horizontalmente)
  3 - Octaedro (ex.: afeta uma área mais ampla ao redor do centro)
Biblioteca gráfica: SDL2
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define LARGURA_TELA 600
#define ALTURA_TELA 600
#define LINHAS 10
#define COLUNAS 10

// Funções para desenhar áreas especiais
void desenhaCone(SDL_Renderer* renderer, int centroLinha, int centroColuna, int cellWidth, int cellHeight) {
    // Exemplo simples: desenha células à frente (para baixo) em forma de triângulo
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // vermelho
    for (int i = 1; i <= 3; i++) {
        for (int j = -i; j <= i; j++) {
            int linha = centroLinha + i;
            int coluna = centroColuna + j;
            if (linha >= 0 && linha < LINHAS && coluna >= 0 && coluna < COLUNAS) {
                SDL_Rect rect = { coluna * cellWidth, linha * cellHeight, cellWidth, cellHeight };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void desenhaCruz(SDL_Renderer* renderer, int centroLinha, int centroColuna, int cellWidth, int cellHeight) {
    // Desenha linhas vertical e horizontal a partir do centro
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // verde
    // Vertical
    for (int i = 0; i < LINHAS; i++) {
        SDL_Rect rect = { centroColuna * cellWidth, i * cellHeight, cellWidth, cellHeight };
        SDL_RenderFillRect(renderer, &rect);
    }
    // Horizontal
    for (int j = 0; j < COLUNAS; j++) {
        SDL_Rect rect = { j * cellWidth, centroLinha * cellHeight, cellWidth, cellHeight };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void desenhaOctaedro(SDL_Renderer* renderer, int centroLinha, int centroColuna, int cellWidth, int cellHeight) {
    // Exemplo simples: desenha um quadrado maior em volta do centro (3x3)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // azul
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int linha = centroLinha + i;
            int coluna = centroColuna + j;
            if (linha >= 0 && linha < LINHAS && coluna >= 0 && coluna < COLUNAS) {
                SDL_Rect rect = { coluna * cellWidth, linha * cellHeight, cellWidth, cellHeight };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Batalha Naval - Módulo Mestre",
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
    
    // Tabuleiro utilizando matriz 2D (poderia conter navios, mas aqui focamos nas habilidades)
    int tabuleiro[LINHAS][COLUNAS] = {0};
    
    // Define posição central para aplicar a habilidade (para demonstração)
    int centroLinha = 5;
    int centroColuna = 5;
    
    // Variável para armazenar a habilidade selecionada (0 = nenhuma)
    int habilidadeSelecionada = 0;
    
    bool rodando = true;
    SDL_Event evento;
    
    while (rodando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT)
                rodando = false;
            else if (evento.type == SDL_KEYDOWN) {
                // Pressione 1, 2 ou 3 para selecionar a habilidade
                switch (evento.key.keysym.sym) {
                    case SDLK_1:
                        habilidadeSelecionada = 1;
                        break;
                    case SDLK_2:
                        habilidadeSelecionada = 2;
                        break;
                    case SDLK_3:
                        habilidadeSelecionada = 3;
                        break;
                    default:
                        break;
                }
            }
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
        
        // (Opcional) Desenha navios já posicionados – aqui, por simplicidade, não adicionamos navios
        // Você pode colorir células específicas se desejar.
        
        // Aplica a habilidade especial selecionada
        switch (habilidadeSelecionada) {
            case 1:
                desenhaCone(renderer, centroLinha, centroColuna, cellWidth, cellHeight);
                break;
            case 2:
                desenhaCruz(renderer, centroLinha, centroColuna, cellWidth, cellHeight);
                break;
            case 3:
                desenhaOctaedro(renderer, centroLinha, centroColuna, cellWidth, cellHeight);
                break;
            default:
                break;
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
