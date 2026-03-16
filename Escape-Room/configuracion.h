#ifndef CONFIGURACION
#define CONFIGURACION
#include <stdio.h>


typedef struct
{
    int id_jugador;
    char nomb_jugador[21];
    char jugador[11];
    char contrasena[9]; //HE CAMBIADO LA Ñ PORQUE SINO EL PROGRAMA NO FUNCIONA PARA QUE USEIS SIEMPRE SIN LA Ñ
    char id_obj[5][4];
} Jugadores;


typedef struct
{
    int id_sala;
    char nombre_sala[31];
    char tipo[8]; /* INICIAL, NORMAL O SALIDA */
    char descrip[151];
} Salas;

typedef struct
{
    int id_puzles;
    char nomb_puz[16];
    int id_sala;
    int tipo; /* Código es 0 o Palabra es 1 */
    char descrip[151];
    char sol[51];
} Puzles;

typedef struct
{
    char id_conexion[4];
    int id_origen;
    int id_destino;
    int estado; /* Activo es 0 y Bloqueado es 1 */
    int cond; /* booleano 0 si no aplica, id_obj o id_puzle */
    Puzles id_puzles;
    Objetos id_objeto;
} Conexiones;

typedef struct
{
    char id_obj[5];
    char nomb_obj[15];
    char descrip[51];
    Salas id_salas; /* si este campo esta vacío se entiende que esta en el inventario */
} Objetos;

typedef struct
{
    /* Id_jugador
    id_sala
    id_obj, localización
    id_conexion, Estado
    puzle: id_puzle, resuelto/pendiente*/
} Partida; /* aqui se unen todas las estructuras */

#endif // CONFIGURACION
