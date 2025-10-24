#include "batalha_naval.h"

// Função principal
int main(int argc, char* argv[]) {
    Aplicacao* app = criar_aplicacao();
    if (!app) {
        printf("Erro ao criar aplicação!\n");
        return 1;
    }
    
    loop_principal(app);
    destruir_aplicacao(app);
    return 0;
}

// Criar aplicação
Aplicacao* criar_aplicacao() {
    Aplicacao* app = malloc(sizeof(Aplicacao));
    if (!app) return NULL;
    
    memset(app, 0, sizeof(Aplicacao));
    
    if (!inicializar_sdl()) {
        free(app);
        return NULL;
    }
    
    app->janela = SDL_CreateWindow("Batalha Naval - Versão Profissional",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   LARGURA_TELA, ALTURA_TELA,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!app->janela) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        free(app);
        return NULL;
    }
    
    app->renderizador = SDL_CreateRenderer(app->janela, -1, 
                                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!app->renderizador) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->janela);
        free(app);
        return NULL;
    }
    
    if (!carregar_recursos(app)) {
        printf("Erro ao carregar recursos!\n");
        SDL_DestroyRenderer(app->renderizador);
        SDL_DestroyWindow(app->janela);
        free(app);
        return NULL;
    }
    
    // Inicializar jogo
    inicializar_tabuleiro(&app->jogo.jogador1);
    inicializar_tabuleiro(&app->jogo.jogador2);
    app->jogo.estado = MENU_PRINCIPAL;
    app->jogo.jogador_atual = 1;
    app->jogo.turno = 1;
    app->jogo.modo_ia = false;
    app->jogo.dificuldade_ia = 1;
    
    app->rodando = true;
    app->fps = 60;
    app->tempo_anterior = SDL_GetTicks();
    
    return app;
}

// Destruir aplicação
void destruir_aplicacao(Aplicacao* app) {
    if (!app) return;
    
    // Liberar fontes
    if (app->fontes.fonte_pequena) TTF_CloseFont(app->fontes.fonte_pequena);
    if (app->fontes.fonte_media) TTF_CloseFont(app->fontes.fonte_media);
    if (app->fontes.fonte_grande) TTF_CloseFont(app->fontes.fonte_grande);
    
    // Liberar sons
    if (app->sons.som_tiro) Mix_FreeChunk(app->sons.som_tiro);
    if (app->sons.som_acerto) Mix_FreeChunk(app->sons.som_acerto);
    if (app->sons.som_erro) Mix_FreeChunk(app->sons.som_erro);
    if (app->sons.som_navio_destruido) Mix_FreeChunk(app->sons.som_navio_destruido);
    if (app->sons.musica_fundo) Mix_FreeMusic(app->sons.musica_fundo);
    
    // Liberar SDL
    if (app->renderizador) SDL_DestroyRenderer(app->renderizador);
    if (app->janela) SDL_DestroyWindow(app->janela);
    
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    
    free(app);
}

// Inicializar SDL
bool inicializar_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return false;
    }
    
    if (TTF_Init() < 0) {
        printf("Erro ao inicializar TTF: %s\n", TTF_GetError());
        return false;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erro ao inicializar Mixer: %s\n", Mix_GetError());
        return false;
    }
    
    return true;
}

// Carregar recursos
bool carregar_recursos(Aplicacao* app) {
    // Carregar fontes (usando fontes do sistema como fallback)
    app->fontes.fonte_pequena = TTF_OpenFont("assets/fonts/arial.ttf", 16);
    if (!app->fontes.fonte_pequena) {
        app->fontes.fonte_pequena = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 16);
    }
    
    app->fontes.fonte_media = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (!app->fontes.fonte_media) {
        app->fontes.fonte_media = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
    }
    
    app->fontes.fonte_grande = TTF_OpenFont("assets/fonts/arial.ttf", 32);
    if (!app->fontes.fonte_grande) {
        app->fontes.fonte_grande = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
    }
    
    // Carregar sons (opcional - continuar sem sons se não encontrar)
    app->sons.som_tiro = Mix_LoadWAV("assets/sounds/shot.wav");
    app->sons.som_acerto = Mix_LoadWAV("assets/sounds/hit.wav");
    app->sons.som_erro = Mix_LoadWAV("assets/sounds/miss.wav");
    app->sons.som_navio_destruido = Mix_LoadWAV("assets/sounds/ship_destroyed.wav");
    app->sons.musica_fundo = Mix_LoadMUS("assets/music/background.mp3");
    
    return true;
}

// Loop principal
void loop_principal(Aplicacao* app) {
    SDL_Event evento;
    
    while (app->rodando) {
        // Processar eventos
        while (SDL_PollEvent(&evento)) {
            processar_eventos(app, &evento);
        }
        
        // Atualizar jogo
        atualizar_jogo(app);
        
        // Renderizar
        limpar_tela(app->renderizador);
        
        switch (app->jogo.estado) {
            case MENU_PRINCIPAL:
                renderizar_menu_principal(app);
                break;
            case SELECAO_MODO:
                renderizar_selecao_modo(app);
                break;
            case CONFIGURACAO_NAVIOS:
                renderizar_configuracao_navios(app);
                break;
            case JOGANDO:
                renderizar_jogo(app);
                break;
            case GAME_OVER:
                renderizar_game_over(app);
                break;
            case CONFIGURACOES:
                renderizar_configuracoes(app);
                break;
            case ESTATISTICAS:
                renderizar_estatisticas(app);
                break;
        }
        
        SDL_RenderPresent(app->renderizador);
        atualizar_fps(app);
    }
}

// Inicializar tabuleiro
void inicializar_tabuleiro(Tabuleiro* tab) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tab->grid[i][j] = 0;
        }
    }
    tab->num_navios = 0;
    tab->navios_destruidos = 0;
}

// Posicionar navio
bool posicionar_navio(Tabuleiro* tab, int x, int y, TipoNavio tipo, Orientacao orientacao) {
    if (tab->num_navios >= 10) return false;
    
    int tamanho = (int)tipo;
    Navio* navio = &tab->navios[tab->num_navios];
    
    navio->x = x;
    navio->y = y;
    navio->tamanho = tamanho;
    navio->tipo = tipo;
    navio->orientacao = orientacao;
    navio->destruido = false;
    navio->acertos = 0;
    
    // Verificar se pode posicionar
    for (int i = 0; i < tamanho; i++) {
        int nx = x, ny = y;
        
        switch (orientacao) {
            case HORIZONTAL:
                nx += i;
                break;
            case VERTICAL:
                ny += i;
                break;
            case DIAGONAL_DIREITA:
                nx += i;
                ny += i;
                break;
            case DIAGONAL_ESQUERDA:
                nx -= i;
                ny += i;
                break;
        }
        
        if (nx < 0 || nx >= TAMANHO_TABULEIRO || ny < 0 || ny >= TAMANHO_TABULEIRO) {
            return false;
        }
        
        if (tab->grid[ny][nx] != 0) {
            return false;
        }
    }
    
    // Posicionar navio
    for (int i = 0; i < tamanho; i++) {
        int nx = x, ny = y;
        
        switch (orientacao) {
            case HORIZONTAL:
                nx += i;
                break;
            case VERTICAL:
                ny += i;
                break;
            case DIAGONAL_DIREITA:
                nx += i;
                ny += i;
                break;
            case DIAGONAL_ESQUERDA:
                nx -= i;
                ny += i;
                break;
        }
        
        tab->grid[ny][nx] = tab->num_navios + 1;
    }
    
    tab->num_navios++;
    return true;
}

// Atirar
bool atirar(Tabuleiro* tab, int x, int y) {
    if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO) {
        return false;
    }
    
    int celula = tab->grid[y][x];
    
    if (celula == -1 || celula == -2) { // Já atirou aqui
        return false;
    }
    
    if (celula > 0) { // Acertou navio
        tab->grid[y][x] = -1; // Marcar como acerto
        Navio* navio = &tab->navios[celula - 1];
        navio->acertos++;
        
        if (navio->acertos >= navio->tamanho) {
            navio->destruido = true;
            tab->navios_destruidos++;
        }
        return true;
    } else { // Errou
        tab->grid[y][x] = -2; // Marcar como erro
        return false;
    }
}

// Verificar vitória
bool verificar_vitoria(Tabuleiro* tab) {
    return tab->navios_destruidos >= tab->num_navios;
}

// Processar eventos
void processar_eventos(Aplicacao* app, SDL_Event* evento) {
    switch (evento->type) {
        case SDL_QUIT:
            app->rodando = false;
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            if (evento->button.button == SDL_BUTTON_LEFT) {
                int mouse_x = evento->button.x;
                int mouse_y = evento->button.y;
                
                // Processar cliques em botões
                for (int i = 0; i < app->num_botoes; i++) {
                    if (ponto_em_retangulo(mouse_x, mouse_y, 
                                         app->botoes[i].x, app->botoes[i].y,
                                         app->botoes[i].largura, app->botoes[i].altura)) {
                        if (app->botoes[i].acao) {
                            app->botoes[i].acao();
                        }
                    }
                }
            }
            break;
            
        case SDL_KEYDOWN:
            switch (evento->key.keysym.sym) {
                case SDLK_ESCAPE:
                    if (app->jogo.estado == JOGANDO) {
                        app->jogo.estado = MENU_PRINCIPAL;
                    } else {
                        app->rodando = false;
                    }
                    break;
                case SDLK_F11:
                    // Toggle fullscreen
                    break;
            }
            break;
    }
}

// Atualizar jogo
void atualizar_jogo(Aplicacao* app) {
    // Lógica de atualização do jogo
    if (app->jogo.estado == JOGANDO && app->jogo.modo_ia && app->jogo.jogador_atual == 2) {
        // IA joga
        jogada_ia(&app->jogo.jogador1, app->jogo.dificuldade_ia);
        app->jogo.jogador_atual = 1;
        app->jogo.turno++;
    }
}

// Limpar tela
void limpar_tela(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0x2C, 0x3E, 0x50, 255);
    SDL_RenderClear(renderer);
}

// Atualizar FPS
void atualizar_fps(Aplicacao* app) {
    Uint32 tempo_atual = SDL_GetTicks();
    Uint32 delta = tempo_atual - app->tempo_anterior;
    
    if (delta < 1000 / app->fps) {
        SDL_Delay(1000 / app->fps - delta);
    }
    
    app->tempo_anterior = SDL_GetTicks();
}

// Criar cor
SDL_Color criar_cor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_Color cor;
    cor.r = r;
    cor.g = g;
    cor.b = b;
    cor.a = a;
    return cor;
}

// Verificar se ponto está em retângulo
bool ponto_em_retangulo(int x, int y, int rx, int ry, int largura, int altura) {
    return x >= rx && x < rx + largura && y >= ry && y < ry + altura;
}
