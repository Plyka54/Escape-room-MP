#include <stdio.h>
#include <string.h>
#include "ficheros.h"
#include "configuracion.h"

//lectura y escritura de ficheros

//Cabecera: void carga(jugadores lista[20], int *total_leidos);
//precondicion:
//poscondicion:cargar en la estructura la informacion de todos los usuarios guardados en el
//fichero jugadores.txt
void carga(partida *p,int *total_leidos){
    FILE *f;
    f=fopen("data/jugadores.txt","r");
    if (f==NULL){

        printf("\nHa habido un error en la apertura del fichero\n");
    }

     char linea[200];
     char *aux;
     int i=0;


     while(fgets(linea,200,f)!=NULL && i<20){ //memoria dinamica: realloc de lo que habia +1
        //ID(lo convierto en entero)
        aux=strtok(linea,"-");
        if(aux) p->jugador[i].id_jugador=atoi(aux);
        //NOMBRE (solo lo copio)
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->jugador[i].nomb_jugador,aux);
        //JUGADOR
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->jugador[i].jugador,aux);
        //CONTRASEÑA
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->jugador[i].contrasena,aux);
        //ID OBJETO
        p->jugador[i].num_inventario=0;
        p->jugador[i].id_obj=NULL;

        aux= strtok(NULL, "-\n\r");
        while(aux!=NULL){
            p->jugador[i].num_inventario++;
            int num_actual=p->jugador[i].num_inventario;

            p->jugador[i].id_obj= (char **)realloc(p->jugador[i].id_obj,num_actual*sizeof(char *));
            if(p->jugador[i].id_obj==NULL){
                printf("Error de memoria asignando objeto.\n");
            }

            p->jugador[i].id_obj[num_actual-1]=(char *)malloc((strlen(aux)+1)*sizeof(char));
            strcpy(p->jugador[i].id_obj[num_actual-1],aux);
            aux=strtok(NULL,"-\n\r");
        }
        i++;
        }

    *total_leidos=i;
    fclose(f);

    f=fopen("data/salas.txt","r");
    if(f==NULL){
        printf("\n Ha habido un error en la apertura del fichero\n");
    }
    i=0;
    while(fgets(linea,200,f)!=NULL && i<20){
        aux=strtok(linea,"-");
        if(aux) p->sala[i].id_sala=atoi(aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->sala[i].nombre_sala,aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->sala[i].tipo,aux);
        aux=strtok(NULL,"\n");
        if(aux) strcpy(p->sala[i].descripcion,aux);
        i++;
    }
    fclose(f);

   f=fopen("data/conexiones.txt","r");
    if(f==NULL){
        printf("\n Ha habido un error en la apertura del fichero\n");
    }
    i=0;
    while(fgets(linea,200,f)!=NULL && i<20){
        aux=strtok(linea,"-");
        if(aux) strcpy(p->conexion[i].id_conexion,aux);
        aux=strtok(NULL,"-");
        if(aux) p->conexion[i].id_origen=atoi(aux);
        aux=strtok(NULL,"-");
        if(aux) p->conexion[i].id_destino=atoi(aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->conexion[i].estado,aux);
        aux=strtok(NULL,"\n");
        if(aux) strcpy(p->conexion[i].cond,aux);
        i++;
    }
    fclose(f);

    f=fopen("data/objetos.txt","r");
    if(f==NULL){
        printf("\n Ha habido un error en la apertura del fichero\n");
    }
    i=0;
    while(fgets(linea,200,f)!=NULL && i<13){
        aux=strtok(linea,"-");
        if(aux) strcpy(p->objeto[i].id_obj,aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->objeto[i].nomb_obj,aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->objeto[i].descrip,aux);
        aux=strtok(NULL,"\n\r");
        if(aux) p->objeto[i].id_sala=atoi(aux);
        i++;
    }
    fclose(f);

    f=fopen("data/puzles.txt","r");
    if(f==NULL){
        printf("\n Ha habido un error en la apertura del fichero\n");
    }
    i=0;

    while(fgets(linea,200,f)!=NULL && i<13){
        aux=strtok(linea,"-");
        if(aux) strcpy(p->puzle[i].id_puzles,aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->puzle[i].nomb_puz,aux);
        aux=strtok(NULL,"-");
        if(aux) p->puzle[i].id_sala=atoi(aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->puzle[i].tipo,aux);
        aux=strtok(NULL,"-");
        if(aux) strcpy(p->puzle[i].descrip,aux);
        aux=strtok(NULL,"\n");
        if(aux) strcpy(p->puzle[i].sol,aux);
        i++;
    }
    fclose(f);

    }

//Cabecera: int comprobar_usuario(char *user)
//Precondicion: Cadena de caracteres inicializada
//Postcondicion: La funcion devuelve un booleano que indicará si el usuario coincide con alguno existente en el fichero "jugadores.txt"
int comprobar_usuario(partida p,char user[11], int total_leidos, int *u){ //la u es para luego ubicar en que posicion del array esta el usuario y no tener que buscarlo otra vez okkk
    int i, encontrado=0;
    for(i=0;i<total_leidos-1;i++){    // al final no hice nada tranquila
        if(strcmp(user,p.jugador[i].jugador)==0) {
            *u=i;
            encontrado=1;}
    }

    return encontrado;
}

//cabecera: int comprobar_clave(jugadores lista[20], char clave, int u);
//precondicion: se debe haber comprobado el usuario antes
//poscondicion: la funcion devuelve un booleano que indicara si la clave es la del usuario
int comprobar_clave(partida p, char clave[8], int u){
    int comprobado=0;
    if(strcmp(clave,p.jugador[u].contrasena)==0) comprobado=1;

    return comprobado;
}
