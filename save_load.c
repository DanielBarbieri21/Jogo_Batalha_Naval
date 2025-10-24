#include "batalha_naval.h"

// Estrutura para salvar o estado do jogo
typedef struct {
    Tabuleiro jogador1;
    Tabuleiro jogador2;
    int jogador_atual;
    int turno;
    int pontuacao_jogador1;
    int pontuacao_jogador2;
    bool jogo_terminado;
    bool modo_ia;
    int dificuldade_ia;
    time_t timestamp;
    char nome_jogo[50];
} EstadoJogo;

// Salvar jogo
bool salvar_jogo(Aplicacao* app, const char* nome_arquivo) {
    EstadoJogo estado;
    
    // Copiar dados do jogo
    estado.jogador1 = app->jogo.jogador1;
    estado.jogador2 = app->jogo.jogador2;
    estado.jogador_atual = app->jogo.jogador_atual;
    estado.turno = app->jogo.turno;
    estado.pontuacao_jogador1 = app->jogo.pontuacao_jogador1;
    estado.pontuacao_jogador2 = app->jogo.pontuacao_jogador2;
    estado.jogo_terminado = app->jogo.jogo_terminado;
    estado.modo_ia = app->jogo.modo_ia;
    estado.dificuldade_ia = app->jogo.dificuldade_ia;
    estado.timestamp = time(NULL);
    strncpy(estado.nome_jogo, nome_arquivo, sizeof(estado.nome_jogo) - 1);
    estado.nome_jogo[sizeof(estado.nome_jogo) - 1] = '\0';
    
    // Salvar em arquivo
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        printf("Erro ao criar arquivo de save: %s\n", nome_arquivo);
        return false;
    }
    
    size_t bytes_escritos = fwrite(&estado, sizeof(EstadoJogo), 1, arquivo);
    fclose(arquivo);
    
    if (bytes_escritos != 1) {
        printf("Erro ao escrever dados do jogo\n");
        return false;
    }
    
    printf("Jogo salvo com sucesso: %s\n", nome_arquivo);
    return true;
}

// Carregar jogo
bool carregar_jogo(Aplicacao* app, const char* nome_arquivo) {
    EstadoJogo estado;
    
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de save: %s\n", nome_arquivo);
        return false;
    }
    
    size_t bytes_lidos = fread(&estado, sizeof(EstadoJogo), 1, arquivo);
    fclose(arquivo);
    
    if (bytes_lidos != 1) {
        printf("Erro ao ler dados do jogo\n");
        return false;
    }
    
    // Restaurar dados do jogo
    app->jogo.jogador1 = estado.jogador1;
    app->jogo.jogador2 = estado.jogador2;
    app->jogo.jogador_atual = estado.jogador_atual;
    app->jogo.turno = estado.turno;
    app->jogo.pontuacao_jogador1 = estado.pontuacao_jogador1;
    app->jogo.pontuacao_jogador2 = estado.pontuacao_jogador2;
    app->jogo.jogo_terminado = estado.jogo_terminado;
    app->jogo.modo_ia = estado.modo_ia;
    app->jogo.dificuldade_ia = estado.dificuldade_ia;
    
    printf("Jogo carregado com sucesso: %s\n", nome_arquivo);
    return true;
}

// Listar jogos salvos
int listar_jogos_salvos(char jogos[][50], int max_jogos) {
    int count = 0;
    DIR* diretorio = opendir(".");
    if (!diretorio) return 0;
    
    struct dirent* entrada;
    while ((entrada = readdir(diretorio)) != NULL && count < max_jogos) {
        if (strstr(entrada->d_name, ".save") != NULL) {
            strncpy(jogos[count], entrada->d_name, 49);
            jogos[count][49] = '\0';
            count++;
        }
    }
    
    closedir(diretorio);
    return count;
}

// Verificar se arquivo de save existe
bool save_existe(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (arquivo) {
        fclose(arquivo);
        return true;
    }
    return false;
}

// Obter informações do save
bool obter_info_save(const char* nome_arquivo, char* info, int tamanho) {
    EstadoJogo estado;
    
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) return false;
    
    size_t bytes_lidos = fread(&estado, sizeof(EstadoJogo), 1, arquivo);
    fclose(arquivo);
    
    if (bytes_lidos != 1) return false;
    
    // Formatar informações
    struct tm* tempo_info = localtime(&estado.timestamp);
    char data_str[50];
    strftime(data_str, sizeof(data_str), "%d/%m/%Y %H:%M", tempo_info);
    
    snprintf(info, tamanho, 
             "Nome: %s\n"
             "Data: %s\n"
             "Turno: %d\n"
             "Jogador: %d\n"
             "Modo: %s\n"
             "Pontuação J1: %d\n"
             "Pontuação J2: %d",
             estado.nome_jogo,
             data_str,
             estado.turno,
             estado.jogador_atual,
             estado.modo_ia ? "vs IA" : "2 Jogadores",
             estado.pontuacao_jogador1,
             estado.pontuacao_jogador2);
    
    return true;
}

// Deletar save
bool deletar_save(const char* nome_arquivo) {
    if (remove(nome_arquivo) == 0) {
        printf("Save deletado: %s\n", nome_arquivo);
        return true;
    }
    return false;
}

// Auto-save
bool auto_save(Aplicacao* app) {
    char nome_arquivo[100];
    time_t agora = time(NULL);
    struct tm* tempo_info = localtime(&agora);
    
    strftime(nome_arquivo, sizeof(nome_arquivo), "autosave_%Y%m%d_%H%M%S.save", tempo_info);
    
    return salvar_jogo(app, nome_arquivo);
}

// Carregar auto-save mais recente
bool carregar_auto_save(Aplicacao* app) {
    char jogos[10][50];
    int num_jogos = listar_jogos_salvos(jogos, 10);
    
    if (num_jogos == 0) return false;
    
    // Procurar pelo auto-save mais recente
    char auto_save_mais_recente[50] = "";
    time_t tempo_mais_recente = 0;
    
    for (int i = 0; i < num_jogos; i++) {
        if (strstr(jogos[i], "autosave_") != NULL) {
            struct stat info_arquivo;
            if (stat(jogos[i], &info_arquivo) == 0) {
                if (info_arquivo.st_mtime > tempo_mais_recente) {
                    tempo_mais_recente = info_arquivo.st_mtime;
                    strcpy(auto_save_mais_recente, jogos[i]);
                }
            }
        }
    }
    
    if (strlen(auto_save_mais_recente) > 0) {
        return carregar_jogo(app, auto_save_mais_recente);
    }
    
    return false;
}

// Limpar auto-saves antigos
void limpar_auto_saves_antigos(int dias_para_manter) {
    char jogos[50][50];
    int num_jogos = listar_jogos_salvos(jogos, 50);
    time_t agora = time(NULL);
    time_t limite = agora - (dias_para_manter * 24 * 60 * 60);
    
    for (int i = 0; i < num_jogos; i++) {
        if (strstr(jogos[i], "autosave_") != NULL) {
            struct stat info_arquivo;
            if (stat(jogos[i], &info_arquivo) == 0) {
                if (info_arquivo.st_mtime < limite) {
                    remove(jogos[i]);
                    printf("Auto-save antigo removido: %s\n", jogos[i]);
                }
            }
        }
    }
}

// Exportar save para arquivo de texto
bool exportar_save_texto(const char* nome_arquivo, const char* arquivo_texto) {
    EstadoJogo estado;
    
    FILE* arquivo_bin = fopen(nome_arquivo, "rb");
    if (!arquivo_bin) return false;
    
    fread(&estado, sizeof(EstadoJogo), 1, arquivo_bin);
    fclose(arquivo_bin);
    
    FILE* arquivo_txt = fopen(arquivo_texto, "w");
    if (!arquivo_txt) return false;
    
    fprintf(arquivo_txt, "=== SAVE DO JOGO BATALHA NAVAL ===\n\n");
    fprintf(arquivo_txt, "Nome: %s\n", estado.nome_jogo);
    fprintf(arquivo_txt, "Data: %s", ctime(&estado.timestamp));
    fprintf(arquivo_txt, "Turno: %d\n", estado.turno);
    fprintf(arquivo_txt, "Jogador Atual: %d\n", estado.jogador_atual);
    fprintf(arquivo_txt, "Modo IA: %s\n", estado.modo_ia ? "Sim" : "Não");
    fprintf(arquivo_txt, "Dificuldade IA: %d\n", estado.dificuldade_ia);
    fprintf(arquivo_txt, "Pontuação J1: %d\n", estado.pontuacao_jogador1);
    fprintf(arquivo_txt, "Pontuação J2: %d\n", estado.pontuacao_jogador2);
    fprintf(arquivo_txt, "Jogo Terminado: %s\n\n", estado.jogo_terminado ? "Sim" : "Não");
    
    // Tabuleiro do jogador 1
    fprintf(arquivo_txt, "=== TABULEIRO JOGADOR 1 ===\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            fprintf(arquivo_txt, "%2d ", estado.jogador1.grid[i][j]);
        }
        fprintf(arquivo_txt, "\n");
    }
    
    fprintf(arquivo_txt, "\n=== TABULEIRO JOGADOR 2 ===\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            fprintf(arquivo_txt, "%2d ", estado.jogador2.grid[i][j]);
        }
        fprintf(arquivo_txt, "\n");
    }
    
    fclose(arquivo_txt);
    return true;
}

// Validar arquivo de save
bool validar_save(const char* nome_arquivo) {
    EstadoJogo estado;
    
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) return false;
    
    size_t bytes_lidos = fread(&estado, sizeof(EstadoJogo), 1, arquivo);
    fclose(arquivo);
    
    if (bytes_lidos != 1) return false;
    
    // Validar dados básicos
    if (estado.turno < 1 || estado.turno > 1000) return false;
    if (estado.jogador_atual < 1 || estado.jogador_atual > 2) return false;
    if (estado.dificuldade_ia < 1 || estado.dificuldade_ia > 3) return false;
    
    return true;
}

// Compactar saves (remover saves corrompidos)
int compactar_saves() {
    char jogos[50][50];
    int num_jogos = listar_jogos_salvos(jogos, 50);
    int removidos = 0;
    
    for (int i = 0; i < num_jogos; i++) {
        if (!validar_save(jogos[i])) {
            if (deletar_save(jogos[i])) {
                removidos++;
            }
        }
    }
    
    return removidos;
}

// Backup de save
bool backup_save(const char* nome_arquivo) {
    char nome_backup[100];
    time_t agora = time(NULL);
    struct tm* tempo_info = localtime(&agora);
    
    strftime(nome_backup, sizeof(nome_backup), "backup_%Y%m%d_%H%M%S.save", tempo_info);
    
    FILE* arquivo_origem = fopen(nome_arquivo, "rb");
    if (!arquivo_origem) return false;
    
    FILE* arquivo_backup = fopen(nome_backup, "wb");
    if (!arquivo_backup) {
        fclose(arquivo_origem);
        return false;
    }
    
    char buffer[1024];
    size_t bytes_lidos;
    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), arquivo_origem)) > 0) {
        fwrite(buffer, 1, bytes_lidos, arquivo_backup);
    }
    
    fclose(arquivo_origem);
    fclose(arquivo_backup);
    
    printf("Backup criado: %s\n", nome_backup);
    return true;
}
