#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "juego.h"
#include "configuracion.h"
#define num_objetos 4 //esto se tiene que cambiar porque supongo que habrá más
#define num_salas 18
#define num_conexiones 17


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

    int volver_menu=0, fin_de_juego=0, eleccion_switch=11;
    char respuesta;

    system("pause");
    system("cls");

   do{

    printf(" %s\n", p->sala[ubicacion_actual].nombre_sala);
    printf("--------------------------------\n\n");

    printf("1. Describir Sala\n2. Examinar Sala\n3. Moverse\n4. Coger objeto\n5. Soltar objeto\n");
    printf("6. Inventario\n7. Usar objeto\n8. Resolver puzle\n9. Guardar partida\n10. Volver\n\n\n");

    scanf("%d", &eleccion_switch);
    printf("\n\n");

    switch (eleccion_switch){

        case 1: //describir sala - FUNCIONA NO TOCAR

            printf("%s\n\n", p->sala[ubicacion_actual].descripcion);
            system("pause");
            system("cls");

            break;

        case 2: //examinar sala por objetos y salidas
            printf("Voy a buscar cosas en la sala...\n");
            printf("He encontrado:\n");
            int i,j,cont=0;
            for(i=0;i<num_objetos;i++){
                if(p->sala[ubicacion_actual].id_sala==p->objeto[i].id_sala){
                    cont++;
                    printf("%d.%s\n",cont,p->objeto[i].nomb_obj);
                }
            }
            printf("Voy a buscar las salidas de esta sala...\n");
            cont=0;
                for(j=0;j<num_conexiones;j++){
                 if(p->sala[ubicacion_actual].id_sala==p->conexion[j].id_origen){
                     cont++;
                    printf("%d. %s\n",cont,p->sala[p->conexion[j].id_destino-1].nombre_sala);
                 }
                 if(p->sala[ubicacion_actual].id_sala==p->conexion[j].id_destino){
                    cont++;
                    printf("%d. %s\n",cont,p->sala[p->conexion[j].id_origen-1].nombre_sala);
                 }
                }




            system("pause");
            system("cls");

            break;

        case 3: //Moverse (fichero conexiones)

                printf("Veamos por donde puedo ir");

                for (int j = 0; j < 3; j++) {
                    printf(".");
                    fflush(stdout);   // fuerza que el punto aparezca ya
                    sleep(1);         // espera 1 segundo
                }

                printf("\n");


                for (int cont=0; cont<=17; cont++){ //recorremos todas las conexiones


                    if (p->conexion[cont].id_origen == p->sala[ubicacion_actual].id_sala){ //CONEXION ENCONTRADA


                          /*  printf("ORIGEN=%d DESTINO=%d COND=[%s]\n",
                                p->conexion[cont].id_origen,
                                p->conexion[cont].id_destino,
                                p->conexion[cont].cond);*/

                            if(strcmp(p->conexion[cont].cond, "0")== 0){ //CONEXION ABIERTA, POSIBLE DESPLAZAMIENTO DEL JUGADOR

                                printf("\nPuedo ir a [%s]\n", p->sala[p->conexion[cont].id_destino - 1].nombre_sala); //-1 porque el destino tiene id=2 y el indice debe ser el 1 (por ejemplo)

                                printf("Quieres ir por aqui? (s/n)\n");

                                    scanf(" %c", &respuesta);

                                    if (respuesta=='s'){ //Actualizamos la posicion actual del jugador

                                        ubicacion_actual=p->sala[p->conexion[cont].id_destino - 1].id_sala -1; //el primer -1 accede al vector y el segundo -1 le cambia el valor a ubicacion actual
                                        break; //no se a donde lleva este break -- LAURA ESTE BREAK TE LLEVA A LA VICTORIA

                                    }

                            }else{

                                printf("Hay una salida bloqueada que me lleva a [%s]\n", p->sala[p->conexion[cont].id_destino - 1].nombre_sala);
                                printf("Quiza pueda hacer algo para desbloquear la salida\n\n");

                            }

                    }else if (p->conexion[cont].id_destino == p->sala[ubicacion_actual].id_sala){ //CONEXION ENCONTRADA


                        if(strcmp(p->conexion[cont].cond, "0")== 0){ //CONEXION ABIERTA, POSIBLE DESPLAZAMIENTO DEL JUGADOR

                                printf("Puedo ir a [%s]\n", p->sala[p->conexion[cont].id_origen -1].nombre_sala);

                                printf("Quieres ir por aqui? (s/n)\n");

                                    scanf(" %c", &respuesta);

                                    if (respuesta=='s'){ //Actualizamos la posicion actual del jugador

                                        ubicacion_actual=p->sala[p->conexion[cont].id_origen -1].id_sala -1;
                                        break; //tampoco se donde lleva

                                    }

                        }else{

                            printf("Hay una salida bloqueada que me lleva a [%s]\n", p->sala[p->conexion[cont].id_origen].nombre_sala);
                            printf("Quiza pueda hacer algo para desbloquear la salida\n\n");
                        }


                    }
                }

            break;

        case 4: {//Coger objeto (si lo hay)
            int i,cont=0, objeto_cogido;
            char op;
            printf("Veamos que hay para coger...\n");
            do{
            for(i=0;i<num_objetos;i++){
                if(p->sala[ubicacion_actual].id_sala==p->objeto[i].id_sala){
                    cont++;
                    printf("%d.%s\n",cont,p->objeto[i].nomb_obj);
                }

            }
            printf("Que objeto deseas coger? (numero)\n");
            scanf(" %c",&objeto_cogido);
            fflush(stdin);

            if(cont==0){
                printf("No hay objetos en esta sala\n");
                break;
            }
            printf("Desea coger otro objeto? s/n\n");
            scanf(" %c",&op);
            fflush(stdin);
            }while(op=='s');

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
