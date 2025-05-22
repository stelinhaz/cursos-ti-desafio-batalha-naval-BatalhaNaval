#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com 0
void inicializaTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Água
        }
    }
}

// Função para posicionar navios fictícios no tabuleiro
void posicionaNavios(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    // Simplesmente vamos colocar alguns navios (valor 3) fixos
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[7][2] = 3;
}

// Função para exibir o tabuleiro
void exibeTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");  // Água
            else if (tabuleiro[i][j] == 3)
                printf("N ");  // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* ");  // Área de habilidade
            else
                printf("? ");
        }
        printf("\n");
    }
}

// Função para criar matriz de habilidade em forma de cone
void criaMatrizCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }

    // Construção do cone (ponta para baixo)
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = meio - i; j <= meio + i; j++) {
            if (j >= 0 && j < TAM_HABILIDADE) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para criar matriz de habilidade em forma de cruz
void criaMatrizCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }

    int meio = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        habilidade[i][meio] = 1;  // coluna do meio
    }

    for (int j = 0; j < TAM_HABILIDADE; j++) {
        habilidade[meio][j] = 1;  // linha do meio
    }
}

// Função para criar matriz de habilidade em forma de octaedro (losango)
void criaMatrizOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    // Inicializa com 0
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }

    int meio = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio) {
                habilidade[i][j] = 1;
            }
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro
void sobrepoeHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha + (i - offset);
                int colunaTab = origemColuna + (j - offset);

                // Garantir que não sai dos limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO && colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == 0) {
                        tabuleiro[linhaTab][colunaTab] = 5;  // marca como área de habilidade
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializaTabuleiro(tabuleiro);
    posicionaNavios(tabuleiro);

    // Criando as matrizes de habilidade
    criaMatrizCone(cone);
    criaMatrizCruz(cruz);
    criaMatrizOctaedro(octaedro);

    // Definindo pontos de origem fixos
    int origemConeLinha = 3, origemConeColuna = 3;
    int origemCruzLinha = 6, origemCruzColuna = 6;
    int origemOctaedroLinha = 8, origemOctaedroColuna = 2;

    // Sobrepondo as habilidades ao tabuleiro
    sobrepoeHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    sobrepoeHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    sobrepoeHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibindo o tabuleiro final
    printf("Tabuleiro com habilidades sobrepostas:\n");
    exibeTabuleiro(tabuleiro);

    return 0;
}
