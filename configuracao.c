#include "batalha_naval.h"

// Estrutura de configurações
typedef struct {
    int volume_musica;
    int volume_efeitos;
    int dificuldade_ia;
    bool som_habilitado;
    bool musica_habilitada;
    bool tela_cheia;
    int resolucao_x;
    int resolucao_y;
} Configuracao;

static Configuracao config;
static bool config_carregada = false;

// Estrutura de estatísticas
typedef struct {
    int jogos_jogados;
    int vitorias;
    int derrotas;
    int empates;
    int tiros_acertados;
    int tiros_total;
    int navios_destruidos;
    int melhor_sequencia;
    int tempo_jogo_medio;
    int pontuacao_maxima;
} Estatisticas;

static Estatisticas stats;
static bool stats_carregadas = false;

// Inicializar configurações padrão
void inicializar_configuracao() {
    if (config_carregada) return;
    
    config.volume_musica = 70;
    config.volume_efeitos = 80;
    config.dificuldade_ia = 2;
    config.som_habilitado = true;
    config.musica_habilitada = true;
    config.tela_cheia = false;
    config.resolucao_x = LARGURA_TELA;
    config.resolucao_y = ALTURA_TELA;
    
    config_carregada = true;
}

// Inicializar estatísticas
void inicializar_estatisticas() {
    if (stats_carregadas) return;
    
    stats.jogos_jogados = 0;
    stats.vitorias = 0;
    stats.derrotas = 0;
    stats.empates = 0;
    stats.tiros_acertados = 0;
    stats.tiros_total = 0;
    stats.navios_destruidos = 0;
    stats.melhor_sequencia = 0;
    stats.tempo_jogo_medio = 0;
    stats.pontuacao_maxima = 0;
    
    stats_carregadas = true;
}

// Carregar configuração
void carregar_configuracao() {
    inicializar_configuracao();
    
    FILE* arquivo = fopen("config.dat", "rb");
    if (arquivo) {
        fread(&config, sizeof(Configuracao), 1, arquivo);
        fclose(arquivo);
    }
}

// Salvar configuração
void salvar_configuracao() {
    FILE* arquivo = fopen("config.dat", "wb");
    if (arquivo) {
        fwrite(&config, sizeof(Configuracao), 1, arquivo);
        fclose(arquivo);
    }
}

// Carregar estatísticas
void carregar_estatisticas() {
    inicializar_estatisticas();
    
    FILE* arquivo = fopen("stats.dat", "rb");
    if (arquivo) {
        fread(&stats, sizeof(Estatisticas), 1, arquivo);
        fclose(arquivo);
    }
}

// Salvar estatísticas
void salvar_estatisticas() {
    FILE* arquivo = fopen("stats.dat", "wb");
    if (arquivo) {
        fwrite(&stats, sizeof(Estatisticas), 1, arquivo);
        fclose(arquivo);
    }
}

// Getters e setters para configuração
int get_volume_musica() {
    carregar_configuracao();
    return config.volume_musica;
}

void set_volume_musica(int volume) {
    carregar_configuracao();
    config.volume_musica = volume;
    if (config.volume_musica < 0) config.volume_musica = 0;
    if (config.volume_musica > 100) config.volume_musica = 100;
    salvar_configuracao();
}

int get_volume_efeitos() {
    carregar_configuracao();
    return config.volume_efeitos;
}

void set_volume_efeitos(int volume) {
    carregar_configuracao();
    config.volume_efeitos = volume;
    if (config.volume_efeitos < 0) config.volume_efeitos = 0;
    if (config.volume_efeitos > 100) config.volume_efeitos = 100;
    salvar_configuracao();
}

int get_dificuldade_ia() {
    carregar_configuracao();
    return config.dificuldade_ia;
}

void set_dificuldade_ia(int dificuldade) {
    carregar_configuracao();
    config.dificuldade_ia = dificuldade;
    if (config.dificuldade_ia < 1) config.dificuldade_ia = 1;
    if (config.dificuldade_ia > 3) config.dificuldade_ia = 3;
    salvar_configuracao();
}

bool get_som_habilitado() {
    carregar_configuracao();
    return config.som_habilitado;
}

void set_som_habilitado(bool habilitado) {
    carregar_configuracao();
    config.som_habilitado = habilitado;
    salvar_configuracao();
}

bool get_musica_habilitada() {
    carregar_configuracao();
    return config.musica_habilitada;
}

void set_musica_habilitada(bool habilitada) {
    carregar_configuracao();
    config.musica_habilitada = habilitada;
    salvar_configuracao();
}

bool get_tela_cheia() {
    carregar_configuracao();
    return config.tela_cheia;
}

void set_tela_cheia(bool cheia) {
    carregar_configuracao();
    config.tela_cheia = cheia;
    salvar_configuracao();
}

// Getters para estatísticas
int get_jogos_jogados() {
    carregar_estatisticas();
    return stats.jogos_jogados;
}

int get_vitorias() {
    carregar_estatisticas();
    return stats.vitorias;
}

int get_derrotas() {
    carregar_estatisticas();
    return stats.derrotas;
}

int get_empates() {
    carregar_estatisticas();
    return stats.empates;
}

int get_tiros_acertados() {
    carregar_estatisticas();
    return stats.tiros_acertados;
}

int get_tiros_total() {
    carregar_estatisticas();
    return stats.tiros_total;
}

int get_navios_destruidos() {
    carregar_estatisticas();
    return stats.navios_destruidos;
}

int get_melhor_sequencia() {
    carregar_estatisticas();
    return stats.melhor_sequencia;
}

int get_tempo_jogo_medio() {
    carregar_estatisticas();
    return stats.tempo_jogo_medio;
}

int get_pontuacao_maxima() {
    carregar_estatisticas();
    return stats.pontuacao_maxima;
}

// Atualizar estatísticas
void atualizar_estatisticas_jogo(int vitoria, int tiros_acertados, int tiros_total, 
                                int navios_destruidos, int tempo_jogo) {
    carregar_estatisticas();
    
    stats.jogos_jogados++;
    stats.tiros_acertados += tiros_acertados;
    stats.tiros_total += tiros_total;
    stats.navios_destruidos += navios_destruidos;
    
    if (vitoria == 1) {
        stats.vitorias++;
    } else if (vitoria == -1) {
        stats.derrotas++;
    } else {
        stats.empates++;
    }
    
    // Atualizar tempo médio
    stats.tempo_jogo_medio = (stats.tempo_jogo_medio * (stats.jogos_jogados - 1) + tempo_jogo) / stats.jogos_jogados;
    
    // Atualizar pontuação máxima
    int pontuacao_atual = tiros_acertados * 10 + navios_destruidos * 50;
    if (pontuacao_atual > stats.pontuacao_maxima) {
        stats.pontuacao_maxima = pontuacao_atual;
    }
    
    salvar_estatisticas();
}

// Calcular taxa de vitória
float calcular_taxa_vitoria() {
    carregar_estatisticas();
    if (stats.jogos_jogados == 0) return 0.0f;
    return (float)stats.vitorias / stats.jogos_jogados * 100.0f;
}

// Calcular precisão de tiros
float calcular_precisao_tiros() {
    carregar_estatisticas();
    if (stats.tiros_total == 0) return 0.0f;
    return (float)stats.tiros_acertados / stats.tiros_total * 100.0f;
}

// Calcular navios destruídos por jogo
float calcular_navios_por_jogo() {
    carregar_estatisticas();
    if (stats.jogos_jogados == 0) return 0.0f;
    return (float)stats.navios_destruidos / stats.jogos_jogados;
}

// Resetar estatísticas
void resetar_estatisticas() {
    inicializar_estatisticas();
    salvar_estatisticas();
}

// Resetar configurações
void resetar_configuracao() {
    inicializar_configuracao();
    salvar_configuracao();
}

// Exportar estatísticas para arquivo de texto
void exportar_estatisticas(const char* nome_arquivo) {
    carregar_estatisticas();
    
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) return;
    
    fprintf(arquivo, "=== ESTATÍSTICAS DO JOGO BATALHA NAVAL ===\n\n");
    fprintf(arquivo, "Jogos Jogados: %d\n", stats.jogos_jogados);
    fprintf(arquivo, "Vitórias: %d\n", stats.vitorias);
    fprintf(arquivo, "Derrotas: %d\n", stats.derrotas);
    fprintf(arquivo, "Empates: %d\n", stats.empates);
    fprintf(arquivo, "Taxa de Vitória: %.1f%%\n", calcular_taxa_vitoria());
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Tiros Acertados: %d\n", stats.tiros_acertados);
    fprintf(arquivo, "Tiros Total: %d\n", stats.tiros_total);
    fprintf(arquivo, "Precisão: %.1f%%\n", calcular_precisao_tiros());
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Navios Destruídos: %d\n", stats.navios_destruidos);
    fprintf(arquivo, "Navios por Jogo: %.1f\n", calcular_navios_por_jogo());
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Melhor Sequência: %d\n", stats.melhor_sequencia);
    fprintf(arquivo, "Tempo Médio de Jogo: %d segundos\n", stats.tempo_jogo_medio);
    fprintf(arquivo, "Pontuação Máxima: %d\n", stats.pontuacao_maxima);
    
    fclose(arquivo);
}

// Importar estatísticas de arquivo
bool importar_estatisticas(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) return false;
    
    fread(&stats, sizeof(Estatisticas), 1, arquivo);
    fclose(arquivo);
    
    salvar_estatisticas();
    return true;
}

// Verificar se arquivo de configuração existe
bool configuracao_existe() {
    FILE* arquivo = fopen("config.dat", "rb");
    if (arquivo) {
        fclose(arquivo);
        return true;
    }
    return false;
}

// Verificar se arquivo de estatísticas existe
bool estatisticas_existem() {
    FILE* arquivo = fopen("stats.dat", "rb");
    if (arquivo) {
        fclose(arquivo);
        return true;
    }
    return false;
}

// Obter informações do sistema
void obter_info_sistema(char* info, int tamanho) {
    snprintf(info, tamanho, "Sistema: Windows 10\nSDL2: %s\nTTF: %s\nMixer: %s", 
             SDL_GetVersion()->major, TTF_GetVersion()->major, MIX_GetVersion()->major);
}

// Validar configuração
bool validar_configuracao() {
    carregar_configuracao();
    
    if (config.volume_musica < 0 || config.volume_musica > 100) return false;
    if (config.volume_efeitos < 0 || config.volume_efeitos > 100) return false;
    if (config.dificuldade_ia < 1 || config.dificuldade_ia > 3) return false;
    if (config.resolucao_x < 800 || config.resolucao_y < 600) return false;
    
    return true;
}

// Aplicar configurações ao jogo
void aplicar_configuracao(Aplicacao* app) {
    carregar_configuracao();
    
    // Aplicar volume
    if (app->sons.musica_fundo) {
        Mix_VolumeMusic(config.volume_musica);
    }
    
    // Aplicar resolução
    if (config.tela_cheia) {
        SDL_SetWindowFullscreen(app->janela, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(app->janela, 0);
        SDL_SetWindowSize(app->janela, config.resolucao_x, config.resolucao_y);
    }
}
