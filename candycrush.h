#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "gameconfig.h"
#include "operations.h"
#include "graphics.h"

enum Movimento {
    Horizontal, Vertical
} Movimento;


int matriz[NX_MATRIZ][NY_MATRIZ];
int mGrafica[NX_GRAFICA][NY_GRAFICA];

int px, py;
int gx, gy;

typedef struct oSave {
    float pontuacao;
    int matriz[NX_MATRIZ][NY_MATRIZ];
} oSave;

void IniciaTempo();

float AtualizaTempo (float t);

void StartCurses();

void SetBackup ();

void LoadBackup ();

void CarregaPlacar ();
void SetPlacar (float p);
void MostraPlacar ();

void MostrarAjuda();

void Testar ();

void AnimaExplode (int px, int py);

void FecharJogo ();

void SalvarJogo(float p);
float LoadJogo ();

void MostraMatriz();

void CriaMatriz ();

void DesenhaEsteiras();

void DesenhaSelection (int per);
void DesenhaLinhaSelecionada (int per);
void DesenhaColunaSelecionada (int per);

void MoveSelection (int c);

void MoveLineCol (int c);

float MarcaPontos (int px, int py, float mult);

float MarcaPontosExtras ();

float Pontua ();

int VerificaFimDeJogo ();

void DesenhaMoldPause();

void LimpaTela(int h);

void FimDeUmJogo(float p);
