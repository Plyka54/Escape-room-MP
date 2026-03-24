#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "ficheros.h"
#include "juego.h"

//Todas las opciones para guardar la partida, crear, cargar...

void Nueva_partida();
void Cargar_partida(partida *p);


void Cargar_partida(partida *p)
{
    /* cargar la situacion de partida.txt */


}

void Bienvenida(){

    int opcion=0;

    system("clear");
    printf("\n\n\n ¡Bienvenido a Escape Room ESI!\n\n\n");


    printf("Introduce lo que quieras hacer\n");

    printf("1. Nueva Partida\n");
    printf("2. Cargar Partida\n");
    printf("3. Salir\n");

    scanf("%d", &opcion);

    switch(opcion){

        case 1:

            Nueva_partida();

            break;

        case 2: //Cargar partida

            //Cargar_partida();

            break;

        case 3: //Salir


            break;

        default:

            printf("Opcion no valida");

            break;

        }







}


