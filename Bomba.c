#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tierra.h"
#include "Bomba.h"

/*
menos_uno(int fila, int columna)

Recibe una fila y columna perteneciente a la matriz tablero,
en caso de que alguno de los dos números se salga del rango del tablero
le aplica módulo. Luego reduce en 1 la vida de la casilla fila,columna

*/

void menos_uno(int fila, int columna){
    
    if(fila < 0)fila = dimension + fila;
    if(columna < 0)columna = dimension + columna;

    int i = fila % dimension;
    int j = columna % dimension;

    if(tipo[i][j] == 'T'){
        Tierra* t = (Tierra*)tablero[i][j];
        t->vida--;
        if(t->vida < 0) t->vida=0;
    }
    else{
        Bomba* b = (Bomba*)tablero[i][j];
        b->tierra_debajo->vida--;
        if(b->tierra_debajo->vida < 0)b->tierra_debajo->vida = 0;
    }
}


/*
TryExplotar(int fila, int columna)

Recibe la fila y la columna en la cual se ubica la bomba que se intentará explotar
disminuye el contador de turnos y si este llega a 0 llama a la función explotar de la bomba

*/

void TryExplotar(int fila, int columna){
    
    Bomba* b = (Bomba*)tablero[fila][columna];
    b->contador_turnos--;
    if(b->contador_turnos <= 0){
        b->explotar(fila,columna);
    }

    return;
}

/*
BorrarBomba(int fila, int columna)

Recibe la fila y la columna en la que se ubica la bomba que se desea borrar del tablero
Libera la memoria reservada para la bomba, pero antes devuelve la tierra al tablero

*/

void BorrarBomba(int fila, int columna){
    
    Bomba* b = (Bomba*)tablero[fila][columna];
    tablero[fila][columna] = b->tierra_debajo;
    tipo[fila][columna] = 'T';
    free(b);

    return;
}

/*
ExplosionPunto(int fila, int columna)

Recibe la fila y la columna de la bomba a explotar. Le baja la vida
a 0 a tierra_debajo y luego llama a la funcion BorrarBomba

*/

void ExplosionPunto(int fila, int columna){
    
    Bomba* b = (Bomba*)tablero[fila][columna];
    b->tierra_debajo->vida = 0;
    BorrarBomba(fila, columna);

    return;
}

/*
ExplosionX(int fila, int columna)

Recibe la fila y la columna de la bomba a explotar
Reduce en 1 la vida de las celdas que se encuentran
en las esquinas que tocan a la celda que contiene la bomba
y también reduce la vida de la celda en la cual se ubica la bomba

*/

void ExplosionX(int fila, int columna){

    menos_uno(fila,columna);
    menos_uno(fila+1,columna+1);
    menos_uno(fila+1,columna-1);
    menos_uno(fila-1,columna-1);
    menos_uno(fila-1,columna+1);    

    BorrarBomba(fila,columna);

    return;
}