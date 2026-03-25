#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "configuracion.h"


void Inicio_escape_room(partida *p){

    int ubicacion_actual=0; //esto pa la estructura, lo suyo seria ir actualizando en funcion de el id_sala
    system("cls");
    printf("%s\n", p->sala[ubicacion_actual].nombre_sala);
    printf("--------------------------------\n");

    //voy a ser una dramas que todos los sepais
    printf("\033[33m");
    printf("Mhm... Donde estoy?\n");

    printf("\033[0m");
    printf("Una tenue luz se filtraba por una ventanilla que habia en la puerta.\n");

    printf("\033[33m");
    printf("No recuerdo nada...\n");

    printf("\033[0m");
    printf("Poco a poco te incorporas y te levantas de lo que parece ser un pupitre.\n\n\n");

    menu_opciones_juego(ubicacion_actual, &p);
}

void menu_opciones_juego(int ubicacion_actual, partida *p){

    int eleccion=11;

   do{

    printf("1. Describir Sala\n2. Examinar Sala\n3. Moverse\n4. Coger objeto\n5. Soltar objeto\n");
    printf("6. Inventario\n7. Usar objeto\n8. Resolver puzle\n9. Guardar partida\n10. Volver\n");

    scanf("%d", &eleccion);

    switch (eleccion){

        case 1: //describir sala

            printf("%s", p->sala[ubicacion_actual].descripcion);

            break;

        case 2: //examinar sala por objetos y salidas

            break;

        case 3: //Moverse (fichero conexiones)

            break;

        case 4: //Coger objeto (si lo hay)

            break;

        case 5: //Soltar objeto (si es que tienes)

            break;

        case 6:  //Ver inventario

            break;

        case 7: //Usar objeto (Si es necesario en la sala)

            break;

        case 8: //Resolver puzle (si hay puzle)

            break;

        case 9:  //guardar partida

            break;

        case 10:  //volver

            Bienvenida(&p);
            break;

        default:

            printf("No puedo hacer eso\n");

        break;

    }

        system("cls");

   }while (eleccion>10);




}
