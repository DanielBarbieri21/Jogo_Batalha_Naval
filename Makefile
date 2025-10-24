# Makefile para Batalha Naval - Versão Profissional
# Desenvolvido por Daniel Barbieri Dev

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ASSETS_DIR = assets

# Nome do executável
TARGET = batalha_naval

# Arquivos fonte
SOURCES = batalha_naval.c renderizacao.c ia.c configuracao.c save_load.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

# Diretórios de assets
ASSETS_SUBDIRS = fonts sounds music images

# Cores para output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m # No Color

# Regra padrão
all: setup $(TARGET)

# Criar diretórios necessários
setup:
	@echo "$(BLUE)Criando estrutura de diretórios...$(NC)"
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(ASSETS_DIR)
	@for dir in $(ASSETS_SUBDIRS); do \
		mkdir -p $(ASSETS_DIR)/$$dir; \
	done
	@echo "$(GREEN)Estrutura criada com sucesso!$(NC)"

# Compilar o executável
$(TARGET): $(OBJECTS)
	@echo "$(YELLOW)Linkando executável...$(NC)"
	$(CC) $(OBJECTS) -o $(BIN_DIR)/$(TARGET) $(LDFLAGS)
	@echo "$(GREEN)Executável criado: $(BIN_DIR)/$(TARGET)$(NC)"

# Compilar arquivos objeto
$(OBJ_DIR)/%.o: %.c
	@echo "$(CYAN)Compilando $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# Instalar dependências (Ubuntu/Debian)
install-deps:
	@echo "$(BLUE)Instalando dependências do sistema...$(NC)"
	sudo apt-get update
	sudo apt-get install -y libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
	@echo "$(GREEN)Dependências instaladas!$(NC)"

# Instalar dependências (Windows - MSYS2)
install-deps-windows:
	@echo "$(BLUE)Instalando dependências para Windows...$(NC)"
	pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_mixer
	@echo "$(GREEN)Dependências instaladas!$(NC)"

# Instalar dependências (macOS)
install-deps-macos:
	@echo "$(BLUE)Instalando dependências para macOS...$(NC)"
	brew install sdl2 sdl2_ttf sdl2_mixer
	@echo "$(GREEN)Dependências instaladas!$(NC)"

# Executar o jogo
run: $(TARGET)
	@echo "$(GREEN)Executando Batalha Naval...$(NC)"
	cd $(BIN_DIR) && ./$(TARGET)

# Executar com debug
debug: CFLAGS += -DDEBUG -g3
debug: $(TARGET)
	@echo "$(YELLOW)Executando em modo debug...$(NC)"
	cd $(BIN_DIR) && gdb ./$(TARGET)

# Executar com valgrind (Linux)
valgrind: $(TARGET)
	@echo "$(YELLOW)Executando com valgrind...$(NC)"
	cd $(BIN_DIR) && valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Limpar arquivos compilados
clean:
	@echo "$(RED)Limpando arquivos compilados...$(NC)"
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "$(GREEN)Limpeza concluída!$(NC)"

# Limpar tudo (incluindo saves e configs)
distclean: clean
	@echo "$(RED)Limpando arquivos de dados...$(NC)"
	rm -f *.save *.dat *.txt
	rm -rf $(ASSETS_DIR)
	@echo "$(GREEN)Limpeza completa!$(NC)"

# Instalar o jogo
install: $(TARGET)
	@echo "$(BLUE)Instalando Batalha Naval...$(NC)"
	sudo mkdir -p /usr/local/games/batalha_naval
	sudo cp $(BIN_DIR)/$(TARGET) /usr/local/games/batalha_naval/
	sudo cp -r $(ASSETS_DIR) /usr/local/games/batalha_naval/
	@echo "$(GREEN)Jogo instalado em /usr/local/games/batalha_naval/$(NC)"

# Desinstalar o jogo
uninstall:
	@echo "$(RED)Desinstalando Batalha Naval...$(NC)"
	sudo rm -rf /usr/local/games/batalha_naval
	@echo "$(GREEN)Jogo desinstalado!$(NC)"

# Criar pacote de distribuição
package: $(TARGET)
	@echo "$(BLUE)Criando pacote de distribuição...$(NC)"
	mkdir -p dist/batalha_naval
	cp $(BIN_DIR)/$(TARGET) dist/batalha_naval/
	cp -r $(ASSETS_DIR) dist/batalha_naval/
	cp README.md dist/batalha_naval/
	cp LICENSE dist/batalha_naval/ 2>/dev/null || true
	cd dist && tar -czf batalha_naval.tar.gz batalha_naval/
	@echo "$(GREEN)Pacote criado: dist/batalha_naval.tar.gz$(NC)"

# Verificar código com cppcheck
check:
	@echo "$(YELLOW)Verificando código com cppcheck...$(NC)"
	cppcheck --enable=all --std=c99 *.c
	@echo "$(GREEN)Verificação concluída!$(NC)"

# Formatar código
format:
	@echo "$(YELLOW)Formatando código...$(NC)"
	clang-format -i *.c *.h
	@echo "$(GREEN)Código formatado!$(NC)"

# Gerar documentação
docs:
	@echo "$(BLUE)Gerando documentação...$(NC)"
	doxygen Doxyfile
	@echo "$(GREEN)Documentação gerada em docs/$(NC)"

# Executar testes
test: $(TARGET)
	@echo "$(YELLOW)Executando testes...$(NC)"
	cd $(BIN_DIR) && ./$(TARGET) --test
	@echo "$(GREEN)Testes concluídos!$(NC)"

# Mostrar informações do projeto
info:
	@echo "$(PURPLE)=== BATALHA NAVAL - VERSÃO PROFISSIONAL ===$(NC)"
	@echo "$(CYAN)Desenvolvido por: Daniel Barbieri Dev$(NC)"
	@echo "$(CYAN)Versão: 2.0$(NC)"
	@echo "$(CYAN)Compilador: $(CC)$(NC)"
	@echo "$(CYAN)Flags: $(CFLAGS)$(NC)"
	@echo "$(CYAN)Bibliotecas: $(LDFLAGS)$(NC)"
	@echo "$(CYAN)Arquivos fonte: $(SOURCES)$(NC)"
	@echo "$(CYAN)Executável: $(BIN_DIR)/$(TARGET)$(NC)"

# Mostrar ajuda
help:
	@echo "$(GREEN)=== COMANDOS DISPONÍVEIS ===$(NC)"
	@echo "$(WHITE)make$(NC)              - Compilar o projeto"
	@echo "$(WHITE)make run$(NC)          - Executar o jogo"
	@echo "$(WHITE)make debug$(NC)        - Executar em modo debug"
	@echo "$(WHITE)make clean$(NC)        - Limpar arquivos compilados"
	@echo "$(WHITE)make distclean$(NC)    - Limpeza completa"
	@echo "$(WHITE)make install$(NC)      - Instalar o jogo"
	@echo "$(WHITE)make uninstall$(NC)    - Desinstalar o jogo"
	@echo "$(WHITE)make package$(NC)      - Criar pacote de distribuição"
	@echo "$(WHITE)make check$(NC)        - Verificar código"
	@echo "$(WHITE)make format$(NC)       - Formatar código"
	@echo "$(WHITE)make docs$(NC)         - Gerar documentação"
	@echo "$(WHITE)make test$(NC)         - Executar testes"
	@echo "$(WHITE)make info$(NC)         - Mostrar informações"
	@echo "$(WHITE)make help$(NC)         - Mostrar esta ajuda"

# Dependências dos arquivos objeto
$(OBJ_DIR)/batalha_naval.o: batalha_naval.c batalha_naval.h
$(OBJ_DIR)/renderizacao.o: renderizacao.c batalha_naval.h
$(OBJ_DIR)/ia.o: ia.c batalha_naval.h
$(OBJ_DIR)/configuracao.o: configuracao.c batalha_naval.h
$(OBJ_DIR)/save_load.o: save_load.c batalha_naval.h

# Regras especiais
.PHONY: all setup install-deps install-deps-windows install-deps-macos run debug valgrind clean distclean install uninstall package check format docs test info help

# Configuração para diferentes sistemas
ifeq ($(OS),Windows_NT)
    LDFLAGS += -lmingw32
    TARGET := $(TARGET).exe
endif

# Configuração para macOS
ifeq ($(shell uname),Darwin)
    LDFLAGS += -framework Cocoa
endif
