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
    char *id_objeto = aux;
    char *loc_texto;
    int localizacion;
    char **temp;

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
        return;  //he quitado el return 1 para que no termine el programa del tiron
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

                while(aux!=NULL && strcmp(aux,"FINCON")!=0 && strcmp(aux,"FINPUZ")!=0)
                {
                    loc_texto=strtok(NULL,"-\n\r");

                    if(loc_texto==NULL)
                    {
                        break;
                    }

                    if(strcmp(loc_texto,"INV")==0)
                    {
                        localizacion=-1;
                    } else
                    {
                        localizacion=atoi(loc_texto);
                    }

                    for (j = 0; j < num_objetos; j++)
                    {
                        if (strcmp(p->objeto[j].id_obj, id_objeto) == 0)
                        {
                            p->objeto[j].id_sala = localizacion;
                            break;
                        }
                    }

                    if(localizacion==-1)
                    {
                        temp=(char **)realloc(p->jugador[u].id_obj,(p->jugador[u].num_inventario + 1) * sizeof(char *));

                        if(temp==NULL)
                        {
                            printf("Error de memoria al cargar inventario,\n");
                            fclose(f);
                            system("pause");
                            return;
                        }

                        p->jugador[u].id_obj = temp;
                        p->jugador[u].id_obj[p->jugador[u].num_inventario]=(char *)malloc((strlen(id_objeto) + 1) * sizeof(char));

                        if(p->jugador[u].id_obj[p->jugador[u].num_inventario]==NULL)
                        {
                            printf("Error de memoria alc arga inventario.\n");
                            fclose(f);
                            system("cls");
                            return;
                        }

                        strcpy(p->jugador[u].id_obj[p->jugador[u].num_inventario], id_objeto);
                        p->jugador[u].num_inventario++;

                        if(strcmp(id_objeto,"OB04")==0)
                        {
                            mapa=1;
                        }
                    }

                    aux=strtok(NULL, "-\n\r");
                }
            }

            //Cargar conexiones sbiertas
            if(aux!=NULL && strcmp(aux, "FINCON")==0)
            {
                aux=strtok(NULL, "-\n\r");
                while(aux!=NULL && strcmp(aux, "FINPUZ")!=0)
                {
                    char *id_conexion = aux;
                    char *estado_conexion;

                    estado_conexion=strtok(NULL,"-\n\r");

                    if(estado_conexion==NULL)
                    {
                        break;
                    }

                    if(strcmp(estado_conexion,"Activa")==0)
                    {
                        for(j=0;j<num_conexiones;j++)
                        {
                            if(strcmp(p->conexion[j].id_conexion,id_conexion)==0)
                            {
                                strcpy(p->conexion[j].estado,"Activa");
                                strcpy(p->conexion[j].cond,"0");
                                break;
                            }
                        }
                    }
                    aux = strtok(NULL, "-\n\r");
                }
            }
            // cargar estado de puzles

            if(aux!=NULL && strcmp(aux,"FINPUZ")==0)
            {
                aux=strtok(NULL,"-\n\r");

                while(aux!=NULL)
                {
                    char *id_puzle = aux;
                    char *estado_puzle;

                    estado_puzle=strtok(NULL,"-\n\r");
                    if(estado_puzle==NULL)
                    {
                        break;
                    }
                    if(strcmp(estado_puzle,"Resuelto")==0)
                    {
                        for(j=0;j<num_conexiones;j++)
                        {
                            if(strcmp(p->conexion[j].cond,id_puzle)==0)
                            {
                                strcpy(p->conexion[j].cond,"0");
                                strcpy(p->conexion[j].estado,"Activa");
                            }
                        }
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
    printf("\n\nBienvenido a Escape Room ESI!\n\n\n");


    printf("Introduce lo que quieras hacer\n\n");

    printf("1. Nueva Partida\n");
    printf("2. Cargar Partida\n");
    printf("3. Salir\n\n");

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
