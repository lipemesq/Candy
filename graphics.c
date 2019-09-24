#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "gameconfig.h"
#include "graphics.h"


void DefineColors() {
	init_color(150, 250*4, 125*4, 0);
	init_pair(LARANJA, COLOR_WHITE, 150);

	init_color(151, 240*4, 0, 0);
	init_pair(VERMELHO, COLOR_WHITE, 151);

	init_color(152, 10*4, 225*4, 50*4);
	init_pair(VERDE, COLOR_WHITE, 152);

	init_color(153, 250*4, 250*4, 0);
	init_pair(AMARELO, COLOR_WHITE, 153);

	init_color(154, 0, 100*4, 250*4);
	init_pair(AZUL, COLOR_WHITE, 154);
	
	init_color(155, 105*4, 0, 250*4);
	init_pair(ROXO, COLOR_WHITE, 155);

	init_color(156, 250*4, 0, 157*4);
	init_pair(ROSA, COLOR_WHITE, 156);
	
    init_color(149, 90*3, 70*3, 50*3);
    init_pair(BORDA, 149, 149);

	init_color(148, 40*3, 35*3, 25*3);
    init_pair(FUNDO_MENU, 148, 148);

	init_color(147, 250*4, 212*4, 0);
    init_pair(COR_MOV_DECIDIU, 147, 149);
    init_pair(184, 147, 148);

	init_color(205, 128*4, 128*4, 128*4);
    init_pair(PEDRA, 205, 205);

	init_color(142, 215*4, 199*4, 150*4); // CREME

	init_pair(COR_LETRA_MENU, 142, 148);
	init_pair(COR_LETRA_JOGO, 142, 149);
	
	init_pair(COR_MOV_INVALIDO, 151, 149);
    init_pair(SELECT, 149, COLOR_WHITE);
	init_pair(ESP_SELECT, COLOR_WHITE, 149);
    init_pair(LETRAS, COLOR_WHITE, 149);
}

void DesenhaArena() {
    for (int j = 0; j < NY_GRAFICA; j++) {
        for (int i = 0; i < NX_GRAFICA; i++) {
            attron(COLOR_PAIR(mGrafica[i][j]));
            mvprintw(j+DY, i+DX, ":"); //addch(ACS_DIAMOND);
        }
    }
	attron(COLOR_PAIR(SELECT));
	for (int i = 3; i < NX_GRAFICA-1; i++) {
		mvprintw(1+DY, i+DX, ""); addch(ACS_HLINE);
		mvprintw(NY_GRAFICA-1+DY, i+DX, ""); addch(ACS_HLINE);
	}
	for (int j = 2; j < NY_GRAFICA-1; j++) {
		mvprintw(j+DY, 2+DX, ""); addch(ACS_VLINE);
		mvprintw(j+DY, DX+NX_GRAFICA-1, ""); addch(ACS_VLINE);
	}
	mvprintw(1+DY, DX+2, ""); addch(ACS_ULCORNER);
	mvprintw(1+DY, DX+NX_GRAFICA-1, ""); addch(ACS_URCORNER);
	mvprintw(NY_GRAFICA-1+DY, DX+2, ""); addch(ACS_LLCORNER);
	mvprintw(NY_GRAFICA-1+DY, DX+NX_GRAFICA-1, ""); addch(ACS_LRCORNER);
}

void MostraTempo (float t) {
	attron(COLOR_PAIR(COR_LETRA_JOGO));
	mvprintw(TEMPO_Y, TEMPO_X, "Segundos restantes: ");
	attron(COLOR_PAIR(COR_MOV_DECIDIU));
	printw("%3.0f", t);
}

void DesenhaPontos(float p) {
    attron(COLOR_PAIR(COR_LETRA_JOGO));
    mvprintw(PONTOS_Y, PONTOS_X, "Pontos: ");
	attron(COLOR_PAIR(COR_MOV_DECIDIU));
	printw("%.2f", p);
}

void DesenhaLinhaSelect (int gy, int per) {
	if (per == MOV_INVALIDO) attron(COLOR_PAIR(COR_MOV_INVALIDO));
	else if (per == Movendo) attron(COLOR_PAIR(COR_MOV_DECIDIU));
	else attron(COLOR_PAIR(ESP_SELECT));
	for (int j = 3; j < NX_GRAFICA-1; j++) {
		mvprintw(gy-1+DY, DX+j, ""); addch(ACS_HLINE);
		mvprintw(gy+1+DY, DX+j, ""); addch(ACS_HLINE);
	}

} 

void DesenhaColunaSelect (int gx, int per) {
	if (per == MOV_INVALIDO) attron(COLOR_PAIR(COR_MOV_INVALIDO));
	else if (per == Movendo) attron(COLOR_PAIR(COR_MOV_DECIDIU));
	else attron(COLOR_PAIR(ESP_SELECT));
	for (int i = 2; i < NY_GRAFICA-1; i++) {
		mvprintw(i+DY, DX+gx-1, ""); addch(ACS_VLINE);
		mvprintw(i+DY, DX+gx+1, ""); addch(ACS_VLINE);
	}

} 

void DesenhaSelect (int gx, int gy, int per) {
	if (per == Movendo) attron(COLOR_PAIR(COR_MOV_DECIDIU));
	else attron(COLOR_PAIR(ESP_SELECT));

    mvprintw(gy-1+DY, DX+gx-1, "");  addch(ACS_ULCORNER); addch(ACS_HLINE); addch(ACS_URCORNER);
    mvprintw(gy+DY, DX+gx-1, ""); addch(ACS_VLINE); mvprintw(gy+DY, DX+gx+1, ""); addch(ACS_VLINE);
    mvprintw(gy+1+DY, DX+gx-1, "");  addch(ACS_LLCORNER); addch(ACS_HLINE); addch(ACS_LRCORNER);

}

void DesenhaDirEsteiras () {
	attron(COLOR_PAIR(LETRAS));
	for (int j = 1; j < NX_MATRIZ-1; j++) {
		if (direcCol[j] == Indefinido) mvprintw(NY_GRAFICA-2+DY, j*3+1+DX, "o");
		else if (direcCol[j] == PraCima) mvprintw(NY_GRAFICA-2+DY, j*3+1+DX, "|");  
		else if (direcCol[j] == PraBaixo) mvprintw(NY_GRAFICA-2+DY, j*3+1+DX, "V");     
	}

	for (int i = 1; i < NY_MATRIZ-1; i++) {
		if (direcLine[i] == Indefinido) mvprintw(i*2+1+DY, NX_GRAFICA-3+DX, "o");
		else if (direcLine[i] == Direita) mvprintw(i*2+1+DY, NX_GRAFICA-3+DX, ">");
		else if (direcLine[i] == PraBaixo) mvprintw(i*2+1+DY, NX_GRAFICA-3+DX, "<");
	}
}

void ExplodeEmAlegria (int gx, int gy, int cor) {
    attron(COLOR_PAIR(cor));
    mvprintw(gy-1, gx-1, "#");  mvprintw(gy-1, gx, "#");  mvprintw(gy-1, gx+1, "#");
    mvprintw(gy, gx-1, "#");                              mvprintw(gy, gx+1, "#");
    mvprintw(gy+1, gx-1, "#");  mvprintw(gy+1, gx, "#");  mvprintw(gy+1, gx+1, "#");
}

void SetGraphics () {
    for (int j = 0; j < NY_GRAFICA; j++) {
        for (int i = 0; i < NX_GRAFICA; i++) {
            mGrafica[i][j] = BORDA;
        }
    }

    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            mGrafica[i*3+1][j*2+1] = matriz[i][j];
        }
    }
}

void DesenhaMolduraPause () {
	attron(COLOR_PAIR(FUNDO_MENU));
	for (int i = 3; i < NX_GRAFICA-1; i++) {
		for (int j = 2; j < NY_GRAFICA-1; j++) {
			attron(COLOR_PAIR(FUNDO_MENU));
			mvprintw(j+DY, i+DX, " ");    
		}
	}
}

void PintaTudo (int h) {
	if (h == 1) {
		attron(COLOR_PAIR(FUNDO_MENU));
	}
	else if (h == 2) {
		attron(COLOR_PAIR(BORDA));
	}
	for (int i = 0; i < NX_GRAFICA+MARGEM_LATERAL+DX; i++) {
		for (int j = 0; j < NY_GRAFICA+DY+DY; j++) {
			mvprintw(j, i, "a");    
		}
	}
	refresh();
}

void DesenhaScores () {
	attron(COLOR_PAIR(FUNDO_MENU));
	for (int i = SCORES_X-4; i < SCORES_X+16; i++) {
		for (int j = SCORES_Y-3; j < SCORES_Y+10; j++) {
			mvprintw(j, i, " ");    
		}
	}
	
	attron(COLOR_PAIR(COR_LETRA_MENU));
	mvprintw(SCORES_Y-2, SCORES_X+1, "HIGSCORES:");
	for (int i = 0; i < N_SCORES; i++) {
		mvprintw(SCORES_Y+i, SCORES_X, "%c%c%c%c: %7.2f", scores->nome[i][0], scores->nome[i][1], scores->nome[i][2], scores->nome[i][3], scores->best[i]);
	}
	mvprintw(SCORES_Y+11, SCORES_X-3, "'SPACE' para voltar\0");
}

void EscreveAjuda () {
	attron(COLOR_PAIR(COR_LETRA_MENU));
	mvprintw(1, 1, "AJUDA:");
	mvprintw(3, 0, "    Esse jogo consiste em tentar formar o maior numero possivel de grandes sequencias de doces (cores). As sequencias sao feitas somente na vertical e horizontal, e precisam ter no minimo 3 elementos em cadeia.");
	mvprintw(8, 0, "    Use as teclas 'w', 'a', 's' e 'd' para movimentar a selecao. Uma vez posicionado no bloco desejado, pressione 'ENTER' para comecar a mover aquela liha ou coluna. Quando estiver pronto, pressione 'ENTER' novamente para completar o movimento. Essa jogada so contara pontos se houver uma sequencia no bloco selecionado.");   
	mvprintw(15, 0, "    Leembra-se: linhas e colunas com pedras nao podem ser movidas, e uma fila ou coluna movida num sentido, nunca mais podera ser movido no outro sentido."); 
	mvprintw(19, 0, "    Depois de contar os pontos a partir do bloco selecionado, outras sequencias pelo mapa serao fechadas tambem, porem valendo menos pontos. Quando uma sequencia e fechada, os blocos acima caem, gerando novos doces no topo.");
	mvprintw(24, 0, "    Voce pode apertar 'q' para pausar o jogo e  'h' para abrir novamente esta pagina de ajuda. Divirta-se! C:");    
	mvprintw(29, 6, "    Pressione 'SPACE' para voltar."); 
}

void OFIMESTAPROXIMO (float p) {
	attron(COLOR_PAIR(COR_LETRA_MENU));
	mvprintw (7, 19, "PARABENS!");
	mvprintw (9, 14, "SUA PONTUACAO FOI:");
	attron(COLOR_PAIR(184));
	mvprintw (10, 18, "%7.2f", p);
	attron(COLOR_PAIR(COR_LETRA_MENU));
	mvprintw (12, 19, "SEU ID:");
	refresh();
	usleep(500000);
	echo();
	nodelay(stdscr, FALSE);
	refresh();
	attron(COLOR_PAIR(184));
	scanf("%c", &id[0]);
	mvprintw (14, 19, "%c", id[0]);
	refresh();
	scanf("%c", &id[1]);
	mvprintw (14, 21, "%c", id[1]);
	refresh();
	scanf("%c", &id[2]);
	mvprintw (14, 23, "%c", id[2]);
	refresh();
	scanf("%c", &id[3]);
	mvprintw (14, 25, "%c", id[3]);
	refresh();
	usleep(3000000);
}



