#ifndef __CONFIGS__
#define __CONFIGS__
// Configurações gerais do jogo

// Config de tempo
#define DELAY 10000

// Config da matriz principal
#define NX_MATRIZ 11
#define NY_MATRIZ 11

// Config Matriz Gráfica
#define NX_GRAFICA NX_MATRIZ*3+2
#define NY_GRAFICA NY_MATRIZ*2+1

// Posição relativa
#define MARGEM_LATERAL 8
#define MARGEM_SUPERIOR 1
#define DX (MARGEM_LATERAL/2)
#define DY (3+MARGEM_SUPERIOR)

// Sobre os pontos
#define PONTOS_X 14
#define PONTOS_Y 1

// Sobre o placar
#define N_SCORES 10
#define SCORES_X 14
#define SCORES_Y 11

// Config Jogador
#define START_X 3
#define START_Y 3

// Config dos blocos
#define BORDA 19
#define VAZIO 2
#define PEDRA 50

// Config das frutas
#define N_PRIMEIRA_FRUTA 20
#define N_FRUTAS 7
#define N_PEDRAS 6

// Config gráfica
#define LETRAS 3
#define SELECT 4
#define ESP_SELECT 5

// Sobre o tempo
#define TEMPO_PARTIDA 10
#define TEMPO_X 9
#define TEMPO_Y 3 

#define true 1
#define false 0

int matriz[NX_MATRIZ][NY_MATRIZ];
int mGrafica[NX_GRAFICA][NY_GRAFICA];
int mBackup[NX_MATRIZ][NY_MATRIZ];

int direcLine[NY_MATRIZ];
int direcCol[NX_MATRIZ];

enum Direction {
    Direita, Esquerda, PraCima, PraBaixo, Indefinido
} Direction;

enum Status {
    Selecionando, Movendo
} Status;

typedef struct Placar {
	float best[10];
	char nome[10][3];
} Placar;

Placar *scores;

char id[4];

#define AMARELO 	20
#define AZUL 		21
#define LARANJA 	22
#define ROXO	 	23
#define VERDE	 	24
#define VERMELHO 	25
#define ROSA		26

#define FUNDO_MENU 			35
#define COR_LETRA_MENU 		36
#define COR_LETRA_JOGO 		37
#define COR_MOV_INVALIDO	30
#define COR_MOV_DECIDIU  	31

#define MOV_INVALIDO -1
#define TUDO_OK 1

#endif
