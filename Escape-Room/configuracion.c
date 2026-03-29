#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "ficheros.h"
#include "juego.h"

//Todas las opciones para guardar la partida, crear, cargar...

void Nueva_partida(partida *p,int u);
void Cargar_partida(partida *p);


void Cargar_partida(partida *p)
{
    /* cargar la situacion de partida.txt */


}

void Bienvenida(partida *p,int u){

    int opcion=0;

    system("cls");
    printf("\n\n\n Bienvenido a Escape Room ESI!\n\n\n");


    printf("Introduce lo que quieras hacer\n\n");

    printf("1. Nueva Partida\n");
    printf("2. Cargar Partida\n");
    printf("3. Salir\n\n");

    scanf("%d", &opcion);

    switch(opcion){

        case 1:

            Nueva_partida(p,u);

            break;

        case 2: //Cargar partida

            //Cargar_partida();

            break;

        case 3: //Salir

            exit(0);
            break;

        default:

            printf("Opcion no valida");

            break;

        }

}

void Nueva_partida(partida *p,int u){


    Inicio_escape_room(p,u);



}


