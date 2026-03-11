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






    return encontrado;
}

void carga(jugadores j){
    FILE *f;
    f=fopen("data/jugadores.txt","r");
    if (fichero==NULL){

        printf("\nHa habido un error en la apertura del fichero\n");
    }

     jugador j;
     char linea[200];
     int i;

     while(fgets(linea,200,f)!=NULL){

     j.id_jugador=strtok(linea,"-");
     j.nomb_jugador=strtok(NULL,"-");
     j.jugador=strtok(NULL,"-");
     j.contraseña=strtok(NULL,"-");
     j.id_obj=strtok(NULL,"\n");
     i++;
    }
    }
