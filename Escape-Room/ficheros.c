#include <stdio.h>
#include "ficheros.h"

//lectura y escritura de ficheros


//Cabecera: int comprobar_usuario(char *user)
//Precondicion: Cadena de caracteres inicializada
//Postcondicion: La funcion devuelve un booleano que indicará si el usuario coincide con alguno existente en el fichero "jugadores.txt"
int comprobar_usuario(char *user){

    int encontrado=0, guiones=2, i;

    FILE *fichero;

    fichero=fopen("data/jugadores.txt", "r"); //abrimos en modo lectura


    if (fichero==NULL){

        printf("\nHa habido un error en la apertura del fichero\n");
    }


    for (i=0; i<=guiones;i++){  //mi idea es contar guiones hasta el campo "jugador" que es donde esta el usuario



    }




    return encontrado;
}
