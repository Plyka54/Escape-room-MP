#ifndef JUEGO
#define JUEGO
#include "configuracion.h"

#define num_objetos 6 //esto se tiene que cambiar porque supongo que habrá más
#define num_salas 18
#define num_conexiones 17

void Inicio_escape_room(partida *p,int u);
void menu_opciones_juego(int ubicacion_actual, partida *p,int u);

#endif // JUEGO
