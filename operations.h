#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "gameconfig.h"

int TemItemLinha (int px, int py, int e);
int TemItemColuna (int px, int py, int e);

int RandomFruit ();

void DesceFruta (int px, int py);

void MarcaSequenciaVertical (int px, int py, int e);
void MarcaSequenciaHorizontal (int px, int py, int e);

void DesceSequenciaVertical (int px, int py, int e);
void DesceSequenciaHorizontal (int px, int py, int deltaX, int e);

int BuscaSequenciaVertical (int px, int py, int e);
int BuscaSequenciaHorizontal (int px, int py, int e);


void DeslizaLinha (int px, int py, int sentido);
void DeslizaColuna (int px, int py, int sentido);

int PossibilidadeAcimaDireita (int e, int x, int y);

int PossibilidadeAbaixoEsquerda (int e, int x, int y);
