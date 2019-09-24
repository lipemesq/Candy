#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>

#define COR_SELECIONADO 11
#define COR_DESCELECIONADO 12

typedef struct OPTION {
    int x, y;
    char *frase;
    int cor;
}  OPTION;

void DefineColorsMenu();

void IniciaOpt (OPTION opt[], int nopt);

void SelecionaMenu (int c, int *n, int nopt);

int AbreMenu (OPTION opt[], int nopt);

void AnimaMenu(int aux);
