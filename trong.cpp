#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "menu.h"
#include <sys/time.h>

#define COR_MOTO 141
#define COR_MOLDURA 150
#define COR_PRETA 120

#define MATRIZ_LARGURA 30
#define MATRIZ_ALTURA 30
//#define COR_DESCELECIONADO 12

enum DIREC {
    CIMA, BAIXO, DIREITA, ESQUERDA
};

typedef struct MOTO_STR {
    int x, y;
    int cor;
    DIREC dir;
}  moto_t;

float timedifference_msec(struct timeval t0, struct timeval t1) {
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}


//init_pair(index, foreground, background);
void DefineColorsMenu() {
    init_pair(COR_MOTO, COLOR_BLUE, COLOR_BLUE);
    init_pair(COR_MOLDURA, COLOR_RED, COLOR_RED);
    init_pair(COR_PRETA, COLOR_BLACK, COLOR_BLACK);
    //init_pair(COR_DESCELECIONADO, COLOR_WHITE, 148);
}


void IniciaOpt (moto_t* player) {
    player->x = 5;
    player->y = 5;
    player->cor = COR_MOTO;
    player->dir = DIREITA;
}


void StartCurses() {
    initscr();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
}

void SelecionaMenu (int c, moto_t* player) {
    switch (c) {
        case 'w':
            player->dir = (player->dir == BAIXO? BAIXO : CIMA); 
        break;

        case 's':
            player->dir = (player->dir == CIMA? CIMA : BAIXO);
        break;

        case 'd':
            player->dir = (player->dir == ESQUERDA? ESQUERDA : DIREITA); 
        break;

        case 'a':
            player->dir = (player->dir == DIREITA? DIREITA : ESQUERDA);
        break;
    }
    return;
}


void moveJogador (moto_t* player) {
    if (player->dir == CIMA) {
        player->y--; 
    }
    else if (player->dir == BAIXO) {
        player->y++; 
    }
    else if (player->dir == ESQUERDA) {
        player->x--; 
    }
    else if (player->dir == DIREITA) {
        player->x++; 
    }
}


void desenhaMatriz (char* matriz) {
    for (int i = 0; i < MATRIZ_ALTURA; ++i) {
        for (int j = 0; j < MATRIZ_LARGURA; ++j) {
            if (matriz[(i*MATRIZ_ALTURA+j)] == '#') {
                attron(COLOR_PAIR(COR_MOLDURA));
                mvprintw(j, i*2, "##");
                attron(COLOR_PAIR(COR_PRETA));
            }
            else {
                attron(COLOR_PAIR(COR_PRETA));
                mvprintw(j, i*2, "  ");
            }
        }   
    }
}


void desenhaJogador (moto_t* player) {
    attron(COLOR_PAIR(player->cor));
    mvprintw(player->y, player->x*2, "@@");
    attron(COLOR_PAIR(COR_PRETA));
}


int AbreMenu (moto_t* jogador) {
    DefineColorsMenu();

    char* matriz = (char*) malloc (sizeof(char)*MATRIZ_ALTURA*MATRIZ_LARGURA);
    for (int i = 0; i < MATRIZ_ALTURA; ++i) {
        for (int j = 0; j < MATRIZ_LARGURA; ++j) {
            if (i == 0 || j == 0 || i == MATRIZ_ALTURA-1 || j == MATRIZ_LARGURA-1) {
                matriz[(i*MATRIZ_ALTURA+j)] = '#';
            }
            else {
                matriz[(i*MATRIZ_ALTURA+j)] = ' ';
            }
        }   
    }


    int n = 0, aux = 0;
    time_t antes, agora;
    time(&antes);
    //AnimaMenu(aux);
    aux = (aux%2) + 1;


    desenhaMatriz (matriz);


    struct timeval start, stop;
    double secs = 0;

    gettimeofday(&start, NULL);
    gettimeofday(&stop, NULL);

    
    // Começa a pegar as teclas
    double dif, intervalo = 75;
    char c = 0;
    while (c != 'q') { // Quando capturar um q, fecha o jogo
        c = getch();

        SelecionaMenu(c, jogador);

        refresh();
        //usleep(10000);

        gettimeofday(&stop, NULL);
        dif = timedifference_msec(start, stop);
        //printf("%d\n", dif);
        if (dif >= intervalo) {
            gettimeofday(&start, NULL);
            
        //for (int i = 0; i < nopt; i++) {
        desenhaJogador (jogador);

        moveJogador (jogador);
        //}


        }
    }
    return -1;
}

int main () {
    StartCurses();

    moto_t p1;
    IniciaOpt(&p1);

    int s = AbreMenu(&p1);
    
    // Fecha a janela da ncurses
    endwin();

    // printa só pra ficar bonito
    printf("%i\n", s);

    return 0;
}
