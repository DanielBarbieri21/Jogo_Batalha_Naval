#ifndef CONFIG_H
#define CONFIG_H

// Configurações do projeto Batalha Naval
// Versão: 2.0
// Desenvolvido por: Daniel Barbieri Dev

// Versão do jogo
#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_STRING "2.0.0"

// Configurações de compilação
#ifdef DEBUG
    #define DEBUG_MODE 1
    #define LOG_LEVEL 2
#else
    #define DEBUG_MODE 0
    #define LOG_LEVEL 1
#endif

// Configurações de performance
#define TARGET_FPS 60
#define MAX_FPS 120
#define MIN_FPS 30

// Configurações de memória
#define MAX_NAVIOS 10
#define MAX_SAVES 50
#define MAX_STATS_ENTRIES 1000

// Configurações de rede (para futuras implementações)
#define MAX_PLAYERS 2
#define MAX_CONNECTIONS 10
#define NETWORK_TIMEOUT 5000

// Configurações de áudio
#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFER_SIZE 2048

// Configurações de gráficos
#define DEFAULT_WIDTH 1200
#define DEFAULT_HEIGHT 800
#define MIN_WIDTH 800
#define MIN_HEIGHT 600
#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

// Configurações de IA
#define IA_MAX_DEPTH 5
#define IA_EVALUATION_TIME 1000
#define IA_MEMORY_SIZE 1024

// Configurações de save/load
#define SAVE_FILE_VERSION 1
#define MAX_SAVE_NAME_LENGTH 50
#define MAX_CONFIG_NAME_LENGTH 100

// Configurações de estatísticas
#define STATS_HISTORY_SIZE 100
#define STATS_UPDATE_INTERVAL 1000

// Configurações de interface
#define UI_ANIMATION_SPEED 300
#define UI_FADE_DURATION 500
#define UI_BUTTON_HOVER_DELAY 100

// Configurações de jogo
#define GAME_MAX_TURNS 1000
#define GAME_TIMEOUT 300000
#define GAME_AUTO_SAVE_INTERVAL 60000

// Configurações de debug
#ifdef DEBUG_MODE
    #define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
    #define DEBUG_ASSERT(expr) do { if (!(expr)) { printf("[ASSERT] %s:%d: %s\n", __FILE__, __LINE__, #expr); exit(1); } } while(0)
#else
    #define DEBUG_PRINT(fmt, ...)
    #define DEBUG_ASSERT(expr)
#endif

// Configurações de log
#define LOG_ERROR(fmt, ...) printf("[ERROR] " fmt "\n", ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) printf("[WARNING] " fmt "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) printf("[INFO] " fmt "\n", ##__VA_ARGS__)

// Configurações de plataforma
#ifdef _WIN32
    #define PLATFORM_WINDOWS 1
    #define PATH_SEPARATOR '\\'
    #define PATH_SEPARATOR_STRING "\\"
#elif defined(__linux__)
    #define PLATFORM_LINUX 1
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STRING "/"
#elif defined(__APPLE__)
    #define PLATFORM_MACOS 1
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STRING "/"
#else
    #define PLATFORM_UNKNOWN 1
    #define PATH_SEPARATOR '/'
    #define PATH_SEPARATOR_STRING "/"
#endif

// Configurações de arquivos
#define CONFIG_FILE "config.dat"
#define STATS_FILE "stats.dat"
#define SAVE_DIRECTORY "saves"
#define ASSETS_DIRECTORY "assets"

// Configurações de segurança
#define MAX_INPUT_LENGTH 256
#define MAX_FILENAME_LENGTH 255
#define MAX_PATH_LENGTH 4096

// Configurações de validação
#define VALIDATE_INPUT 1
#define VALIDATE_FILES 1
#define VALIDATE_MEMORY 1

// Configurações de otimização
#define USE_FAST_MATH 1
#define USE_VECTORIZATION 1
#define USE_MULTITHREADING 1

// Configurações de compatibilidade
#define SUPPORT_LEGACY_SAVES 1
#define SUPPORT_OLD_CONFIGS 1
#define SUPPORT_EXPERIMENTAL_FEATURES 0

#endif // CONFIG_H
