#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "candycrush.h"

int main() {

    srand(time(NULL));

    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            if (i == 0 || j == 0) matriz[i][j] = BORDA;
            else if (i +1 == NX_MATRIZ || j +1 == NY_MATRIZ) matriz[i][j] = BORDA;
            else matriz[i][j] = RandomFruit();
        }
    }

    SetGraphics();

    MostraMatriz();
    EncontraSequencia();

    StartCurses();

    DefineColors();

    int c = 1, status = 1, nx = -1, ny = -1, aux;
    while (c != 'q') {
        SetGraphics();
        DesenhaArena();

        c = getch();
        if (c == 'k') {
            if (status == 1){
                status = 2;
                nx = px; ny = py;
            }
            else if (status == 2){
                status = 1;
                aux = matriz[px][py];
                matriz[px][py] = matriz[nx][ny];
                matriz[nx][ny] = aux;
                EncontraSequencia();
                nx = -1; ny = -1;
            }
        }
        if (status == 1) {
            MoveSelection(c, matriz, &px, &py);
        }
        else if (status == 2) {
            MoveSelectionWithRestriction (c, matriz, &px, &py, nx, ny);
        }

        attron(COLOR_PAIR(LETRAS));
        mvprintw(17, 0, "%i %i", px, py);


        if (nx != -1) {
            DesenhaSelect(nx*2+1, ny*2+1, ESP_SELECT);
            //mvprintw(ny*2+1, nx*2+1, "!");
        }
        DesenhaSelect(gx, gy, SELECT);
        refresh();

        usleep(DELAY);
        if (VerificaFimDeJogo() == true){
            endwin();

            exit(0);
        }
    }

    endwin();

}
