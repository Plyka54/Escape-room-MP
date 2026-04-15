#ifndef CONFIGURACION
#define CONFIGURACION
#include <stdio.h>


typedef struct
{
    int id_jugador;
    char nomb_jugador[21];
    char jugador[11];
    char contrasena[9]; //HE CAMBIADO LA Ñ PORQUE SINO EL PROGRAMA NO FUNCIONA PARA QUE USEIS SIEMPRE SIN LA Ñ
    char **id_obj; //inventario
    int num_inventario;
    int ubicacion_actual;
} jugadores;


typedef struct
{
    int id_sala;
    char nombre_sala[31];
    char tipo[8]; /* INICIAL, NORMAL O SALIDA */
    char descripcion[151];
} salas;

typedef struct
{
    char id_puzles[4]; // es por ejemplo P01,P02,...
    char nomb_puz[50];
    int id_sala;
    char tipo[10];
    char descrip[151];
    char sol[51]; /* solución */
} puzles;

typedef struct
{
    char id_obj[5];
    char nomb_obj[21];  //16 pa el espacio del \0
    char descrip[100];
    int id_sala; /* si es -1 esta en el inventario */
} objetos;

typedef struct
{
    char id_conexion[4];
    int id_origen;
    int id_destino;
    char estado[10];
    char cond[10];
} conexiones;

typedef struct
{
    jugadores jugador[20];
    salas sala[30];
    puzles puzle[30];
    objetos objeto[20];
    conexiones conexion[20];
} partida; /* aqui se unen todas las estructuras */

void Nueva_partida(partida *p,int u);
void Cargar_partida(partida *p, int u);
void Bienvenida(partida *p, int u);

#endif // CONFIGURACION
