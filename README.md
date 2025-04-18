# Projeto Batalha Naval com SDL2
Este projeto é uma implementação simplificada do clássico jogo Batalha Naval, desenvolvido em linguagem C e utilizando a biblioteca gráfica SDL2. O jogo foi dividido em três módulos com níveis de dificuldade crescentes, onde cada módulo explora conceitos de vetores, matrizes, estruturas de repetição aninhadas e condicionais para manipular o tabuleiro e aplicar habilidades especiais.

## Módulos do Projeto
### Módulo 1 – Novato:
Utiliza um vetor unidimensional para representar o tabuleiro e posiciona um navio fixo em uma célula específica.
Conceitos abordados:

Vetores (arrays unidimensionais)

Interface gráfica básica com SDL2

Desenho de grid e posicionamento de um objeto (navio)

### Módulo 2 – Aventureiro:
Utiliza uma matriz (array bidimensional) para representar o tabuleiro, permitindo posicionar múltiplos navios, inclusive em posições diagonais.
Conceitos abordados:

Matrizes (arrays bidimensionais)

Estruturas de repetição aninhadas (loops)

Desenho de grid e posicionamento de vários objetos

### Módulo 3 – Mestre:
Implementa habilidades especiais que afetam áreas específicas do tabuleiro (cone, cruz e octaedro). O usuário pode selecionar a habilidade através do teclado, e o efeito é desenhado a partir de uma posição central fixa.
Conceitos abordados:

Condicionais e loops aninhados para determinar áreas de efeito

Manipulação avançada de matrizes

Integração de lógica de jogo com interface gráfica

Requisitos
Linguagem: C

### Biblioteca gráfica: SDL2

### Sistema Operacional: Pode ser compilado em Linux, Windows, ou macOS (necessita de ajustes de configuração conforme o ambiente)

Configuração do Ambiente
Instalar SDL2:
Certifique-se de ter a SDL2 instalada no seu sistema.

Linux: Utilize o gerenciador de pacotes (ex.: sudo apt-get install libsdl2-dev).

Windows: Baixe e configure a SDL2 de acordo com as instruções do site oficial.

macOS: Utilize o Homebrew (brew install sdl2).


# Funcionamento
Interface Gráfica:
Cada módulo cria uma janela onde é desenhado um grid representando o tabuleiro de 10x10 células.

## Módulo 1:
Um único navio é desenhado em uma posição pré-definida usando um vetor unidimensional.

## Módulo 2:
Vários navios são posicionados utilizando uma matriz, com posicionamentos horizontais, verticais e diagonais.

## Módulo 3:
O usuário pode pressionar as teclas 1, 2 ou 3 para aplicar diferentes habilidades especiais (cone, cruz e octaedro) a partir de uma posição central fixa (para demonstração).


### Desenvolvido por Daniel Barbieri Dev como parte do desafio da Oceanic Games !!!