#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "menu.h"
#include "gameconfig.h"

void DefineColorsMenu() {
    init_pair(COR_SELECIONADO, COLOR_WHITE, COLOR_BLUE);
	init_color(148, 40*3, 35*3, 25*3); // MARROM ESCURO
	init_color(147, 250*4, 212*4, 0); // DOURADO
	init_color(142, 215*4, 199*4, 150*4); // CREME
    init_pair(COR_DESCELECIONADO, COLOR_WHITE, 148);
	init_pair(200, 147, 148);
	init_pair(201, 142, 148); // COR PALAVRA
}

void IniciaOpt (OPTION opt[], int nopt) {
    for (int i = 0; i < nopt; i++) {
        opt[i].x = 0;
        opt[i].y = i;
        opt[i].cor = COR_DESCELECIONADO;
    }
}

void SelecionaMenu (int c, int *n, int nopt) {
    switch (c) {
        case 'w':
            *n = (*n > 0? *n-1 : nopt-1);
            usleep(10000); break;

        case 's':
            *n = (*n < nopt-1? *n+1 : 0); break;
    }
    return;
}

int AbreMenu (OPTION opt[], int nopt) {
    DefineColorsMenu();
    //IniciaOpt(opt, nopt);
    int n = 0, aux = 0;
	time_t antes, agora;
	antes = time(NULL);
	AnimaMenu(aux);
	aux = (aux%2) + 1;

    char c = 0;
    while (c != 'q') {
        c = getch();
        if (c == '\n') return n;
        SelecionaMenu(c, &n, nopt);

        for (int i = 0; i < nopt; i++) {
            if (n == i) {
                opt[i].cor = COR_SELECIONADO;
            }
            else {
                opt[i].cor = 201;
            }
        }

        for (int i = 0; i < nopt; i++) {
            attron(COLOR_PAIR(opt[i].cor));
            mvprintw(opt[i].y+DY, DX+opt[i].x, "%s", opt[i].frase);
        }
		agora = time(NULL);
		if (difftime(agora, antes) >= 0.5) {
			AnimaMenu(aux);
			aux = (aux%2) + 1;
			antes = time(NULL);
		}
        refresh();
		usleep(500);
    }
    return -1;
}

void AnimaMenu (int aux) {
	attron(COLOR_PAIR(200));
	for (int i = 5; i < NX_GRAFICA-3; i++) {
		if (((aux + i) % 2) == 0) {
			mvprintw(NY_GRAFICA-3+DY, i+DX, "+");
			mvprintw(3+DY, i+DX, "+");
		}
		else {
			mvprintw(NY_GRAFICA-3+DY, DX+i, "-");
			mvprintw(3+DY, DX+i, "-");
		}
	}

	for (int j = 4; j < NY_GRAFICA-3; j++) {
		if (((aux + j) % 2) == 0) {
			mvprintw(j+DY, DX+NX_GRAFICA-4, "+");
			mvprintw(j+DY, 5+DX, "+");
		}
		else {
			mvprintw(j+DY, DX+NX_GRAFICA-4, "|");
			mvprintw(j+DY, DX+5, "|");
		}
	}
}
