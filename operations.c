#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "gameconfig.h"
#include "candycrush.h"
#include "operations.h"

int TemItemLinha (int px, int py, int e) {
    for (int i = 1; i < NX_MATRIZ; i++) {
        if (matriz[i][py] == e) return 1;
    }
    return 0;
}
int TemItemColuna (int px, int py, int e) {
    for (int i = 1; i < NY_MATRIZ; i++) {
        if (matriz[px][i] == e) return 1;
    }
    return 0;
}


int RandomFruit () {
    return ((rand() % N_FRUTAS) + N_PRIMEIRA_FRUTA);
}


void DesceFruta (int px, int py) {
    if ((px >= 1) && (px < NX_MATRIZ-1) && (py >= 1) && (py < NY_MATRIZ-1)){
        for (int i = py; (i > 1) && (i < NY_MATRIZ - 1); i--) {
            matriz[px][i] = matriz[px][i-1];
            Testar();
        }
        matriz[px][1] = RandomFruit();
    }
}

void MarcaSequenciaVertical (int px, int py, int e) {
    int i = py;
    while (i >= 1 && matriz[px][i-1] == e){
        i--;
    }
    while (i < NY_MATRIZ - 1 && matriz[px][i] == e){
		DesenhaSelect(px*3+1, i*2+1, 3);
		i++;
    }
	refresh();
	usleep(500000);
	printf("\7");
return;
}

void MarcaSequenciaHorizontal (int px, int py, int e) {
    int i = px;

    while ((i >= 1) && (i < NX_MATRIZ-1) && (matriz[i-1][py] == e)){
        i--;
    }
    while (((i < NX_MATRIZ - 1) && (matriz[i][py] == e))) {
		DesenhaSelect(i*3+1, py*2+1, 3);
        i++;
    }
	refresh();
	usleep(500000);
	printf("\a");
    return;
}

void DesceSequenciaVertical (int px, int py, int e) {
    int i = py;
    refresh();
    while (i >= 1 && matriz[px][i-1] == e){
        i--;
        refresh();
    }
    while (i < NY_MATRIZ - 1 && matriz[px][i] == e){
        DesceFruta(px, i);
        i++;
        refresh();
    }
}


void DesceSequenciaHorizontal (int px, int py, int deltaX, int e) {
    int i = px;
    while ((i >= 1) && (i < NX_MATRIZ-1) && (matriz[i-1][py] == e)){
        i--;
    }
    while (((i < NX_MATRIZ - 1) && (matriz[i][py] == e))) {
        if (i != px){
            DesceFruta(i, py);
        }
        i++;
    }
    return;
}


int BuscaSequenciaVertical (int px, int py, int e) {
    int i = py, s = 0;

    while (i > 1 && matriz[px][i-1] == e){
        i--;
    }
    while ((i < NY_MATRIZ - 1) && (matriz[px][i] == e)){
        s++;
        i++;
    }
	
    return s;
}

int BuscaSequenciaHorizontal (int px, int py, int e) {
    int i = px, s = 0;

    while ((i > 1) && (matriz[i-1][py] == e)){
        i--;
    }
    while (((i < NX_MATRIZ - 1) && (matriz[i][py] == e))) {
        s++;
        i++;
    }
    return s;
}


void DeslizaLinha (int px, int py, int sentido) {
    int aux;
    if (sentido > 0) {
        aux = matriz[NX_MATRIZ-2][py];
        for (int i = NX_MATRIZ-2; i > 1; i--) {
            matriz[i][py] = matriz[i-1][py];
        }
        matriz[1][py] = aux;
    }
    else if (sentido < 0) {
        aux = matriz[1][py];
        for (int i = 1; i < NX_MATRIZ-2; i++) {
            matriz[i][py] = matriz[i+1][py];
        }
        matriz[NX_MATRIZ-2][py] = aux;
    }
}


void DeslizaColuna (int px, int py, int sentido) {
    int aux;
    if (sentido > 0) {
        aux = matriz[px][1];
        for (int i = 1; i < NY_MATRIZ-2; i++) {
            matriz[px][i] = matriz[px][i+1];
        }
        matriz[px][NY_MATRIZ-2] = aux;
    }
    else if (sentido < 0) {
        aux = matriz[px][NY_MATRIZ-2];
        for (int i = NY_MATRIZ-2; i > 1; i--) {
            matriz[px][i] = matriz[px][i-1];
        }
        matriz[px][1] = aux;
    }
}


int PossibilidadeAcimaDireita (int e, int x, int y) {
    int ax = x, ay = y;

    ax = x+3;
    if (ax < NX_MATRIZ - 1) {
        if ((matriz[ax][y] == e) && (matriz[ax-1][y] == e)) {
            return true;
        }
    }
    ax = x+2;
    ay = y-1;
    if ((ax < NX_MATRIZ - 1) && (ay >= 1)) {
        if ((matriz[ax][ay] == e) && (matriz[ax-1][ay] == e)) {
            return true;
        }
    }
    ay = y-3;
    if (ay >= 1) {
        if ((matriz[x][ay] == e) && (matriz[x][ay+1] == e)) {
            return true;
        }
    }
    ax = x-2;
    ay = y-1;
    if ((ax >= 1) && (ay >= 1)) {
        if ((matriz[ax][ay] == e) && (matriz[ax+1][ay] == e)) {
            return true;
        }
    }
        //printf("DIREITA");
    return false;
}

int PossibilidadeAbaixoEsquerda (int e, int x, int y) {
    int ax = x, ay = y;

    ax = x-3;
    if (ax >= 1) {
        if ((matriz[ax][y] == e) && (matriz[ax+1][y] == e)) {
            return true;
        }
    }
    ax = x-2;
    ay = y+1;
    if ((ax >= 1) && (ay < NY_MATRIZ-1)) {
        if ((matriz[ax][ay] == e) && (matriz[ax+1][ay] == e)) {
            return true;
        }
    }
    ay = y+3;
    if (ay < NY_MATRIZ-1) {
        if ((matriz[x][ay] == e) && (matriz[x][ay-1] == e)) {
            return true;
        }
    }
    ax = x+2;
    ay = y+1;
    if ((ax < NX_MATRIZ-1) && (ay < NY_MATRIZ-1)) {
        if ((matriz[ax][ay] == e) && (matriz[ax-1][ay] == e)) {
            return true;
        }
    }
    //printf("ESQUERDA");
    return false;
}
