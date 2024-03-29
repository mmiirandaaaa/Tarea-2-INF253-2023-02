Maximiliano Miranda 202273117-6

Al formato entregado para la elaboración de la tarea se añadieron las siguientes variables extern:

	- char** tipos : variable global que almacenará la matriz que contiene la información necesaria para conocer el tipo de dato (Tierra* o Bomba*) almacenado en tablero[i][j]
	- int tesoros : variable global que cuenta la cantidad total de tesoros generados al iniciar el tablero 

Además se añadieron las siguientes funciones:

	En Tablero.c : 
		- Tierra* crear_tierra() : Esta función fue añadida para mejorar el orden y la limpieza del código de la función IniciarTablero(). Simplemente pide memoria para una variable del tipo Tierra con las condiciones pedidas (vida aleatoria entre 1 a 3, y 5% de probabilidades de ser tesoro) y retorna el puntero a ella para que sea almacenado en una posición de la matriz tablero

	En Bomba.c :
		- void menos_uno(int fila, int columna) : Esta función fue añadida con el propósito de mejorar el orden y limpieza del código de la función ExplosiónX. Simplemente recibe una posición en la matriz tablero y reduce en 1 la vida de esa celda



Para compilar se requiere de una carpeta que contenga los siguientes archivos:
	
	- Tablero.h : header de Tablero.c
	- Tablero.c : funciones del tablero
	- Bomba.h : header de Bomba.h
	- Bomba.c : funciones para las bombas
	- Tierra.h : header que contiene la definición del struct Tierra
	- TreasureFinder.c : función main para la ejecución del programa

El programa se compila con la instrucción

	make

Esta genera los archivos necesarios para la creación del archivo ejecutable (.o , .h.gch y out) llamado out , además de dicho ejecutable.
Para eliminar estos archivos creados por make se usa la siguiente instrucción

	make clean