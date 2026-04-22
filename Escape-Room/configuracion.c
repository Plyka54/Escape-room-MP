#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "configuracion.h"
#include "ficheros.h"
#include "juego.h"

//Cabecera: void Cargar_partida(partida *p, int u)
//Precondicion: Estructura partida inicializada y usuario logueado correctamente en la posicion 'u'.
//Postcondicion: Lee el fichero de guardado para restaurar el inventario, ubicacion y estado de las conexiones. Da paso al juego o vuelve al menu si no hay partida.
void Cargar_partida(partida *p, int u)  //  Comprobado
{
    FILE *f;
    char linea[700];
    char *aux;
    int total_usuarios;
    int id_guardado;
    int ubicacion_actual=0;
    int encontrada=0;
    int i, j;
    int mapa=0;

    system("cls");
    printf("\nCargando partida...\n");

    for(i=0; i<p->jugador[u].num_inventario; i++)   // vaciar inventario
    {
        free(p->jugador[u].id_obj[i]);
    }

    free(p->jugador[u].id_obj);
    p->jugador[u].id_obj=NULL;
    p->jugador[u].num_inventario=0;

    carga(p, &total_usuarios);

    f=fopen("data/partida.txt","r");

    if(f==NULL)
    {
        printf("No existe  ninguna partida guardada.\n");
        system("pause");
        Bienvenida(p,u);   // si no hay partida guardada vuelve a bienvenida
        return;
    }

    while(fgets(linea, sizeof(linea), f) != NULL && encontrada ==0)
    {
         aux = strtok(linea, "-\n\r");

         if(aux!=NULL)
         {
             id_guardado=atoi(aux);

             if(id_guardado==p->jugador[u].id_jugador)
             {
                 encontrada=1;

                 aux=strtok(NULL, "-\n\r");
                 if(aux!=NULL)
                 {
                     ubicacion_actual=atoi(aux)-1;
                     p->jugador[u].ubicacion_actual=ubicacion_actual;
                 }

                 for(i=0;i<num_objetos;i++)  //objetos
                 {
                     char *id_obj = strtok(NULL, "-\n\r");
                     char *loc_str = strtok(NULL, "-\n\r");

                     if(id_obj!=NULL && loc_str!=NULL)
                     {
                         int loc=atoi(loc_str);

                         for(j = 0; j < num_objetos; j++)
                         {
                             if(strcmp(p->objeto[j].id_obj, id_obj) == 0)
                             {
                                 p->objeto[j].id_sala = loc;

                                 if(loc == -1)    // Si la localizacion es -1, lo metemos en el inventario
                                 {
                                     p->jugador[u].id_obj = (char **)realloc(p->jugador[u].id_obj, (p->jugador[u].num_inventario + 1) * sizeof(char *));
                                     p->jugador[u].id_obj[p->jugador[u].num_inventario] = strdup(id_obj);
                                     p->jugador[u].num_inventario++;

                                     if(strcmp(id_obj, "OB04") == 0) mapa = 1;
                                 }
                                 break;
                             }
                         }
                     }
                 }
                 for(i = 0; i < num_conexiones; i++)  //conexiones y puzles
                 {
                     char *id_con = strtok(NULL, "-\n\r");
                     char *cond_str = strtok(NULL, "-\n\r");

                     if(id_con != NULL && cond_str != NULL)
                     {
                         for(j = 0; j < num_conexiones; j++)
                         {
                             if(strcmp(p->conexion[j].id_conexion, id_con) == 0)
                             {
                                 strcpy(p->conexion[j].cond, cond_str);

                                 if(strncmp(cond_str, "0", 1) == 0)
                                 {
                                     strcpy(p->conexion[j].estado, "Activa");
                                 } else
                                 {
                                     strcpy(p->conexion[j].estado, "Bloqueada");
                                 }
                                 break;
                             }
                         }
                     }
                 }
             }
         }
    }

    fclose(f);

    if(encontrada==0)
    {
        printf("No hay ninguna partida guardada para este jugador.\n");
        system("pause");
        Bienvenida(p,u);
        return;
    } else
    {
        printf("Partida cargada con exito.\n");
        menu_opciones_juego(p, u, mapa);
    }
}

//Cabecera: void Bienvenida(partida *p, int u)
//Precondicion: El jugador debe haberse logueado o registrado correctamente.
//Postcondicion: Muestra el menu principal y redirige al usuario a una partida nueva, a cargar una partida existente o a salir del juego.
void Bienvenida(partida *p,int u){

    int opcion=0;

    system("cls");
    printf("\n\nBienvenido a Escape Room ESI!\n\n\n");
    printf("Introduce lo que quieras hacer\n\n");
    printf("1. Nueva Partida\n2. Cargar Partida\n3. Salir\n\n");
    scanf("%d", &opcion);

    switch(opcion){
        case 1:
            Nueva_partida(p,u);
            break;

        case 2:
            Cargar_partida(p,u);
            break;

        case 3:
            exit(0);
            break;

        default:
            printf("Opcion no valida");
            break;
        }
}

//Cabecera: void Nueva_partida(partida *p, int u)
//Precondicion: Estructura partida inicializada y disponible en memoria.
//Postcondicion: Reinicia el estado del mundo leyendo los datos base de los ficheros, vacia el inventario del jugador y da comienzo al juego.
void Nueva_partida(partida *p,int u)
{
    int total_usuarios;
    int i;

    system("cls");
    printf("\nCreando una Nueva partida...\n");
    carga(p, &total_usuarios);
    printf("Datos cargados correctamente.\n");


    for(i=0; i<p->jugador[u].num_inventario;i++)
    {
        free(p->jugador[u].id_obj[i]);
    }

    free(p->jugador[u].id_obj);
    p->jugador[u].id_obj=NULL;
    p->jugador[u].num_inventario=0;     // 0 objetos

    printf("Inventario vaciado.\n\n");

    system("pause");

    //Los printf son para ir indicando que las cosas funcionan

    Inicio_escape_room(p,u);
}
