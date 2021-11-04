CC=gcc
CFLAGS= -Wall -finput-charset="UTF-8" -fexec-charset="UTF-8"
EXEC=main

all: $(EXEC)

main:	main.c Passagers.c Train.c
	$(CC) $(CFLAGS) -o $(EXEC) main.c Passagers.c Train.c

clean:
	rm $(EXEC)

execute:
	setterm -cursor off
	./$(EXEC)
	setterm -cursor on
