#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tablero.h"


void*** tablero;
int dimension;
char** tipo;
int tesoros;

/*
Tierra* crear_tierra()

Función auxiliar que pide memoria para almacenar un struct Tierra
y retorna el puntero al struct creado

*/

Tierra* crear_tierra(){
    Tierra* t = malloc(sizeof(Tierra));
    t->vida = rand()%3 + 1;
    int treasure = rand()%100 + 1;
    if(treasure <= 5){
        ++tesoros;
        t->es_tesoro = 1;
    }
    else t->es_tesoro = 0;
    return t;
}

/*
IniciarTablero(int n)

Crea una matriz de punteros void que inicialmente apuntan a Tierra
De manera paralela crea otra matriz para almacenar el tipo de dato
al que apunta el tablero en la posicion i,j

*/
void IniciarTablero(int n){
    tesoros = 0;
    dimension = n;
    tipo = malloc(sizeof(char*)*n);
    tablero = malloc(sizeof(void**)*n);
    for(int i=0; i<n; i++){
        tipo[i] = malloc(sizeof(char)*n);
        tablero[i] = malloc(sizeof(void*)*n);
        for(int j=0; j<n; j++){
            tipo[i][j] = 'T';
            tablero[i][j] = crear_tierra();
        }
    }
    return;
}

/*
PasarTurno

Recorre la matriz del tablero intentando explotar las bombas que esten presentes en el tablero

*/

void PasarTurno(){

    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            if(tipo[i][j] != 'T'){
                TryExplotar(i,j);
            }
        }
    }

    return;  
}

/*
ColocarBomba(Bomba* b, int fila, int columna)

Recibe un puntero a una bomba y la coloca en la posicion fila,columna
en el tablero cambiando también la matriz tipo en fila,columna a un caracter
que representa la funcion explotar de la bomba

*/

void ColocarBomba(Bomba* b, int fila, int columna){

    b->tierra_debajo = (Tierra*)tablero[fila][columna];
    tablero[fila][columna] = b;
    if(b->explotar == ExplosionPunto)tipo[fila][columna] = 'P';
    else tipo[fila][columna] = 'X';

    return;
}

/*
MostrarTablero()

Imprime por pantalla el tablero, mostrando los tesoros descubiertos con el caracter *,
las bombas con o y las tierras con un entero correspondiente a la vida de la tierra.
Además cuenta los tesoros revelados en el tablero, si esta cantidad es igual a la cantidad
de tesoros presentes en el tablero, establece la cantidad de tesoros en 0 para que termine
el programa principal

*/

void MostrarTablero(){
    int encontrados=0;
    printf("     ");
    for(int indices = 0; indices<dimension; indices++){
        if(indices < 9)printf("   %d",indices+1);
        else printf("  %d",indices+1);
    }
    printf("\n\n");
    for(int i=0; i<dimension; i++){
        if(i < 9)printf("  %d   |",i+1);
        else printf("  %d  |",i+1);
        for(int j=0; j<dimension; j++){
            if(tipo[i][j] == 'T'){
                Tierra* t = (Tierra*)tablero[i][j];
                if(t->vida <= 0 && t->es_tesoro){printf(" * |"); ++encontrados;}
                else printf(" %d |",t->vida);
            }
            else printf(" o |");
        }
        printf("\n");
    }

    if(encontrados == tesoros)tesoros = 0;

    printf("\n");
    return;
}

/*
MostrarBombas

Muestra las bombas activas presentes en el tablero

*/

void MostrarBombas(){
    int cont = 0;

    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            if(tipo[i][j] != 'T'){
                
                char nombre_funcion_explotar[20];
                if(tipo[i][j] == 'P')strcpy(nombre_funcion_explotar, "ExplosionPunto");
                else if(tipo[i][j] == 'X')strcpy(nombre_funcion_explotar, "ExplosionX");

                Bomba* b = (Bomba*)tablero[i][j];
                printf("Turnos que le faltan para explotar: %d\n",b->contador_turnos);
                printf("Coordenadas: (%d,%d)\n",i+1,j+1);
                printf("Forma de explosión: %s\n",nombre_funcion_explotar);
                printf("Vida de tierra debajo: %d\n\n",b->tierra_debajo->vida);

                cont++;
            }
        }
    }
    if(!cont)printf("No hay ninguna bomba colocada\n\n");

    return;
}

/*
VerTesoros

Imprime el tablero por la pantalla, pero revelando todos los tesoros presentes en este

*/

void VerTesoros(){

    printf("     ");
    for(int indices = 0; indices<dimension; indices++){
        if(indices < 9)printf("   %d",indices+1);
        else printf("  %d",indices+1);
    }
    printf("\n\n");
    for(int i=0; i<dimension; i++){
        if(i<9)printf("  %d   |",i+1);
        else printf("  %d  |",i+1);
        for(int j=0; j<dimension; j++){
            if(tipo[i][j] == 'T'){
                Tierra* t = (Tierra*)tablero[i][j];
                if(t->es_tesoro)printf(" * |");
                else printf(" %d |",t->vida);
            }
            else{
                Bomba* b = (Bomba*)tablero[i][j];
                if(b->tierra_debajo->es_tesoro) printf(" * |");
                else printf(" o |");
            }
        }
        printf("\n");
    }
    printf("\nHay %d tesoros\n\n",tesoros);
    return;
}

/*
BorrarTablero

Libera toda la memoria reservada para el tablero

*/

void BorrarTablero(){
    for(int i=0; i<dimension; i++){
        for(int j=0; j<dimension; j++){
            if(tipo[i][j]!='T'){
                Bomba* b = (Bomba*)tablero[i][j];
                free(b->tierra_debajo);
            }
            free(tablero[i][j]);
        }
        free(tablero[i]);
        free(tipo[i]);
    }
    free(tablero);
    free(tipo);
    return;
}