#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "menu.h"
#include "candycrush.h"

enum optMenuInicial {
    IniciarJogo, Configs, Ajuda, Sair
} optMenuInicial;

enum optMenuPause {
    Continuar, Deixar, SalvarSair, irParaMenu
} optMenuPause;


int main () {

    // Inicia a ncurses
    StartCurses();

    // pontos
    float auxP, pontinhos = 0;

    // Cria as opções do menu inicial
    int nopt = 4;
    OPTION opt[nopt];
    IniciaOpt(opt, nopt);

    for (int i = 0; i < nopt; i++) {
        opt[i].x = 11;
        opt[i].y = 8 + 2*i;
    }

    // Escolhe as frases de cada opção
    opt[0].frase = "Novo Jogo";
    opt[1].frase = "Continuar Jogo";
    opt[2].frase = "Ajuda";
    opt[3].frase = "Sair";
	LimpaTela(1);
    // Enquanto estiver no menu, verifique por essas opções:
    int optEscolhida = -1;
    while (optEscolhida != Sair) {
        optEscolhida = AbreMenu(opt, nopt);
        if (optEscolhida == Configs) {
            pontinhos = LoadJogo();
            break;
        }
        else if (optEscolhida == Ajuda) {
            MostrarAjuda();
        }
        else if (optEscolhida == Sair) {
            FecharJogo();
        }
        else if (optEscolhida == IniciarJogo) {
   			CriaMatriz();
 			//Pontua();
            break;
        }
    }

    // Inicia o jogo

    SetGraphics();
    SetBackup();
	LimpaTela(2);
    //EncontraSequencia();
	//MostraMatriz();

    // Cria as opções do menu de pause
    int noptpause = 4;
    OPTION optpause[noptpause];
    IniciaOpt(optpause, noptpause);

    for (int i = 0; i < noptpause; i++) {
        optpause[i].x = 10;
        optpause[i].y = 8 + 2*i;
    }

    // Escolhe as frases de cada opção
    optpause[0].frase = "Continuar";
    optpause[1].frase = "Deixar a partida";
    optpause[2].frase = "Salvar e sair";
    optpause[3].frase = "Highscores";

    // Condições para fim de jogo
    float tempoSegs = TEMPO_PARTIDA, auxTempo, auxPause = 0;    short venceu = 0;

    // Status do jogador
    int stats = Selecionando;    int ch = 0;     int optEscolhidaPause = -1;

	// Setando o tempo
	IniciaTempo();

	// Carregando o placar
	CarregaPlacar();

    // Loop do jogo
    while (tempoSegs > 0 && !venceu) {
		// Primeiro de tudo ajusta os tempos

        // Desenha a fase, chama os componentes gráficos
        SetGraphics();
        DesenhaArena();
		DesenhaEsteiras();
		DesenhaLinhaSelecionada(stats);
		DesenhaColunaSelecionada(stats);
      	DesenhaSelection(stats);
        DesenhaPontos(pontinhos);
		//MostraPlacar();
		auxTempo = TEMPO_PARTIDA - ((float)AtualizaTempo(tempoSegs));
		tempoSegs -= (tempoSegs-auxTempo-auxPause);
        refresh();

        // Pega a tecla
        ch = getch();
        // Se estiver selecionando a linha/coluna
        if (stats == Selecionando) {
            // Move a seleção, escolhe no ponto que vai ser o eixo
            MoveSelection(ch);
        }
        else if (stats == Movendo) {
            // Move a linha ou a coluna do eixo
            MoveLineCol(ch);
        }

        // Abre menu de pause
        if (ch == 'q') {
			time_t tempoPausado = time(NULL), tDepois;
			DesenhaMoldPause();
			while ((optEscolhidaPause = AbreMenu(optpause, noptpause)) != Continuar) {

		        if (optEscolhidaPause == Continuar) {
		            // Do nothing?
		        }
		        else if (optEscolhidaPause == Deixar) {
		            FecharJogo();
		        }
		        else if (optEscolhidaPause == SalvarSair) {
		            // Salvar e sair
		            SalvarJogo(pontinhos);
					FecharJogo();
		        }
		        else if (optEscolhidaPause == irParaMenu) {
					MostraPlacar();
		        }
				DesenhaMoldPause();
			}
			tDepois = time(NULL);
			auxPause += (float)difftime(tDepois, tempoPausado);
        }

        else if (ch == '\n') {
            if (stats == Selecionando) {
                stats = Movendo;
            }
            else if (stats == Movendo) {
                auxP = Pontua() / 10; 
                if (auxP == 0) {
                    LoadBackup();
                }
                else {
                    SetBackup();
                }
                pontinhos += auxP;
                stats = Selecionando;
            }
        }
		else if (ch == 'h') {
			time_t tempoPausado = time(NULL), tDepois;
			MostrarAjuda();
			LimpaTela(2);
			tDepois = time(NULL);
			auxPause += (float)difftime(tDepois, tempoPausado);
		}
    }
	FimDeUmJogo(pontinhos);
	SetPlacar(pontinhos);
	FecharJogo();
}
