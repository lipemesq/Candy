
CFLAGS = -Wall -g	# Flags de Compilação

LDLIBS = -lncurses	# Bibliotecas padrão

# Arquivos objeto
objs = graphics.o candycrush.o menu.o jogo.o operations.o

candys:	$(objs)
	gcc -o candys $(objs) $(LDLIBS)

graphics.o: graphics.c gameconfig.h graphics.h
	gcc -c graphics.c $(CFLAGS)

candycrush.o: candycrush.c operations.h gameconfig.h graphics.h
	gcc -c candycrush.c $(CFLAGS)

menu.o: menu.c gameconfig.h menu.h
	gcc -c menu.c $(CFLAGS)

jogo.o: jogo.c menu.h candycrush.h
	gcc -c jogo.c $(CFLAGS)

operations.o: operations.c gameconfig.h operations.h candycrush.h
	gcc -c operations.c $(CFLAGS)

clean: 
	-rm $(objs)

purge: clean
	-rm candys

