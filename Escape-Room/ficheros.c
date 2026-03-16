#include <stdio.h>
#include "ficheros.h"

//lectura y escritura de ficheros

//Cabecera: void carga(jugadores lista[20], int *total_leidos);
//precondicion:
//poscondicion:cargar en la estructura la informacion de todos los usuarios guardados en el
//fichero jugadores.txt
void carga(jugadores lista[20],int *total_leidos){
    FILE *f;
    f=fopen("data/jugadores.txt","r");
    if (f==NULL){

        printf("\nHa habido un error en la apertura del fichero\n");
    }

     char linea[200];
     char *aux;
     int i=0;


     while(fgets(linea,200,f)!=NULL && i<20){
        //ID(lo convierto en entero)
        aux=strtok(linea,"-");
        if(aux) lista[i].id_jugador=atoi(aux);
        //NOMBRE (solo lo copio)
        aux=strtok(NULL,"-");
        if(aux) strcpy(lista[i].nomb_jugador,aux);
        //JUGADOR
        aux=strtok(NULL,"-");
        if(aux) strcpy(lista[i].jugador,aux);
        //CONTRASEÑA
        aux=strtok(NULL,"-");
        if(aux) strcpy(lista[i].contrasena,aux);
        //ID OBJETO
        int j=0;
        while((aux=strtok(NULL,"-\n"))!=NULL && j<5){
            strncpy(lista[i].id_obj[j],aux);
            j++;
        }

        i++;
    }
    *total_leidos=i;
    fclose(f);
    }

//Cabecera: int comprobar_usuario(char *user)
//Precondicion: Cadena de caracteres inicializada
//Postcondicion: La funcion devuelve un booleano que indicará si el usuario coincide con alguno existente en el fichero "jugadores.txt"
int comprobar_usuario(jugadores lista[20],char user[11], int total_leidos, int *u){ //la u es para luego ubicar en que posicion del array esta el usuario y no tener que buscarlo otra vez okkk
    int i, encontrado;
    for(i=0;i<total_leidos-1;i++){
        if(strcmp(user,lista[i].jugador)) {
            *u=i;
            encontrado=1;}
    }

    return encontrado;
}

//cabecera: int comprobar_clave(jugadores lista[20], char clave, int u);
//precondicion: se debe haber comprobado el usuario antes
//poscondicion: la funcion devuelve un booleano que indicara si la clave es la del usuario
int comprobar_clave(jugadores lista[20], char clave, int u){
    int comprobado;
    if(strcmp(clave,lista[u].contrasena)) comprobado=1;

    return comprobado;
}
