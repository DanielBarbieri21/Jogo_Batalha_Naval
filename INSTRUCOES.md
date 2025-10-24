# 📋 Instruções de Uso - Batalha Naval Profissional

## 🚀 Início Rápido

### 1. **Compilação**
```bash
# Compilar o projeto
make

# Ou usar o script de instalação
./install.sh
```

### 2. **Execução**
```bash
# Executar o jogo
make run

# Ou executar diretamente
./bin/batalha_naval
```

### 3. **Testes**
```bash
# Executar testes
make test

# Verificar código
make check
```

## 🎮 Controles do Jogo

### **Menu Principal**
- **Mouse**: Navegar pelos botões
- **Enter**: Selecionar opção
- **ESC**: Sair do jogo

### **Durante o Jogo**
- **Mouse**: Clicar nas células do tabuleiro
- **ESC**: Voltar ao menu
- **F11**: Alternar tela cheia
- **S**: Salvar jogo
- **L**: Carregar jogo

### **Configurações**
- **Setas**: Navegar pelas opções
- **Enter**: Confirmar
- **ESC**: Voltar

## 🎯 Modos de Jogo

### **1. Modo Novato**
- Tutorial interativo
- Um navio por vez
- Dicas visuais
- Ideal para iniciantes

### **2. Modo Aventureiro**
- Múltiplos navios
- Diferentes orientações
- Estratégia básica
- Para jogadores intermediários

### **3. Modo Mestre**
- Habilidades especiais
- Estratégias avançadas
- IA inteligente
- Para jogadores experientes

## 🤖 Inteligência Artificial

### **Níveis de Dificuldade**

#### 🟢 **Fácil**
- Jogadas aleatórias
- Estratégia básica
- Ideal para iniciantes

#### 🟡 **Médio**
- Análise de probabilidades
- Padrões de posicionamento
- Estratégia adaptativa

#### 🔴 **Difícil**
- Algoritmos avançados
- Análise de densidade
- Estratégia de caça
- Aprendizado de padrões

## 💾 Sistema de Save/Load

### **Salvar Jogo**
1. Durante o jogo, pressione **S**
2. Digite o nome do save
3. Confirme a operação

### **Carregar Jogo**
1. No menu principal, selecione "Carregar Jogo"
2. Escolha o save desejado
3. Confirme a operação

### **Auto-save**
- Salvamento automático a cada minuto
- Arquivos em `autosave_*.save`
- Backup automático de segurança

## 📊 Estatísticas

### **Métricas Acompanhadas**
- **Jogos Jogados**: Total de partidas
- **Taxa de Vitória**: Percentual de vitórias
- **Precisão**: Percentual de tiros acertados
- **Navios Destruídos**: Total por jogo
- **Melhor Sequência**: Maior sequência de acertos
- **Tempo Médio**: Duração média das partidas
- **Pontuação Máxima**: Melhor pontuação alcançada

### **Visualizar Estatísticas**
1. Menu Principal → Estatísticas
2. Navegar pelas métricas
3. Exportar para arquivo (opcional)

## ⚙️ Configurações

### **Acessar Configurações**
1. Menu Principal → Configurações
2. Ajustar opções desejadas
3. Salvar configurações

### **Opções Disponíveis**
- **Volume da Música**: 0-100%
- **Volume dos Efeitos**: 0-100%
- **Dificuldade da IA**: 1-3 níveis
- **Resolução**: Múltiplas resoluções
- **Tela Cheia**: Sim/Não
- **Som**: Habilitar/Desabilitar

## 🔧 Solução de Problemas

### **Erro de Compilação**
```bash
# Verificar dependências
make install-deps

# Limpar e recompilar
make clean
make
```

### **Erro de Execução**
```bash
# Verificar bibliotecas
ldd bin/batalha_naval

# Executar em modo debug
make debug
```

### **Problemas de Som**
1. Verificar se SDL2_mixer está instalado
2. Verificar configurações de áudio
3. Testar com `make test`

### **Problemas de Gráficos**
1. Verificar drivers de vídeo
2. Tentar diferentes resoluções
3. Verificar configurações de SDL2

## 📁 Estrutura de Arquivos

### **Arquivos Principais**
- `batalha_naval.c` - Arquivo principal
- `batalha_naval.h` - Cabeçalhos
- `renderizacao.c` - Sistema de renderização
- `ia.c` - Inteligência artificial
- `configuracao.c` - Sistema de configurações
- `save_load.c` - Sistema de save/load

### **Arquivos de Configuração**
- `Makefile` - Sistema de build
- `config.h` - Configurações do projeto
- `Doxyfile` - Configuração de documentação
- `.gitignore` - Arquivos ignorados pelo Git

### **Arquivos de Dados**
- `config.dat` - Configurações salvas
- `stats.dat` - Estatísticas salvas
- `*.save` - Jogos salvos
- `assets/` - Recursos do jogo

## 🧪 Desenvolvimento

### **Compilar para Debug**
```bash
make debug
```

### **Verificar Código**
```bash
make check
```

### **Gerar Documentação**
```bash
make docs
```

### **Executar Testes**
```bash
make test
```

### **Análise de Memória (Linux)**
```bash
make valgrind
```

## 📞 Suporte

### **Problemas Comuns**
1. **Jogo não inicia**: Verificar dependências
2. **Som não funciona**: Verificar SDL2_mixer
3. **Gráficos distorcidos**: Verificar drivers
4. **Save não funciona**: Verificar permissões

### **Logs de Debug**
- Ativar modo debug: `make debug`
- Verificar logs no console
- Usar `make valgrind` para análise de memória

### **Relatórios de Bug**
1. Descrever o problema
2. Incluir logs de erro
3. Especificar sistema operacional
4. Incluir versão do jogo

## 🎯 Dicas de Jogo

### **Estratégias Básicas**
1. **Posicionamento**: Espalhe navios pelo tabuleiro
2. **Orientação**: Use diferentes orientações
3. **Padrões**: Evite padrões previsíveis
4. **Bordas**: Use bordas estrategicamente

### **Contra IA**
1. **Fácil**: Jogue normalmente
2. **Médio**: Use estratégias mais complexas
3. **Difícil**: Seja imprevisível

### **Habilidades Especiais**
1. **Cone**: Use em áreas densas
2. **Cruz**: Use em cruzamentos
3. **Octaedro**: Use em áreas centrais

## 📈 Melhorias Futuras

### **Recursos Planejados**
- Modo multijogador online
- Mais tipos de navios
- Habilidades especiais adicionais
- Temas visuais personalizáveis
- Sistema de conquistas
- Modo torneio

### **Contribuições**
- Fork o projeto
- Crie uma branch
- Implemente melhorias
- Envie pull request

---

**Desenvolvido por Daniel Barbieri Dev**  
**Versão 2.0 - 2024**

Para mais informações, consulte o README.md principal.
