#include "batalha_naval.h"
#include <math.h>

// Estrutura para rastrear tentativas da IA
typedef struct {
    int x, y;
    bool tentado;
    int probabilidade;
} CelulaIA;

static CelulaIA tabuleiro_ia[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
static bool ia_inicializada = false;

// Inicializar sistema de IA
void inicializar_ia() {
    if (ia_inicializada) return;
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro_ia[i][j].x = j;
            tabuleiro_ia[i][j].y = i;
            tabuleiro_ia[i][j].tentado = false;
            tabuleiro_ia[i][j].probabilidade = 0;
        }
    }
    ia_inicializada = true;
}

// Jogada da IA
void jogada_ia(Tabuleiro* tab_inimigo, int dificuldade) {
    inicializar_ia();
    
    int x, y;
    
    switch (dificuldade) {
        case 1: // Fácil - jogadas aleatórias
            do {
                x = rand() % TAMANHO_TABULEIRO;
                y = rand() % TAMANHO_TABULEIRO;
            } while (tab_inimigo->grid[y][x] == -1 || tab_inimigo->grid[y][x] == -2);
            break;
            
        case 2: // Médio - estratégia básica
            calcular_probabilidades(tab_inimigo);
            encontrar_melhor_jogada(&x, &y);
            break;
            
        case 3: // Difícil - estratégia avançada
            calcular_probabilidades_avancadas(tab_inimigo);
            encontrar_melhor_jogada(&x, &y);
            break;
    }
    
    // Executar jogada
    bool acerto = atirar(tab_inimigo, x, y);
    tabuleiro_ia[y][x].tentado = true;
    
    // Se acertou, marcar células adjacentes como mais prováveis
    if (acerto) {
        aumentar_probabilidade_adjacentes(x, y);
    }
}

// Calcular probabilidades básicas
void calcular_probabilidades(Tabuleiro* tab) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tab->grid[i][j] == -1 || tab->grid[i][j] == -2) {
                tabuleiro_ia[i][j].probabilidade = 0;
                continue;
            }
            
            int prob = 0;
            
            // Verificar se há navios próximos
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < TAMANHO_TABULEIRO && nj >= 0 && nj < TAMANHO_TABULEIRO) {
                        if (tab->grid[ni][nj] == -1) { // Acerto próximo
                            prob += 10;
                        }
                    }
                }
            }
            
            // Padrões de navios comuns
            prob += verificar_padrao_navio(tab, j, i);
            
            tabuleiro_ia[i][j].probabilidade = prob;
        }
    }
}

// Calcular probabilidades avançadas
void calcular_probabilidades_avancadas(Tabuleiro* tab) {
    calcular_probabilidades(tab);
    
    // Análise de padrões mais sofisticada
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tab->grid[i][j] == -1 || tab->grid[i][j] == -2) continue;
            
            int prob = tabuleiro_ia[i][j].probabilidade;
            
            // Análise de densidade de navios
            prob += analisar_densidade_navios(tab, j, i);
            
            // Análise de bordas (navios tendem a ficar nas bordas)
            prob += analisar_bordas(j, i);
            
            // Análise de simetria
            prob += analisar_simetria(tab, j, i);
            
            tabuleiro_ia[i][j].probabilidade = prob;
        }
    }
}

// Verificar padrão de navio
int verificar_padrao_navio(Tabuleiro* tab, int x, int y) {
    int prob = 0;
    
    // Verificar linhas horizontais
    int navios_h = contar_navios_linha(tab, y);
    if (navios_h > 0) prob += 5;
    
    // Verificar colunas verticais
    int navios_v = contar_navios_coluna(tab, x);
    if (navios_v > 0) prob += 5;
    
    // Verificar diagonais
    int navios_d1 = contar_navios_diagonal1(tab, x, y);
    int navios_d2 = contar_navios_diagonal2(tab, x, y);
    if (navios_d1 > 0 || navios_d2 > 0) prob += 3;
    
    return prob;
}

// Contar navios em linha
int contar_navios_linha(Tabuleiro* tab, int linha) {
    int count = 0;
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        if (tab->grid[linha][j] > 0) count++;
    }
    return count;
}

// Contar navios em coluna
int contar_navios_coluna(Tabuleiro* tab, int coluna) {
    int count = 0;
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (tab->grid[i][coluna] > 0) count++;
    }
    return count;
}

// Contar navios em diagonal principal
int contar_navios_diagonal1(Tabuleiro* tab, int x, int y) {
    int count = 0;
    int min = (x < y) ? x : y;
    int start_x = x - min;
    int start_y = y - min;
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        int nx = start_x + i;
        int ny = start_y + i;
        if (nx < TAMANHO_TABULEIRO && ny < TAMANHO_TABULEIRO) {
            if (tab->grid[ny][nx] > 0) count++;
        }
    }
    return count;
}

// Contar navios em diagonal secundária
int contar_navios_diagonal2(Tabuleiro* tab, int x, int y) {
    int count = 0;
    int start_x = x + y;
    int start_y = 0;
    
    if (start_x >= TAMANHO_TABULEIRO) {
        start_x = TAMANHO_TABULEIRO - 1;
        start_y = x + y - start_x;
    }
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        int nx = start_x - i;
        int ny = start_y + i;
        if (nx >= 0 && ny < TAMANHO_TABULEIRO) {
            if (tab->grid[ny][nx] > 0) count++;
        }
    }
    return count;
}

// Analisar densidade de navios
int analisar_densidade_navios(Tabuleiro* tab, int x, int y) {
    int densidade = 0;
    int raio = 2;
    
    for (int i = y - raio; i <= y + raio; i++) {
        for (int j = x - raio; j <= x + raio; j++) {
            if (i >= 0 && i < TAMANHO_TABULEIRO && j >= 0 && j < TAMANHO_TABULEIRO) {
                if (tab->grid[i][j] > 0) {
                    int distancia = abs(i - y) + abs(j - x);
                    densidade += (raio - distancia + 1);
                }
            }
        }
    }
    
    return densidade;
}

// Analisar bordas
int analisar_bordas(int x, int y) {
    int prob = 0;
    
    // Bordas têm menor probabilidade
    if (x == 0 || x == TAMANHO_TABULEIRO - 1 || y == 0 || y == TAMANHO_TABULEIRO - 1) {
        prob -= 2;
    }
    
    // Cantos têm ainda menor probabilidade
    if ((x == 0 || x == TAMANHO_TABULEIRO - 1) && (y == 0 || y == TAMANHO_TABULEIRO - 1)) {
        prob -= 3;
    }
    
    return prob;
}

// Analisar simetria
int analisar_simetria(Tabuleiro* tab, int x, int y) {
    int prob = 0;
    
    // Verificar simetria horizontal
    int simetria_h = 0;
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        if (tab->grid[y][j] > 0 && tab->grid[y][TAMANHO_TABULEIRO - 1 - j] > 0) {
            simetria_h++;
        }
    }
    if (simetria_h > 0) prob += 2;
    
    // Verificar simetria vertical
    int simetria_v = 0;
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (tab->grid[i][x] > 0 && tab->grid[TAMANHO_TABULEIRO - 1 - i][x] > 0) {
            simetria_v++;
        }
    }
    if (simetria_v > 0) prob += 2;
    
    return prob;
}

// Encontrar melhor jogada
void encontrar_melhor_jogada(int* x, int* y) {
    int melhor_prob = -1;
    int melhor_x = 0, melhor_y = 0;
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (!tabuleiro_ia[i][j].tentado && tabuleiro_ia[i][j].probabilidade > melhor_prob) {
                melhor_prob = tabuleiro_ia[i][j].probabilidade;
                melhor_x = j;
                melhor_y = i;
            }
        }
    }
    
    // Se não encontrou nenhuma célula com probabilidade, escolher aleatória
    if (melhor_prob == -1) {
        do {
            melhor_x = rand() % TAMANHO_TABULEIRO;
            melhor_y = rand() % TAMANHO_TABULEIRO;
        } while (tabuleiro_ia[melhor_y][melhor_x].tentado);
    }
    
    *x = melhor_x;
    *y = melhor_y;
}

// Aumentar probabilidade de células adjacentes
void aumentar_probabilidade_adjacentes(int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + j;
            int ny = y + i;
            if (nx >= 0 && nx < TAMANHO_TABULEIRO && ny >= 0 && ny < TAMANHO_TABULEIRO) {
                if (!tabuleiro_ia[ny][nx].tentado) {
                    tabuleiro_ia[ny][nx].probabilidade += 15;
                }
            }
        }
    }
}

// Avaliar posição (para análise de jogadas)
int avaliar_posicao(Tabuleiro* tab, int x, int y) {
    if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO) {
        return -1;
    }
    
    int celula = tab->grid[y][x];
    
    if (celula == -1) return 1;  // Acerto
    if (celula == -2) return 0;   // Erro
    if (celula > 0) return 1;    // Navio
    
    return 0; // Água
}

// Estratégia de caça (quando já acertou um navio)
void estrategia_caca(Tabuleiro* tab, int* x, int* y) {
    // Procurar por acertos que ainda não foram explorados
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tab->grid[i][j] == -1) { // Acerto
                // Procurar células adjacentes não exploradas
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < TAMANHO_TABULEIRO && nj >= 0 && nj < TAMANHO_TABULEIRO) {
                            if (tab->grid[ni][nj] == 0 && !tabuleiro_ia[ni][nj].tentado) {
                                *x = nj;
                                *y = ni;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Se não encontrou, usar estratégia normal
    encontrar_melhor_jogada(x, y);
}

// Estratégia de posicionamento de navios para IA
void posicionar_navios_ia(Tabuleiro* tab) {
    // Limpar tabuleiro
    inicializar_tabuleiro(tab);
    
    // Posicionar navios de forma estratégica
    TipoNavio tipos[] = {SUBMARINO, DESTROIER, CRUZADOR, ENCOURACADO, PORTA_AVIOES};
    int quantidades[] = {4, 3, 2, 1, 1};
    
    for (int t = 0; t < 5; t++) {
        for (int q = 0; q < quantidades[t]; q++) {
            bool posicionado = false;
            int tentativas = 0;
            
            while (!posicionado && tentativas < 100) {
                int x = rand() % TAMANHO_TABULEIRO;
                int y = rand() % TAMANHO_TABULEIRO;
                Orientacao orientacao = rand() % 4;
                
                if (posicionar_navio(tab, x, y, tipos[t], orientacao)) {
                    posicionado = true;
                }
                tentativas++;
            }
        }
    }
}
