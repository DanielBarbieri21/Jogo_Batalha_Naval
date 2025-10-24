/*
 * Exemplo de uso do Batalha Naval - Versão Profissional
 * Desenvolvido por Daniel Barbieri Dev
 * 
 * Este arquivo demonstra como usar as principais funcionalidades
 * do sistema de Batalha Naval.
 */

#include "batalha_naval.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

// Função de exemplo para demonstrar o uso do sistema
void exemplo_uso_completo() {
    printf("=== EXEMPLO DE USO - BATALHA NAVAL ===\n\n");
    
    // 1. Criar aplicação
    printf("1. Criando aplicação...\n");
    Aplicacao* app = criar_aplicacao();
    if (!app) {
        printf("Erro ao criar aplicação!\n");
        return;
    }
    printf("✓ Aplicação criada com sucesso!\n\n");
    
    // 2. Configurar jogo
    printf("2. Configurando jogo...\n");
    app->jogo.estado = CONFIGURACAO_NAVIOS;
    app->jogo.modo_ia = false;
    app->jogo.dificuldade_ia = 2;
    printf("✓ Jogo configurado!\n\n");
    
    // 3. Posicionar navios
    printf("3. Posicionando navios...\n");
    Tabuleiro* tab = &app->jogo.jogador1;
    
    // Posicionar submarino
    if (posicionar_navio(tab, 2, 2, SUBMARINO, HORIZONTAL)) {
        printf("✓ Submarino posicionado em (2,2)\n");
    }
    
    // Posicionar destroier
    if (posicionar_navio(tab, 5, 5, DESTROIER, VERTICAL)) {
        printf("✓ Destroier posicionado em (5,5)\n");
    }
    
    // Posicionar cruzador
    if (posicionar_navio(tab, 1, 8, CRUZADOR, DIAGONAL_DIREITA)) {
        printf("✓ Cruzador posicionado em (1,8)\n");
    }
    
    printf("✓ Navios posicionados!\n\n");
    
    // 4. Simular jogo
    printf("4. Simulando jogo...\n");
    app->jogo.estado = JOGANDO;
    app->jogo.jogador_atual = 1;
    app->jogo.turno = 1;
    
    // Simular alguns tiros
    printf("Turno %d - Jogador %d atira em (2,2): ", app->jogo.turno, app->jogo.jogador_atual);
    if (atirar(&app->jogo.jogador2, 2, 2)) {
        printf("ACERTO!\n");
    } else {
        printf("ERRO!\n");
    }
    
    app->jogo.turno++;
    printf("Turno %d - Jogador %d atira em (5,5): ", app->jogo.turno, app->jogo.jogador_atual);
    if (atirar(&app->jogo.jogador2, 5, 5)) {
        printf("ACERTO!\n");
    } else {
        printf("ERRO!\n");
    }
    
    app->jogo.turno++;
    printf("Turno %d - Jogador %d atira em (1,8): ", app->jogo.turno, app->jogo.jogador_atual);
    if (atirar(&app->jogo.jogador2, 1, 8)) {
        printf("ACERTO!\n");
    } else {
        printf("ERRO!\n");
    }
    
    printf("✓ Jogo simulado!\n\n");
    
    // 5. Salvar jogo
    printf("5. Salvando jogo...\n");
    if (salvar_jogo(app, "exemplo.save")) {
        printf("✓ Jogo salvo em exemplo.save\n");
    } else {
        printf("✗ Erro ao salvar jogo\n");
    }
    printf("\n");
    
    // 6. Carregar jogo
    printf("6. Carregando jogo...\n");
    if (carregar_jogo(app, "exemplo.save")) {
        printf("✓ Jogo carregado de exemplo.save\n");
    } else {
        printf("✗ Erro ao carregar jogo\n");
    }
    printf("\n");
    
    // 7. Mostrar estatísticas
    printf("7. Estatísticas do jogo:\n");
    printf("   - Jogos jogados: %d\n", get_jogos_jogados());
    printf("   - Vitórias: %d\n", get_vitorias());
    printf("   - Derrotas: %d\n", get_derrotas());
    printf("   - Taxa de vitória: %.1f%%\n", calcular_taxa_vitoria());
    printf("   - Precisão: %.1f%%\n", calcular_precisao_tiros());
    printf("\n");
    
    // 8. Configurações
    printf("8. Configurações:\n");
    printf("   - Volume da música: %d%%\n", get_volume_musica());
    printf("   - Volume dos efeitos: %d%%\n", get_volume_efeitos());
    printf("   - Dificuldade da IA: %d\n", get_dificuldade_ia());
    printf("   - Som habilitado: %s\n", get_som_habilitado() ? "Sim" : "Não");
    printf("   - Música habilitada: %s\n", get_musica_habilitada() ? "Sim" : "Não");
    printf("\n");
    
    // 9. Limpar recursos
    printf("9. Limpando recursos...\n");
    destruir_aplicacao(app);
    printf("✓ Recursos limpos!\n\n");
    
    printf("=== EXEMPLO CONCLUÍDO ===\n");
}

// Função de exemplo para demonstrar IA
void exemplo_ia() {
    printf("=== EXEMPLO DE IA ===\n\n");
    
    // Criar aplicação
    Aplicacao* app = criar_aplicacao();
    if (!app) {
        printf("Erro ao criar aplicação!\n");
        return;
    }
    
    // Configurar para modo IA
    app->jogo.modo_ia = true;
    app->jogo.dificuldade_ia = 3; // Difícil
    
    printf("Configurando IA nível %d...\n", app->jogo.dificuldade_ia);
    
    // Posicionar navios do jogador
    Tabuleiro* tab_jogador = &app->jogo.jogador1;
    posicionar_navio(tab_jogador, 0, 0, SUBMARINO, HORIZONTAL);
    posicionar_navio(tab_jogador, 2, 2, DESTROIER, VERTICAL);
    posicionar_navio(tab_jogador, 5, 5, CRUZADOR, DIAGONAL_DIREITA);
    
    printf("Navios do jogador posicionados!\n");
    
    // Simular jogadas da IA
    printf("Simulando jogadas da IA...\n");
    for (int i = 0; i < 5; i++) {
        printf("IA joga: ");
        jogada_ia(tab_jogador, app->jogo.dificuldade_ia);
        printf("Turno %d concluído\n", i + 1);
    }
    
    // Limpar recursos
    destruir_aplicacao(app);
    printf("✓ Exemplo de IA concluído!\n\n");
}

// Função de exemplo para demonstrar save/load
void exemplo_save_load() {
    printf("=== EXEMPLO DE SAVE/LOAD ===\n\n");
    
    // Criar aplicação
    Aplicacao* app = criar_aplicacao();
    if (!app) {
        printf("Erro ao criar aplicação!\n");
        return;
    }
    
    // Configurar jogo
    app->jogo.estado = JOGANDO;
    app->jogo.turno = 5;
    app->jogo.jogador_atual = 1;
    
    // Posicionar navios
    Tabuleiro* tab = &app->jogo.jogador1;
    posicionar_navio(tab, 1, 1, SUBMARINO, HORIZONTAL);
    posicionar_navio(tab, 3, 3, DESTROIER, VERTICAL);
    
    printf("Jogo configurado - Turno %d, Jogador %d\n", app->jogo.turno, app->jogo.jogador_atual);
    
    // Salvar jogo
    printf("Salvando jogo...\n");
    if (salvar_jogo(app, "teste.save")) {
        printf("✓ Jogo salvo com sucesso!\n");
    } else {
        printf("✗ Erro ao salvar jogo!\n");
    }
    
    // Modificar estado
    app->jogo.turno = 10;
    app->jogo.jogador_atual = 2;
    printf("Estado modificado - Turno %d, Jogador %d\n", app->jogo.turno, app->jogo.jogador_atual);
    
    // Carregar jogo
    printf("Carregando jogo...\n");
    if (carregar_jogo(app, "teste.save")) {
        printf("✓ Jogo carregado com sucesso!\n");
        printf("Estado restaurado - Turno %d, Jogador %d\n", app->jogo.turno, app->jogo.jogador_atual);
    } else {
        printf("✗ Erro ao carregar jogo!\n");
    }
    
    // Limpar recursos
    destruir_aplicacao(app);
    printf("✓ Exemplo de save/load concluído!\n\n");
}

// Função principal
int main() {
    printf("🚢 BATALHA NAVAL - VERSÃO PROFISSIONAL\n");
    printf("Exemplos de uso do sistema\n");
    printf("Desenvolvido por Daniel Barbieri Dev\n\n");
    
    // Executar exemplos
    exemplo_uso_completo();
    exemplo_ia();
    exemplo_save_load();
    
    printf("=== TODOS OS EXEMPLOS CONCLUÍDOS ===\n");
    printf("Para compilar e executar o jogo completo, use:\n");
    printf("  make\n");
    printf("  make run\n\n");
    
    return 0;
}
