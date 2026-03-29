#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "configuracion.h"


void Inicio_escape_room(partida *p){

    int ubicacion_actual=0; //esto pa la estructura, lo suyo seria ir actualizando en funcion de el id_sala
    system("cls");
                                                //printf("DEBUG: id_sala = %d\n", p->sala[0].id_sala); si pone 0 no esta cargado

    printf(" %s\n", p->sala[ubicacion_actual].nombre_sala);
    printf("--------------------------------\n\n");

    //voy a ser una dramas que todos los sepais
    printf("\033[33m");
    printf("Mhm... Donde estoy?\n");

    printf("\033[0m");
    printf("Una tenue luz se filtraba por una ventanilla que habia en la puerta.\n");

    printf("\033[33m");
    printf("No recuerdo nada...\n");

    printf("\033[0m");
    printf("Poco a poco te incorporas y te levantas de lo que parece ser un pupitre.\n\n\n");

    menu_opciones_juego(ubicacion_actual, p);
}

void menu_opciones_juego(int ubicacion_actual, partida *p){

    int volver_menu=0, fin_de_juego=0, eleccion=11;
    system("pause");
    system("cls");

   do{

    printf(" %s\n", p->sala[ubicacion_actual].nombre_sala);
    printf("--------------------------------\n\n");

    printf("1. Describir Sala\n2. Examinar Sala\n3. Moverse\n4. Coger objeto\n5. Soltar objeto\n");
    printf("6. Inventario\n7. Usar objeto\n8. Resolver puzle\n9. Guardar partida\n10. Volver\n\n\n");

    scanf("%d", &eleccion);
    printf("\n\n");

    switch (eleccion){

        case 1: //describir sala - FUNCIONA NO TOCAR

            printf("%s\n\n", p->sala[ubicacion_actual].descripcion);
            system("pause");
            system("cls");

            break;

        case 2: //examinar sala por objetos y salidas

            system("pause");
            system("cls");

            break;

        case 3: //Moverse (fichero conexiones)

            if(p->conexion[ubicacion_actual].cond!=0){ //esto hay que revisarlo porque no se que pasa si tengo mas de una conexion y una funciona y la otra no

                printf("No puedo irme todavia, tengo que hacer algo aqui.\n\n");
                system("pause");
                system("cls");

            }else {

                printf("Parece que puedo ir a...\n\n");

                for (int cont=0; cont<=17; cont++){ //recorremos todas las conexiones

                    if (p->conexion[cont].id_origen == p->sala[ubicacion_actual].id_sala){

                            //si el origen de la conexion coincide con la sala en la que estamos

                            printf("%s\n", p->sala[p->conexion[cont].id_destino].nombre_sala);

                            //tenemos que guardarnos este destino en un vector para poder elegir después.
                    }

                    cont++;

                }

            }


            break;

        case 4: {//Coger objeto (si lo hay)
           int i;
            char op;
          /*  for(i=0;p.objeto[i].id_obj==NULL;i++){
                if(ubicacion_actual==p.objeto[i].id_sala){
                    printf("Vaya parece que hay un %s\n",p.objeto[i].nomb_obj);
                    printf("Quieres cogerlo? s/n\n");
                    scanf(" %c",&op);
                    fflush(stdin);
                    if(op=='s'){

                    }

                }
            }*/
            system("pause");
            system("cls");
        }
            break;

        case 5: //Soltar objeto (si es que tienes)

            printf("Nada aun\n");
            system("pause");
            system("cls");

            break;

        case 6:  //Ver inventario

            printf("Los objetos que tengo encima son:\n");

            system("pause");
            system("cls");
            break;

        case 7: //Usar objeto (Si es necesario en la sala)

            printf("Nada aun\n");
            system("pause");
            system("cls");

            break;

        case 8: //Resolver puzle (si hay puzle)

            printf("Nada aun\n");
            system("pause");
            system("cls");

            break;

        case 9:  //guardar partida

            printf("Nada aun\n");
            system("pause");
            system("cls");

            break;

        case 10:  //volver - FUNCIONA NO TOCAR

            volver_menu=1;
            Bienvenida(&p);
            break;

        default:

            printf("No puedo hacer eso\n");
            system("pause");
            system("cls");

        break;

    }



   }while (fin_de_juego==0 && volver_menu==0);


        //En este punto del juego ya se puede escapar, hay que escribir el final

}
