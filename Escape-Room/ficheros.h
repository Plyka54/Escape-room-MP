#ifndef FICHEROS
#define FICHEROS

#include "configuracion.h"

void carga(partida *p,int *total_leidos);
int comprobar_usuario(partida p,char user[11], int total_leidos, int *u);
int comprobar_clave(partida p, char *clave, int u);

#endif // FICHEROS
