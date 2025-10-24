#include "batalha_naval.h"

// Renderizar menu principal
void renderizar_menu_principal(Aplicacao* app) {
    // Título
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    renderizar_texto(app, "BATALHA NAVAL", LARGURA_TELA/2 - 150, 100, 
                   app->fontes.fonte_grande, cor_titulo);
    
    // Subtítulo
    SDL_Color cor_subtitulo = criar_cor(200, 200, 200, 255);
    renderizar_texto(app, "Versão Profissional", LARGURA_TELA/2 - 100, 150, 
                   app->fontes.fonte_media, cor_subtitulo);
    
    // Botões do menu
    app->num_botoes = 0;
    
    // Botão Jogar
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 250;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "JOGAR");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    // Botão Configurações
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 320;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "CONFIGURAÇÕES");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    // Botão Estatísticas
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 390;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "ESTATÍSTICAS");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    // Botão Sair
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 460;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "SAIR");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar seleção de modo
void renderizar_selecao_modo(Aplicacao* app) {
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    renderizar_texto(app, "SELECIONE O MODO DE JOGO", LARGURA_TELA/2 - 200, 100, 
                   app->fontes.fonte_grande, cor_titulo);
    
    app->num_botoes = 0;
    
    // Botão 2 Jogadores
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 150;
    app->botoes[app->num_botoes].y = 200;
    app->botoes[app->num_botoes].largura = 300;
    app->botoes[app->num_botoes].altura = 60;
    strcpy(app->botoes[app->num_botoes].texto, "2 JOGADORES");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    // Botão vs IA
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 150;
    app->botoes[app->num_botoes].y = 280;
    app->botoes[app->num_botoes].largura = 300;
    app->botoes[app->num_botoes].altura = 60;
    strcpy(app->botoes[app->num_botoes].texto, "VS INTELIGÊNCIA ARTIFICIAL");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    // Botão Voltar
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 500;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "VOLTAR");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar configuração de navios
void renderizar_configuracao_navios(Aplicacao* app) {
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    char titulo[100];
    sprintf(titulo, "CONFIGURAÇÃO - JOGADOR %d", app->jogo.jogador_atual);
    renderizar_texto(app, titulo, LARGURA_TELA/2 - 150, 50, 
                   app->fontes.fonte_grande, cor_titulo);
    
    // Renderizar tabuleiro do jogador atual
    renderizar_tabuleiro(app, &app->jogo.jogador1, OFFSET_X, OFFSET_Y, true);
    
    // Instruções
    SDL_Color cor_instrucao = criar_cor(200, 200, 200, 255);
    renderizar_texto(app, "Clique para posicionar navios", OFFSET_X, OFFSET_Y - 30, 
                   app->fontes.fonte_pequena, cor_instrucao);
    
    // Botões de controle
    app->num_botoes = 0;
    
    // Botão Próximo
    app->botoes[app->num_botoes].x = LARGURA_TELA - 200;
    app->botoes[app->num_botoes].y = ALTURA_TELA - 100;
    app->botoes[app->num_botoes].largura = 150;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "PRÓXIMO");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar jogo
void renderizar_jogo(Aplicacao* app) {
    // Título do turno
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    char titulo[100];
    sprintf(titulo, "TURNO %d - JOGADOR %d", app->jogo.turno, app->jogo.jogador_atual);
    renderizar_texto(app, titulo, LARGURA_TELA/2 - 150, 30, 
                   app->fontes.fonte_media, cor_titulo);
    
    // Renderizar tabuleiros
    int x1 = OFFSET_X;
    int x2 = x1 + TAMANHO_TABULEIRO * TAMANHO_CELULA + ESPACAMENTO_TABULEIROS;
    
    // Tabuleiro do jogador atual (mostrar navios)
    SDL_Color cor_label = criar_cor(200, 200, 200, 255);
    renderizar_texto(app, "SEU TABULEIRO", x1, x1 - 30, 
                   app->fontes.fonte_pequena, cor_label);
    renderizar_tabuleiro(app, &app->jogo.jogador1, x1, OFFSET_Y, true);
    
    // Tabuleiro do inimigo (não mostrar navios)
    renderizar_texto(app, "TABULEIRO INIMIGO", x2, x2 - 30, 
                   app->fontes.fonte_pequena, cor_label);
    renderizar_tabuleiro(app, &app->jogo.jogador2, x2, OFFSET_Y, false);
    
    // Botões de controle
    app->num_botoes = 0;
    
    // Botão Menu
    app->botoes[app->num_botoes].x = 50;
    app->botoes[app->num_botoes].y = ALTURA_TELA - 100;
    app->botoes[app->num_botoes].largura = 100;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "MENU");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar game over
void renderizar_game_over(Aplicacao* app) {
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    char titulo[100];
    sprintf(titulo, "JOGADOR %d VENCEU!", app->jogo.jogador_atual);
    renderizar_texto(app, titulo, LARGURA_TELA/2 - 150, 200, 
                   app->fontes.fonte_grande, cor_titulo);
    
    // Botões
    app->num_botoes = 0;
    
    // Botão Jogar Novamente
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 150;
    app->botoes[app->num_botoes].y = 350;
    app->botoes[app->num_botoes].largura = 300;
    app->botoes[app->num_botoes].altura = 60;
    strcpy(app->botoes[app->num_botoes].texto, "JOGAR NOVAMENTE");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    // Botão Menu
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 430;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "MENU PRINCIPAL");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar configurações
void renderizar_configuracoes(Aplicacao* app) {
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    renderizar_texto(app, "CONFIGURAÇÕES", LARGURA_TELA/2 - 100, 100, 
                   app->fontes.fonte_grande, cor_titulo);
    
    // Opções de configuração
    SDL_Color cor_texto = criar_cor(200, 200, 200, 255);
    renderizar_texto(app, "Volume da Música:", 200, 200, 
                   app->fontes.fonte_media, cor_texto);
    renderizar_texto(app, "Volume dos Efeitos:", 200, 250, 
                   app->fontes.fonte_media, cor_texto);
    renderizar_texto(app, "Dificuldade da IA:", 200, 300, 
                   app->fontes.fonte_media, cor_texto);
    
    // Botões
    app->num_botoes = 0;
    
    // Botão Voltar
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 500;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "VOLTAR");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar estatísticas
void renderizar_estatisticas(Aplicacao* app) {
    SDL_Color cor_titulo = criar_cor(255, 255, 255, 255);
    renderizar_texto(app, "ESTATÍSTICAS", LARGURA_TELA/2 - 100, 100, 
                   app->fontes.fonte_grande, cor_titulo);
    
    // Estatísticas
    SDL_Color cor_texto = criar_cor(200, 200, 200, 255);
    renderizar_texto(app, "Jogos Jogados: 0", 200, 200, 
                   app->fontes.fonte_media, cor_texto);
    renderizar_texto(app, "Vitórias: 0", 200, 250, 
                   app->fontes.fonte_media, cor_texto);
    renderizar_texto(app, "Derrotas: 0", 200, 300, 
                   app->fontes.fonte_media, cor_texto);
    renderizar_texto(app, "Taxa de Vitória: 0%", 200, 350, 
                   app->fontes.fonte_media, cor_texto);
    
    // Botões
    app->num_botoes = 0;
    
    // Botão Voltar
    app->botoes[app->num_botoes].x = LARGURA_TELA/2 - 100;
    app->botoes[app->num_botoes].y = 500;
    app->botoes[app->num_botoes].largura = 200;
    app->botoes[app->num_botoes].altura = 50;
    strcpy(app->botoes[app->num_botoes].texto, "VOLTAR");
    app->botoes[app->num_botoes].ativo = true;
    app->num_botoes++;
    
    renderizar_botoes(app);
}

// Renderizar tabuleiro
void renderizar_tabuleiro(Aplicacao* app, Tabuleiro* tab, int x, int y, bool mostrar_navios) {
    // Desenhar grid
    SDL_SetRenderDrawColor(app->renderizador, 100, 100, 100, 255);
    
    // Linhas horizontais
    for (int i = 0; i <= TAMANHO_TABULEIRO; i++) {
        SDL_RenderDrawLine(app->renderizador, 
                          x, y + i * TAMANHO_CELULA,
                          x + TAMANHO_TABULEIRO * TAMANHO_CELULA, y + i * TAMANHO_CELULA);
    }
    
    // Linhas verticais
    for (int i = 0; i <= TAMANHO_TABULEIRO; i++) {
        SDL_RenderDrawLine(app->renderizador, 
                          x + i * TAMANHO_CELULA, y,
                          x + i * TAMANHO_CELULA, y + TAMANHO_TABULEIRO * TAMANHO_CELULA);
    }
    
    // Desenhar células
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            int celula = tab->grid[i][j];
            SDL_Rect rect = {x + j * TAMANHO_CELULA + 1, y + i * TAMANHO_CELULA + 1, 
                           TAMANHO_CELULA - 2, TAMANHO_CELULA - 2};
            
            if (celula == -1) { // Acerto
                SDL_SetRenderDrawColor(app->renderizador, 255, 0, 0, 255);
                SDL_RenderFillRect(app->renderizador, &rect);
            } else if (celula == -2) { // Erro
                SDL_SetRenderDrawColor(app->renderizador, 128, 128, 128, 255);
                SDL_RenderFillRect(app->renderizador, &rect);
            } else if (celula > 0 && mostrar_navios) { // Navio
                SDL_SetRenderDrawColor(app->renderizador, 139, 69, 19, 255);
                SDL_RenderFillRect(app->renderizador, &rect);
            } else { // Água
                SDL_SetRenderDrawColor(app->renderizador, 30, 144, 255, 255);
                SDL_RenderFillRect(app->renderizador, &rect);
            }
        }
    }
}

// Renderizar navio
void renderizar_navio(Aplicacao* app, Navio* navio, int x, int y) {
    SDL_SetRenderDrawColor(app->renderizador, 139, 69, 19, 255);
    
    for (int i = 0; i < navio->tamanho; i++) {
        int nx = x, ny = y;
        
        switch (navio->orientacao) {
            case HORIZONTAL:
                nx += i * TAMANHO_CELULA;
                break;
            case VERTICAL:
                ny += i * TAMANHO_CELULA;
                break;
            case DIAGONAL_DIREITA:
                nx += i * TAMANHO_CELULA;
                ny += i * TAMANHO_CELULA;
                break;
            case DIAGONAL_ESQUERDA:
                nx -= i * TAMANHO_CELULA;
                ny += i * TAMANHO_CELULA;
                break;
        }
        
        SDL_Rect rect = {nx, ny, TAMANHO_CELULA, TAMANHO_CELULA};
        SDL_RenderFillRect(app->renderizador, &rect);
    }
}

// Renderizar interface do jogo
void renderizar_interface_jogo(Aplicacao* app) {
    // Renderizar informações do jogo
    SDL_Color cor_info = criar_cor(255, 255, 255, 255);
    char info[100];
    sprintf(info, "Turno: %d | Jogador: %d", app->jogo.turno, app->jogo.jogador_atual);
    renderizar_texto(app, info, 50, 50, app->fontes.fonte_pequena, cor_info);
}

// Renderizar botões
void renderizar_botoes(Aplicacao* app) {
    for (int i = 0; i < app->num_botoes; i++) {
        Botao* botao = &app->botoes[i];
        
        if (!botao->ativo) continue;
        
        // Cor do botão
        if (botao->hover) {
            SDL_SetRenderDrawColor(app->renderizador, 52, 152, 219, 255);
        } else {
            SDL_SetRenderDrawColor(app->renderizador, 41, 128, 185, 255);
        }
        
        // Desenhar botão
        SDL_Rect rect = {botao->x, botao->y, botao->largura, botao->altura};
        SDL_RenderFillRect(app->renderizador, &rect);
        
        // Borda
        SDL_SetRenderDrawColor(app->renderizador, 255, 255, 255, 255);
        SDL_RenderDrawRect(app->renderizador, &rect);
        
        // Texto do botão
        SDL_Color cor_texto = criar_cor(255, 255, 255, 255);
        renderizar_texto(app, botao->texto, 
                        botao->x + botao->largura/2 - strlen(botao->texto) * 6, 
                        botao->y + botao->altura/2 - 10, 
                        app->fontes.fonte_pequena, cor_texto);
    }
}

// Renderizar texto
void renderizar_texto(Aplicacao* app, const char* texto, int x, int y, TTF_Font* fonte, SDL_Color cor) {
    if (!fonte) return;
    
    SDL_Surface* superficie = TTF_RenderText_Solid(fonte, texto, cor);
    if (!superficie) return;
    
    SDL_Texture* textura = SDL_CreateTextureFromSurface(app->renderizador, superficie);
    if (!textura) {
        SDL_FreeSurface(superficie);
        return;
    }
    
    SDL_Rect dest = {x, y, superficie->w, superficie->h};
    SDL_RenderCopy(app->renderizador, textura, NULL, &dest);
    
    SDL_DestroyTexture(textura);
    SDL_FreeSurface(superficie);
}
