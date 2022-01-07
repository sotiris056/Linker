CC=gcc -g
CFLAGS= -Wall

programme: etape_1.o arithmetic_functions.o util.o
	$(CC) -o programme etape_1.o arithmetic_functions.o util.o -lm

#programme2: etape_1v2.o arithmetic_functions.o util.o
#	$(CC) -o programme2 etape_1v2.o arithmetic_functions.o util.o -lm

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c -lm

#etape_1v2.o: etape_1v2.c etape_1v2.h arithmetic_functions.h util.h
#	$(CC) $(CFLAGS) -c etape_1v2.c -lm

etape_1.o: etape_1.c etape_1.h arithmetic_functions.h util.h
	$(CC) $(CFLAGS) -c etape_1.c -lm

arithmetic_functions.o: arithmetic_functions.c arithmetic_functions.h 
	$(CC) $(CFLAGS) -c arithmetic_functions.c -lm

clean: programme
	rm -f *.o 
