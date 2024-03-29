#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

int main()
{
    srand(time(NULL));
    int opcion,turno = 1;
    printf("-------- BIENVENIDO A TREASUREFINDER --------\n\n");
    printf("Ingrese tamaño del tablero\n");
    printf("Opciones: 1.-7x7    2.-10x10    3.-12x12\n");
    printf("Su opción: ");scanf("%d",&opcion);printf("\n");
    
    do{

        switch(opcion){
            case 1: IniciarTablero(7);break;
            case 2: IniciarTablero(10);break;
            case 3: IniciarTablero(12);
        }
        if(tesoros == 0)BorrarTablero();

    }while(tesoros == 0);

    while(tesoros){
        printf("Tablero (turno %d)\n\n",turno++);
        MostrarTablero();if(tesoros == 0)break;
        printf("Escoja alguna de las siguientes opciones: 1.-Colocar Bomba    2.-Mostrar Bombas    3.-Ver Tesoros    4.-Salir\n");
        printf("Su opción: ");scanf("%d", &opcion);printf("\n");

        while(opcion!=4 && opcion!=1){
            if(opcion == 2){
                MostrarBombas();
                printf("Escoja alguna de las siguientes opciones: 1.-Colocar Bomba    2.-Mostrar Bombas    3.-Ver Tesoros    4.-Salir\n");
                printf("Su opción: ");scanf("%d", &opcion);printf("\n");
            }
            else if(opcion == 3){
                VerTesoros();
                printf("Escoja alguna de las siguientes opciones: 1.-Colocar Bomba    2.-Mostrar Bombas    3.-Ver Tesoros    4.-Salir\n");
                printf("Su opción: ");scanf("%d", &opcion);printf("\n");
            }
        }

        if(opcion == 4){printf("-------- JUEGO FINALIZADO --------\n");BorrarTablero();return 0;}

        //OPCION 2
        int fila,columna;
        printf("Indique dónde desea colocar la bomba(coordenadas)\n");
        printf("Fila: ");scanf("%d",&fila);printf("Columna: ");scanf("%d",&columna);
        printf("Indique forma en que desea que explote la bomba\n");
        printf("Opciones: 1.-Punto    2.-X\n");
        printf("Su opción: ");scanf("%d",&opcion);printf("\n");

        Bomba* bomba = malloc(sizeof(Bomba));
        switch(opcion){
            case 1: bomba->explotar = ExplosionPunto;
                    bomba->contador_turnos = 1;
                    break;
            case 2: bomba->explotar = ExplosionX;
                    bomba->contador_turnos = 3;
        }
        ColocarBomba(bomba, fila-1, columna-1);

        PasarTurno();

    }

    printf("\n-------- GANASTE!!! --------\n");
    printf("\n-------- JUEGO FINALIZADO --------\n");

    BorrarTablero();
    return 0;
}