#!/bin/bash

# Script de instalação para Batalha Naval - Versão Profissional
# Desenvolvido por Daniel Barbieri Dev

set -e

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# Função para imprimir mensagens coloridas
print_message() {
    echo -e "${2}${1}${NC}"
}

# Função para verificar se comando existe
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Função para detectar sistema operacional
detect_os() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS="linux"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macos"
    elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
        OS="windows"
    else
        OS="unknown"
    fi
}

# Função para instalar dependências no Linux
install_deps_linux() {
    print_message "Instalando dependências para Linux..." $BLUE
    
    if command_exists apt-get; then
        # Ubuntu/Debian
        sudo apt-get update
        sudo apt-get install -y build-essential libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
    elif command_exists yum; then
        # CentOS/RHEL
        sudo yum install -y gcc gcc-c++ SDL2-devel SDL2_ttf-devel SDL2_mixer-devel
    elif command_exists pacman; then
        # Arch Linux
        sudo pacman -S --noconfirm base-devel sdl2 sdl2_ttf sdl2_mixer
    else
        print_message "Gerenciador de pacotes não suportado. Instale manualmente: SDL2, SDL2_ttf, SDL2_mixer" $RED
        exit 1
    fi
}

# Função para instalar dependências no macOS
install_deps_macos() {
    print_message "Instalando dependências para macOS..." $BLUE
    
    if command_exists brew; then
        brew install sdl2 sdl2_ttf sdl2_mixer
    else
        print_message "Homebrew não encontrado. Instale o Homebrew primeiro:" $RED
        print_message "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"" $YELLOW
        exit 1
    fi
}

# Função para instalar dependências no Windows
install_deps_windows() {
    print_message "Instalando dependências para Windows..." $BLUE
    
    if command_exists pacman; then
        # MSYS2
        pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_mixer
    else
        print_message "MSYS2 não encontrado. Instale o MSYS2 primeiro:" $RED
        print_message "https://www.msys2.org/" $YELLOW
        exit 1
    fi
}

# Função para criar estrutura de diretórios
create_directories() {
    print_message "Criando estrutura de diretórios..." $BLUE
    
    mkdir -p assets/fonts
    mkdir -p assets/sounds
    mkdir -p assets/music
    mkdir -p assets/images
    mkdir -p docs
    mkdir -p obj
    mkdir -p bin
    
    print_message "Estrutura de diretórios criada!" $GREEN
}

# Função para criar arquivos de exemplo
create_example_files() {
    print_message "Criando arquivos de exemplo..." $BLUE
    
    # Arquivo de exemplo para fontes
    cat > assets/fonts/README.md << EOF
# Fontes do Jogo

Coloque aqui as fontes do jogo:
- arial.ttf (fonte principal)
- arial-bold.ttf (fonte em negrito)
- arial-italic.ttf (fonte em itálico)

As fontes serão carregadas automaticamente pelo jogo.
EOF

    # Arquivo de exemplo para sons
    cat > assets/sounds/README.md << EOF
# Efeitos Sonoros

Coloque aqui os efeitos sonoros do jogo:
- shot.wav (som de tiro)
- hit.wav (som de acerto)
- miss.wav (som de erro)
- ship_destroyed.wav (som de navio destruído)

Os sons serão carregados automaticamente pelo jogo.
EOF

    # Arquivo de exemplo para música
    cat > assets/music/README.md << EOF
# Música de Fundo

Coloque aqui as músicas de fundo do jogo:
- background.mp3 (música principal)
- menu.mp3 (música do menu)
- victory.mp3 (música de vitória)
- defeat.mp3 (música de derrota)

As músicas serão carregadas automaticamente pelo jogo.
EOF

    # Arquivo de exemplo para imagens
    cat > assets/images/README.md << EOF
# Imagens e Sprites

Coloque aqui as imagens do jogo:
- logo.png (logo do jogo)
- background.jpg (fundo do jogo)
- ship.png (sprite do navio)
- explosion.png (sprite de explosão)

As imagens serão carregadas automaticamente pelo jogo.
EOF

    print_message "Arquivos de exemplo criados!" $GREEN
}

# Função para compilar o projeto
compile_project() {
    print_message "Compilando o projeto..." $BLUE
    
    if make clean && make; then
        print_message "Compilação concluída com sucesso!" $GREEN
    else
        print_message "Erro na compilação!" $RED
        exit 1
    fi
}

# Função para executar testes
run_tests() {
    print_message "Executando testes..." $BLUE
    
    if make test; then
        print_message "Testes executados com sucesso!" $GREEN
    else
        print_message "Alguns testes falharam!" $YELLOW
    fi
}

# Função para mostrar informações do sistema
show_system_info() {
    print_message "=== INFORMAÇÕES DO SISTEMA ===" $PURPLE
    print_message "Sistema Operacional: $OS" $CYAN
    print_message "Arquitetura: $(uname -m)" $CYAN
    print_message "Versão do Kernel: $(uname -r)" $CYAN
    print_message "Compilador: $(gcc --version | head -n1)" $CYAN
    print_message "Make: $(make --version | head -n1)" $CYAN
}

# Função para mostrar ajuda
show_help() {
    print_message "=== AJUDA - INSTALAÇÃO BATALHA NAVAL ===" $PURPLE
    print_message "Uso: $0 [opções]" $WHITE
    print_message "" $WHITE
    print_message "Opções:" $WHITE
    print_message "  -h, --help     Mostrar esta ajuda" $WHITE
    print_message "  -d, --deps     Instalar apenas dependências" $WHITE
    print_message "  -c, --compile  Compilar o projeto" $WHITE
    print_message "  -t, --test     Executar testes" $WHITE
    print_message "  -i, --info     Mostrar informações do sistema" $WHITE
    print_message "  -a, --all      Instalação completa (padrão)" $WHITE
    print_message "" $WHITE
    print_message "Exemplos:" $WHITE
    print_message "  $0                # Instalação completa" $WHITE
    print_message "  $0 --deps         # Apenas dependências" $WHITE
    print_message "  $0 --compile      # Apenas compilação" $WHITE
}

# Função principal
main() {
    print_message "🚢 BATALHA NAVAL - VERSÃO PROFISSIONAL" $PURPLE
    print_message "Instalador automático" $BLUE
    print_message "Desenvolvido por Daniel Barbieri Dev" $CYAN
    print_message "" $WHITE
    
    # Detectar sistema operacional
    detect_os
    print_message "Sistema detectado: $OS" $GREEN
    
    # Processar argumentos
    case "${1:-}" in
        -h|--help)
            show_help
            exit 0
            ;;
        -d|--deps)
            install_deps_$OS
            exit 0
            ;;
        -c|--compile)
            compile_project
            exit 0
            ;;
        -t|--test)
            run_tests
            exit 0
            ;;
        -i|--info)
            show_system_info
            exit 0
            ;;
        -a|--all|"")
            # Instalação completa
            install_deps_$OS
            create_directories
            create_example_files
            compile_project
            run_tests
            show_system_info
            print_message "🎉 Instalação concluída com sucesso!" $GREEN
            print_message "Execute 'make run' para jogar!" $YELLOW
            ;;
        *)
            print_message "Opção inválida: $1" $RED
            show_help
            exit 1
            ;;
    esac
}

# Executar função principal
main "$@"
