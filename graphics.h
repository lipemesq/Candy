#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "gameconfig.h"

void DefineColors();

void DesenhaArena();

void MostraTempo (float t);

void DesenhaPontos(float p);

void DesenhaSelect (int gx, int gy, int per);

void DesenhaDirEsteiras();
void DesenhaLinhaSelect (int gy, int per);
void DesenhaColunaSelect (int gx, int per);

void ExplodeEmAlegria (int gx, int gy, int cor);

void SetGraphics ();

void DesenhaMolduraPause ();

void PintaTudo(int h);

void DesenhaScores();

void EscreveAjuda();

void OFIMESTAPROXIMO (float p);
