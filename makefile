GC = gcc -Wall

out: Tablero.o Bomba.o
	$(GC) -o out TreasureFinder.c Tierra.h Tablero.o Bomba.o

Tablero.o:
	$(GC) -c Tablero.c Tablero.h Tierra.h

Bomba.o:
	$(GC) -c Bomba.c Bomba.h Tierra.h

.PHONY: clean
clean:
	rm -rf *.o out *.h.gch