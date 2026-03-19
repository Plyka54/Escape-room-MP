#ifndef CONFIGURACION
#define CONFIGURACION
#include <stdio.h>


typedef struct
{
    int id_jugador;
    char nomb_jugador[21];
    char jugador[11];
    char contrasena[9]; //HE CAMBIADO LA Ñ PORQUE SINO EL PROGRAMA NO FUNCIONA PARA QUE USEIS SIEMPRE SIN LA Ñ
    char id_obj[5][5];
} jugadores;


typedef struct
{
    int id_sala;
    char nombre_sala[31];
    char tipo[8]; /* INICIAL, NORMAL O SALIDA */
    char descrip[151];
} salas;

typedef struct
{
    char id_puzles[4]; // es por ejemplo P01,P02,...
    char nomb_puz[16];
    int id_sala;
    int tipo; /* Código es 0 o Palabra es 1 */
    char descrip[151];
    char sol[51]; /* solución */
} puzles;

typedef struct
{
    char id_obj[5];
    char nomb_obj[16];  //16 pa el espacio del \0
    char descrip[51];
    int id_sala; /* si es -1 esta en el inventario */
} objetos;

typedef struct
{
    char id_conexion[4];
    int id_origen;
    int id_destino;
    int estado; /* Activo es 0 y Bloqueado es 1 */
    int cond; /* booleano 0 si no aplica, id_obj o id_puzle */
} conexiones;

typedef struct
{
    jugadores jugador[20];
    salas sala[30];
    puzles puzle[30];
    objetos objeto[20];
    conexiones conexion[20];
} partida; /* aqui se unen todas las estructuras */

#endif // CONFIGURACION
