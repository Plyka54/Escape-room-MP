#ifndef FICHEROS
#define FICHEROS
#define num_objetos 7
#define num_salas 18
#define num_conexiones 17
#define num_puzles 6

#include "configuracion.h"

void carga(partida *p,int *total_leidos);
int comprobar_usuario(partida p,char user[11], int total_leidos, int *u);
int comprobar_clave(partida p, char *clave, int u);

#endif // FICHEROS
