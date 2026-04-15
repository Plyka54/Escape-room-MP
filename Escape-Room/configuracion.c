#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "configuracion.h"
#include "ficheros.h"
#include "juego.h"

//Todas las opciones para guardar la partida, crear, cargar...



void Cargar_partida(partida *p, int u)  //  Comprobado
{
    FILE *f;
    char linea[200];
    char *aux;
    int total_usuarios;
    int id_guardado;
    int ubicacion_actual=0;
    int encontrada=0;
    int i, j;
    int mapa=0;

    system("cls");
    printf("\nCargando partida...\n");

    for(i=0; i<p->jugador[u].num_inventario; i++)
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
        return 1;
    }

    while(fgets(linea, sizeof(linea), f) != NULL && encontrada ==0)
    {
        aux=strtok(linea, "-\n\r");

        if(aux != NULL)
        {
            id_guardado=atoi(aux);

            if(id_guardado == p->jugador[u].id_jugador)
            {
                encontrada=1;
                aux=strtok(NULL, "-\n\r");

                if(aux!=NULL)
                {
                    ubicacion_actual=atoi(aux)-1;
                    p->jugador[u].ubicacion_actual=ubicacion_actual;
                }

                aux=strtok(NULL,"-\n\r");

                while(aux!=NULL)
                {
                    char **temp;
                    temp=(char **)realloc(p->jugador[u].id_obj,(p->jugador[u].num_inventario + 1) * sizeof(char *));

                    if(temp==NULL)
                    {
                        printf("Error de memoria al cargar inventario.\n");
                        fclose(f);
                        system("pause");
                        return ;
                    }

                    p->jugador[u].id_obj = temp;
                    p->jugador[u].id_obj[p->jugador[u].num_inventario]=(char *)malloc((strlen(aux) + 1) * sizeof(char));

                    if(p->jugador[u].id_obj[p->jugador[u].num_inventario]==NULL)
                    {
                        printf("Error de memoria al cargar inventario.\n");
                        fclose(f);
                        system("pause");
                        return ;
                    }

                    strcpy(p->jugador[u].id_obj[p->jugador[u].num_inventario], aux);
                    p->jugador[u].num_inventario++;

                    for (j = 0; j < num_objetos; j++)
                    {
                        if (strcmp(p->objeto[j].id_obj, aux) == 0)
                        {
                            p->objeto[j].id_sala = -1;
                            break;
                        }
                    }
                    if (strcmp(aux, p->objeto[3].id_obj) == 0) {
                        mapa = 1;
                    }
                     aux = strtok(NULL, "-\n\r");
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
        printf("%d\n",ubicacion_actual);
        menu_opciones_juego(p, u, mapa);
    }
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

            Cargar_partida(p,u);


            break;

        case 3: //Salir

            exit(0);
            break;

        default:

            printf("Opcion no valida");

            break;

        }

}

void Nueva_partida(partida *p,int u)
{
    int total_usuarios;
    int i;

    system("cls");
    printf("\nCreando una Nueva partida...\n");
    carga(p, &total_usuarios);
    printf("Datas cargados correctamente.\n");


    for(i=0; i<p->jugador[u].num_inventario;i++)
    {
        free(p->jugador[u].id_obj[i]);
    }

    free(p->jugador[u].id_obj);
    p->jugador[u].id_obj=NULL;
    p->jugador[u].num_inventario=0;     // 0 objetos

    printf("Inventario vaciado.\n");

    system("pause");

    //Los printf son para ir indicando que las cosas funcionan

    Inicio_escape_room(p,u);
}
