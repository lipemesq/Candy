#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include "gameconfig.h"
#include "operations.h"
#include "graphics.h"

int px = START_X, py = START_Y;
int gx = START_X*3+1, gy = START_Y*2+1;

time_t antes, agora, restante;

enum Movimento {
    Horizontal, Vertical
} Movimento;


typedef struct oSave {
    float pontuacao;
    int matriz[NX_MATRIZ][NY_MATRIZ];
	int direcLine[NY_MATRIZ];
	int direcCol[NX_MATRIZ];
} oSave;

void IniciaTempo() {
	antes = time(NULL);
}

float AtualizaTempo (float t) {
	time(&agora);
	MostraTempo(t);
	return difftime(agora, antes);
}

void StartCurses() {
    initscr();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
	DefineColors();
	srand(time(NULL));
	resizeterm(NY_GRAFICA+DY+DY, NX_GRAFICA+MARGEM_LATERAL+DX);
}

void MostraMatriz() {
    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            printf("%i ", matriz[i][j]);
        }
        printf("\n");
    }
}


void SetBackup () {
    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            mBackup[i][j] = matriz[i][j];
        }
    }
}

void LoadBackup () {
    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            matriz[i][j] = mBackup[i][j];
        }
    }
}


void FecharJogo () {
    endwin();
    exit(0);
}


void SalvarJogo (float p) {
    oSave *save = calloc (1, sizeof(oSave));
    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            save->matriz[i][j] = matriz[i][j];
        }
    }
	for (int j = 0; j < NY_MATRIZ; j++) {
		save->direcLine[j] = direcLine[j];
	}
	for (int i = 0; i < NX_MATRIZ; i++) {
    	save->direcCol[i] = direcCol[i];
    }
    save->pontuacao = p;
//printf ("PONTUAÇAO SALVA = %f", save->pontuacao);
    FILE  * arq = fopen("save.bin", "w+");
    fwrite(save, sizeof(oSave), 1, arq);
    fclose(arq);
	free(save);
}

float LoadJogo () {
    FILE  * arq = fopen("save.bin", "r");
    oSave *save = calloc(1, sizeof(oSave));
    fread(save, sizeof(oSave), 1, arq);
    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            matriz[i][j] = save->matriz[i][j];
        }
    }
	for (int j = 0; j < NY_MATRIZ; j++) {
		direcLine[j] = save->direcLine[j];
	}
	for (int i = 0; i < NX_MATRIZ; i++) {
    	direcCol[i] = save->direcCol[i];
    }
	float pts = save->pontuacao;
	fclose(arq);
	free(save);
	DefineColors();
    return pts;
}


void CarregaPlacar () {
	scores = calloc(1, sizeof(Placar));
	FILE  * arqx = fopen("scores.bin", "r");
	if (!arqx) {
		for (int i = 0; i < N_SCORES; i++) {
			scores->best[i] = 0;
			scores->nome[i][0] = '-';
			scores->nome[i][1] = '-';
			scores->nome[i][2] = '-';
			scores->nome[i][3] = '-';
		}
	} 
	else {
		fread(scores, sizeof(Placar), 1, arqx);
		fclose(arqx);
	}
}

void SetPlacar (float p) {
	for (int i = 0; i < N_SCORES; i++) {
		if (p >= scores->best[i]) {
			for (int j = N_SCORES-1; j > i; j--) {
				scores->best[j] = scores->best[j-1];
			}
			scores->best[i] = p;
			scores->nome[i][0] = id[0];
			scores->nome[i][1] = id[1];
			scores->nome[i][2] = id[2];
			scores->nome[i][3] = id[3];
			break;
		} 
	}
	FILE  * arq = fopen("scores.bin", "w");
	fwrite(scores, sizeof(Placar), 1, arq);
	fclose(arq);
}

void LimpaTela(int h) {
	PintaTudo(h);
}

void AnimaChamp (int aux) {
	attron(COLOR_PAIR(184));
	for (int i = 5; i < NX_GRAFICA-3; i++) {
		if (((aux + i) % 2) == 0) {
			mvprintw(NY_GRAFICA-3+DY, i+DX, "*");
			mvprintw(3+DY, i+DX, "*");
		}
		else {
			mvprintw(NY_GRAFICA-3+DY, DX+i, "=");
			mvprintw(3+DY, DX+i, "=");
		}
	}

	for (int j = 4; j < NY_GRAFICA-3; j++) {
		if (((aux + j) % 2) == 0) {
			mvprintw(j+DY, DX+NX_GRAFICA-4, "*");
			mvprintw(j+DY, 5+DX, "*");
		}
		else {
			mvprintw(j+DY, DX+NX_GRAFICA-4, ":");
			mvprintw(j+DY, DX+5, ":");
		}
	}
}

void MostraPlacar () {
	int aux = 0;
	time_t antesb, agorab;
	antesb = time(NULL);
	AnimaChamp(aux);
	aux = (aux%2) + 1;
	char k = 0;
	DesenhaScores ();
	refresh();
	while (k != ' ') {
		agorab = time(NULL);
		if (difftime(agorab, antesb) >= 0.5) {
			AnimaChamp(aux);
			aux = (aux%2) + 1;
			antesb = time(NULL);
			refresh();
		}
		k = getch();
	}
	return;
}

void MostrarAjuda() {
	LimpaTela(1);
	EscreveAjuda();
	refresh();
	char a = 0;
	while (a != ' ') {
		a = getchar();
	}
	LimpaTela(1);
}

void CriaMatriz () {
    for (int j = 0; j < NY_MATRIZ; j++) {
        for (int i = 0; i < NX_MATRIZ; i++) {
            if (i == 0 || j == 0) matriz[i][j] = BORDA;
            else if (i +1 == NX_MATRIZ || j +1 == NY_MATRIZ) matriz[i][j] = BORDA;
            else matriz[i][j] = RandomFruit();
        }
        direcLine[j] = Indefinido;
        direcCol[j] = Indefinido;
    }
	
	int xp, yp;
	for (int p = 0; p < N_PEDRAS; p++) {
		xp = (rand() % (NX_MATRIZ-2)) + 1;
		yp = (rand() % (NY_MATRIZ-2)) + 1;
		matriz[xp][yp] = PEDRA;
	}
    DefineColors();

}

void DesenhaEsteiras() {
	DesenhaDirEsteiras();
}

void DesenhaSelection (int per) {
    DesenhaSelect(gx, gy, per);
}

void DesenhaLinhaSelecionada (int per) {
	DesenhaLinhaSelect (gy, per);
}
void DesenhaColunaSelecionada (int per) {
	DesenhaColunaSelect (gx, per);
}


void MoveSelection (int c) {
    //mvprintw(17, 0, "%i %i", px, py);
    switch (c) {
        case 'a':
            px = (matriz[px-1][py] != BORDA? px - 1 : px); break;
        case 'w':
            py = (matriz[px][py-1] != BORDA? py - 1 : py); break;
        case 'd':
            px = (matriz[px+1][py] != BORDA? px + 1 : px); break;
        case 's':
            py = (matriz[px][py+1] != BORDA? py + 1 : py); break;
    }
    gx = px*3+1;
    gy = py*2+1;
}


void MoveLineCol (int c) {

    switch (c) {
        case 'a':   // Moveu a linha para a esquerda
        if (!TemItemLinha(px, py, PEDRA)) {
            if (direcLine[py] == Esquerda) DeslizaLinha(px, py, -1);
            else if (direcLine[py] == Indefinido) {
                direcLine[py] = Esquerda;
                DeslizaLinha(px, py, -1);
            }
			else {
				DesenhaLinhaSelect(gy, MOV_INVALIDO);
				refresh();
				usleep(50000);
			}
        }
		else {
			DesenhaLinhaSelect(gy, MOV_INVALIDO);
			refresh();
			usleep(50000);
		}
        break;

        case 'w':   // Moveu a coluna para cima
        if (!TemItemColuna(px, py, PEDRA)) {
            if (direcCol[px] == PraCima) DeslizaColuna(px, py, 1);
            else if (direcCol[px] == Indefinido) {
                direcCol[px] = PraCima;
                DeslizaColuna(px, py, 1);
            }
			else {
				DesenhaColunaSelect(gx, MOV_INVALIDO);
				refresh();
				usleep(50000);
			}
        }
		else {
			DesenhaColunaSelect(gx, MOV_INVALIDO);
			refresh();
			usleep(50000);
		}
        break;

        case 'd':   // Moveu a linha para a direita
        if (!TemItemLinha(px, py, PEDRA)) {
            if (direcLine[py] == Direita) DeslizaLinha(px, py, 1);
            else if (direcLine[py] == Indefinido) {
                direcLine[py] = Direita;
                DeslizaLinha(px, py, 1);
            }
			
			else {
				DesenhaLinhaSelect(gy, MOV_INVALIDO);
				refresh();
				usleep(50000);
			}
        }
		else {
			DesenhaLinhaSelect(gy, MOV_INVALIDO);
			refresh();
			usleep(50000);
		}
        break;

        case 's':   // Moveu a coluna para baixo
        if (!TemItemColuna(px, py, PEDRA)) {
            if (direcCol[px] == PraBaixo) DeslizaColuna(px, py, -1);
            else if (direcCol[px] == Indefinido) {
                direcCol[px] = PraBaixo;
                DeslizaColuna(px, py, -1);
            }
			else {
				DesenhaColunaSelect(gx, MOV_INVALIDO);
				refresh();
				usleep(50000);
			}
        }
		else {
			DesenhaColunaSelect(gx, MOV_INVALIDO);
			refresh();
			usleep(50000);
		}
        break;


    }
    gx = px*3+1;
    gy = py*2+1;
}


float MarcaPontos (int px, int py, float mult) {
    float pontos = 0;
    int e = matriz[px][py];
    int tamSeqX, tamSeqY;

    if ((px >= 1) && (px < NX_MATRIZ-1) && (py >= 1) && (py < NY_MATRIZ-1))
    {
        tamSeqX = BuscaSequenciaHorizontal(px, py, e);

    tamSeqY = BuscaSequenciaVertical(px, py, e);

    //tamSeqX++; tamSeqY++;
    attron(COLOR_PAIR(LETRAS));
    if (tamSeqX >= 3 && tamSeqY >= 3) {
        //mvprintw(0,24, "Cruz, x: %d, y: %d ", px, py);
        pontos += (tamSeqX*1.5 + tamSeqY*1.5) * mult;
		MarcaSequenciaVertical (px, py, e);
		MarcaSequenciaHorizontal (px, py, e);
        DesceSequenciaHorizontal(px, py, 1, e);
        DesceSequenciaVertical(px, py, e);
    }
    else if (tamSeqX >= 3) {
        //mvprintw(0,24, "Linha, x: %d, y: %d ", px, py);
        pontos += tamSeqX * mult;
		MarcaSequenciaHorizontal (px, py, e);
        DesceSequenciaHorizontal(px, py, 1, e);
        DesceFruta(px, py);
    }
    else if (tamSeqY >= 3) {
        //mvprintw(0,24, "Coluna, x: %d, y: %d ", px, py);
        refresh();
        pontos += tamSeqY * mult;
		MarcaSequenciaVertical (px, py, e);
        DesceSequenciaVertical(px, py, e);
    }
    else pontos = 0;
    }
    return pontos;
}


float MarcaPontosExtras () {
    float pExtras, pExtrasTotais = 0;
    do {
        pExtras = 0;
        for (int j = 1; j < NY_MATRIZ-1; j++) {
            for (int i = 1; i < NX_MATRIZ-1; i++) {
                //p = 0;
                //p = MarcaPontos(i, j, 0.5);
                //while (p != 0) {
                pExtras += MarcaPontos(i, j, 0.5);
                //mvprintw(2,24, "pExtras: %f ", pExtras);
                //refresh();
                //    p = 0;
                //    p = MarcaPontos(i, j, 0.5);
                    //p = MarcaPontosExtras();
                //}
            }
        }
        //mvprintw(3,24, "pExtras: %f ", pExtras);
        //refresh();
        pExtrasTotais += pExtras;
    } while (pExtras != 0);
    return pExtrasTotais;
}


float Pontua () {
    float pontosDaRodada = 0;
    pontosDaRodada += MarcaPontos(px, py, 1);
    if (pontosDaRodada == 0) return 0;
    pontosDaRodada += MarcaPontosExtras();
    //mvprintw(2,24, "P: %f ", pontosDaRodada);
    refresh();
    return pontosDaRodada;
}

void Testar () {
    SetGraphics();
    DesenhaArena();
    DesenhaSelection(TUDO_OK);
    refresh();
    usleep(50000);
}

int VerificaFimDeJogo () {
    int e;
    int oFimEstaProximo = true;
    for (int j = 1; j < NY_MATRIZ - 1; j++) {
        for (int i = 1; i < NX_MATRIZ - 1; i++) {
            e = matriz[i][j];
            if (true == PossibilidadeAcimaDireita(e, i, j) ||
                true == PossibilidadeAbaixoEsquerda(e, i, j)) {
                oFimEstaProximo = false;
            }
        }
    }
    return oFimEstaProximo;
}

void DesenhaMoldPause() {
	DesenhaMolduraPause();
}

void FimDeUmJogo (float p) {
	LimpaTela(1);
	OFIMESTAPROXIMO(p);
	LimpaTela(1);
	nodelay(stdscr, TRUE);
	MostraPlacar();
}
