#ifndef BATALHA_NAVAL_H
#define BATALHA_NAVAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Constantes do jogo
#define LARGURA_TELA 1200
#define ALTURA_TELA 800
#define TAMANHO_TABULEIRO 10
#define TAMANHO_CELULA 50
#define OFFSET_X 100
#define OFFSET_Y 100
#define ESPACAMENTO_TABULEIROS 50

// Cores do jogo
#define COR_AGUA 0x1E90FF
#define COR_NAVIO 0x8B4513
#define COR_ACERTO 0xFF0000
#define COR_ERRO 0x808080
#define COR_SELECAO 0xFFFF00
#define COR_FUNDO 0x2C3E50
#define COR_TEXTO 0xFFFFFF
#define COR_BOTAO 0x3498DB
#define COR_BOTAO_HOVER 0x2980B9

// Estados do jogo
typedef enum {
    MENU_PRINCIPAL,
    SELECAO_MODO,
    CONFIGURACAO_NAVIOS,
    JOGANDO,
    GAME_OVER,
    CONFIGURACOES,
    ESTATISTICAS
} EstadoJogo;

// Tipos de navio
typedef enum {
    SUBMARINO = 1,
    DESTROIER = 2,
    CRUZADOR = 3,
    ENCOURACADO = 4,
    PORTA_AVIOES = 5
} TipoNavio;

// Orientação dos navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_DIREITA,
    DIAGONAL_ESQUERDA
} Orientacao;

// Estrutura de um navio
typedef struct {
    int x, y;
    int tamanho;
    TipoNavio tipo;
    Orientacao orientacao;
    bool destruido;
    int acertos;
} Navio;

// Estrutura do tabuleiro
typedef struct {
    int grid[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Navio navios[10];
    int num_navios;
    int navios_destruidos;
} Tabuleiro;

// Estrutura do jogo
typedef struct {
    Tabuleiro jogador1;
    Tabuleiro jogador2;
    Tabuleiro* tabuleiro_atual;
    Tabuleiro* tabuleiro_inimigo;
    EstadoJogo estado;
    int jogador_atual;
    int turno;
    int pontuacao_jogador1;
    int pontuacao_jogador2;
    bool jogo_terminado;
    int x_selecionado, y_selecionado;
    bool navio_selecionado;
    int navio_para_posicionar;
    bool modo_ia;
    int dificuldade_ia;
} Jogo;

// Estrutura de botão
typedef struct {
    int x, y, largura, altura;
    char texto[50];
    bool hover;
    bool ativo;
    void (*acao)();
} Botao;

// Estrutura de fonte
typedef struct {
    TTF_Font* fonte_pequena;
    TTF_Font* fonte_media;
    TTF_Font* fonte_grande;
} Fontes;

// Estrutura de sons
typedef struct {
    Mix_Chunk* som_tiro;
    Mix_Chunk* som_acerto;
    Mix_Chunk* som_erro;
    Mix_Chunk* som_navio_destruido;
    Mix_Music* musica_fundo;
} Sons;

// Estrutura principal do jogo
typedef struct {
    SDL_Window* janela;
    SDL_Renderer* renderizador;
    Jogo jogo;
    Fontes fontes;
    Sons sons;
    Botao botoes[10];
    int num_botoes;
    bool rodando;
    int fps;
    Uint32 tempo_anterior;
} Aplicacao;

// Funções principais
Aplicacao* criar_aplicacao();
void destruir_aplicacao(Aplicacao* app);
bool inicializar_sdl();
bool carregar_recursos(Aplicacao* app);
void loop_principal(Aplicacao* app);

// Funções de renderização
void renderizar_menu_principal(Aplicacao* app);
void renderizar_tabuleiro(Aplicacao* app, Tabuleiro* tab, int x, int y, bool mostrar_navios);
void renderizar_navio(Aplicacao* app, Navio* navio, int x, int y);
void renderizar_interface_jogo(Aplicacao* app);
void renderizar_botoes(Aplicacao* app);
void renderizar_texto(Aplicacao* app, const char* texto, int x, int y, TTF_Font* fonte, SDL_Color cor);

// Funções de jogo
void inicializar_tabuleiro(Tabuleiro* tab);
bool posicionar_navio(Tabuleiro* tab, int x, int y, TipoNavio tipo, Orientacao orientacao);
bool atirar(Tabuleiro* tab, int x, int y);
bool verificar_vitoria(Tabuleiro* tab);
void processar_eventos(Aplicacao* app, SDL_Event* evento);
void atualizar_jogo(Aplicacao* app);

// Funções de IA
void jogada_ia(Tabuleiro* tab_inimigo, int dificuldade);
int avaliar_posicao(Tabuleiro* tab, int x, int y);

// Funções de utilidade
SDL_Color criar_cor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
bool ponto_em_retangulo(int x, int y, int rx, int ry, int largura, int altura);
void limpar_tela(SDL_Renderer* renderer);
void atualizar_fps(Aplicacao* app);

// Funções de configuração
void salvar_configuracao();
void carregar_configuracao();
void salvar_estatisticas();
void carregar_estatisticas();

#endif
