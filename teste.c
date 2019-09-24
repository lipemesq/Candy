#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>

int matriz[5][4] = {{0, 0, 0, 0, 0},
                   {0, 2, 3, 3, 0},
                   {0, 1, 1, 1, 0},
                   {0, 0, 0, 0, 0}};

                   // COPIAR E TESTAR

int px = 2, py = 2;


int RandomFruit () {
    return (rand() % 5 + 1);
}

void DesenhaArena() {
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 5; i++) {
            //attron(COLOR_PAIR(mGrafica[i][j]));
            printf("%i ", matriz[j][i]);
        }
        printf("\n");
    }
}

void DesceFruta (int px, int py) {
   for (int i = py; i > 1; i--) {
       matriz[px][py] = matriz[px][py - 1];
   }
   matriz[px][1] = RandomFruit();
}


void DesceSequencia (int px, int py, int deltaX, int deltaY, int e) {
    int m = 0, n = 0;
    for (int i = 0; matriz[px + deltaX*i][py + deltaY*i] == e; i--) {
        m = i;
    }
    //printf("m = %i\nmatriz[px + deltaX*i][py + deltaY*i] = ", m, matriz[px + deltaX*m][py + deltaY*m]);
    for (int i = m; matriz[px + deltaX*i][py + deltaY*i] == e; i++) {
        printf("%i\n",matriz[px + deltaX*i][py + deltaY*i]);
        DesenhaArena();
        //matriz[py + deltaY*i][px + deltaX*i] = 0;
        DesceFruta(px + deltaX*i, py + deltaY*i);
    }
    int i = m;
    printf("OQ: %i\n", matriz[px + deltaX*i][py + deltaY*i]);
    i++;
    printf("OQ: %i\n", matriz[px + deltaX*i][py + deltaY*i]);
   return;
}


int BuscaSequencia (int px, int py, int deltaX, int deltaY, int tseq) {
   if (matriz[px][py] == matriz[px+deltaX][py+deltaY]) {
       tseq++;
       return BuscaSequencia(px+deltaX, py+deltaY, deltaX, deltaY, tseq);
   }
   return tseq;
}


int Pontua () {
    int tamSeqX = 0, tamSeqY = 0;

        //printf("Pra esquerda: %d\n", BuscaSequencia(py, px, 0, -vx, 0));
        tamSeqX += BuscaSequencia(px, py, 0, -1, 0);
        //printf("Pra direita: %d\n", BuscaSequencia(py, px, 0, vx, 0));
        tamSeqX += BuscaSequencia(px, py, 0, 1, 0);

        //printf("Pra Cima: %d\n", BuscaSequencia(py, px, -vy, 0, 0));
        tamSeqY += BuscaSequencia(px, py, 1, 0, 0);
        //printf("Pra Baixo: %d\n", BuscaSequencia(py, px, vy, 0, 0));
        tamSeqY += BuscaSequencia(px, py, -1, 0, 0);

        tamSeqX++; tamSeqY++;

        printf("%d\n", tamSeqY);
        int e =  matriz[px][py];

        if (tamSeqX >= 3 && tamSeqY >= 3) {
            printf("Uma cruz\n");
        }
        else if (tamSeqX >= 2) {
            printf("Uma linha\n");
            //DesceSequencia(px, py, -1, 0, e);
            DesceSequencia(px, py, 1, 0, e);
        }
        else if (tamSeqY >= 2) {
            printf("Uma coluna\n");
            DesceSequencia(px, py, 0, 1, e);
            //DesceSequencia(px, py, 0, -1, e);
        }

        return 1;
}

int main() {

    DesenhaArena();

    printf("%d\n", Pontua());

    DesenhaArena();

}
