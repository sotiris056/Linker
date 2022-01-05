CC=gcc
CFLAGS=

programme: etape_1.o arithmetic_functions.o
	$(CC) -o programme etape_1.o arithmetic_functions.o

etape_1.o: etape_1.c etape_1.h arithmetic_functions.h
	$(CC) $(CFLAGS) -c etape_1.c

arithmetic_functions.o: arithmetic_functions.c arithmetic_functions.h
	$(CC) $(CFLAGS) -c arithmetic_functions.c