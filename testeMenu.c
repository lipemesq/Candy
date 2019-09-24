#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include "menu.h"

void StartCurses() {
    initscr();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
}

int main () {
    StartCurses();

    OPTION opt[4];
    IniciaOpt(opt, 4);

    opt[0].frase = "Option 01";
    opt[1].frase = "Option 02";
    opt[2].frase = "Option 03";
    opt[3].frase = "Option 04";

    int s = AbreMenu(opt, 4);
    endwin();
    printf("%i\n", s);

    return 0;
}
