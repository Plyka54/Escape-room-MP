#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include "juego.h"
#include "puzles.h"
#include "configuracion.h"
#include "ficheros.h"

void mostrar_mapa();
void final_malo();
void game_over();

//Cabecera: void Inicio_escape_room(partida *p,int u)
//Precondicion: El usuario debe de estar en una partida nueva, no en una cargada.
//Postcondicion: Se inicializan a 0 distintos campos de las estructuras y comienzan la historia del juego.
void Inicio_escape_room(partida *p,int u){

    int mapa=0;
    p->jugador[u].ubicacion_actual=0; //esto pa la estructura, lo suyo seria ir actualizando en funcion de el id_sala
    system("cls");


    //printf("DEBUG: id_sala = %d\n", p->sala[0].id_sala); si pone 0 no esta cargado

    printf(" %s\n", p->sala[p->jugador[u].ubicacion_actual].nombre_sala);
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

    p->jugador[u].num_inventario = 0;
    p->jugador[u].id_obj = NULL;

    menu_opciones_juego(p,u,mapa);
}

//Cabecera: void menu_opciones_juego(int ubicacion_actual, partida *p,int u)
//Precondicion: Ubicacion actual del jugador inicializada
//Postcondicion: La funcion presenta todas las opciones del menu del juego
void menu_opciones_juego( partida *p,int u, int mapa){
                                                                                   //Lo de declarar 40 variables iguales en cada caso hay que arreglarlo eh
    int volver_menu=0, fin_de_juego=0, eleccion_switch=11, puzle=0, alarma=3;       //Booleanos
    char respuesta;
    int ubicacion_actual, destino;
    ubicacion_actual=p->jugador[u].ubicacion_actual;

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

        case 1: //describir sala - FUNCIONA

            printf("\033[33m");
            printf("%s\n\n", p->sala[ubicacion_actual].descripcion);
            printf("\033[0m");



            if(ubicacion_actual==13) puzle_morse(p); //acordaos que los puzles hay que ponerlos en un numero menos porque es un vector las salas
            if(ubicacion_actual==7) puzle_switch(p);
            if(ubicacion_actual==6) puzle_despacho(p);
            if(ubicacion_actual==15) puzle_final(p);

            system("pause");
            system("cls");

            break;

        case 2: //examinar sala por objetos y salidas - FUNCIONA NO TOCAR

            printf("\033[33m");
            printf("Voy a buscar cosas en la sala...\n");
            printf("\033[0m");

            int i,j,k,cont=0, puzle_sala=0, conexion_asociada;

            for(i=0;i<num_objetos;i++){
                if(p->sala[ubicacion_actual].id_sala==p->objeto[i].id_sala){
                    if(cont==0){
                        printf("\033[33m");
                        printf("He encontrado...\n\n");
                        printf("\033[0m");
                    }
                    cont++;
                    printf("%d.%s\n",cont,p->objeto[i].nomb_obj);
                }
            }

            printf("\033[0m");

            if(cont==0){

                printf("\033[33m");
                printf("En esta sala no parece haber ningun objeto\n");
                printf("\033[0m");
            }
            for(i=0;i<0;i++)
            {
                conexion_asociada=-1;

                if(p->puzle[i].id_sala==p->sala[ubicacion_actual].id_sala)
                {
                    for(k=0;k<num_conexiones;k++)
                    {
                        if(strcmp(p->conexion[k].cond,p->puzle[i].id_puzles)==0)
                        {
                            conexion_asociada=k;
                            break;
                        }
                    }
                    if(conexion_asociada=-1 && strcmp(p->conexion[conexion_asociada].cond, "0")!=0)
                    {
                        puzle_sala=1;
                        break;
                    }
                }
            }

            printf("\033[33m");
            if(puzle_sala==1)
            {
                printf("Parece que hay un puzle pendiente en esta sala.\n");
            } else
            {
                printf("No parece haber ningun puzle pendiente en esta sala.\n");
            }
            printf("\033[33m");

            printf("\033[33m");
            printf("\nVoy a buscar las salidas de esta sala...\n\n");
            printf("\033[0m");

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

            printf("\033[0m");

            system("pause");
            system("cls");

            break;

        case 3: //Moverse (fichero conexiones)  FUNCIONA - NO TOCAR

                if(mapa==1){ //si tenemos el mapa podremos usarlo siempre que queramos

                    printf("Quieres ver el mapa antes de moverte? (s/n)\n");
                    scanf(" %c", &respuesta);

                    if (respuesta=='s'||respuesta=='S') mostrar_mapa();

                }

                printf("\033[33m");
                printf("Veamos por donde puedo ir");

                for (int j = 0; j < 3; j++) {
                    printf(".");
                    fflush(stdout);   // fuerza que el punto aparezca ya
                    sleep(1);         // espera 1 segundo
                }

                printf("\n");

                printf("\033[0m");


                for (int cont=0; cont<=17; cont++){ //recorremos todas las conexiones


                    if (p->conexion[cont].id_origen == p->sala[ubicacion_actual].id_sala){ //CONEXION ENCONTRADA


                          /*  printf("ORIGEN=%d DESTINO=%d COND=[%s]\n",
                                p->conexion[cont].id_origen,
                                p->conexion[cont].id_destino,
                                p->conexion[cont].cond);*/

                            if(strcmp(p->conexion[cont].cond, "0")== 0){ //CONEXION ABIERTA, POSIBLE DESPLAZAMIENTO DEL JUGADOR

                                printf("\033[33m");
                                printf("\nPuedo ir a [%s]\n", p->sala[p->conexion[cont].id_destino - 1].nombre_sala); //-1 porque el destino tiene id=2 y el indice debe ser el 1 (por ejemplo)
                                printf("\033[0m");

                                printf("Quieres ir por aqui? (s/n)\n");

                                    scanf(" %c", &respuesta);

                                    if (respuesta=='s' || respuesta=='S'){ //Actualizamos la posicion actual del jugador

                                        ubicacion_actual=p->sala[p->conexion[cont].id_destino - 1].id_sala -1; //el primer -1 accede al vector y el segundo -1 le cambia el valor a ubicacion actual
                                        break; //no se a donde lleva este break -- LAURA ESTE BREAK TE LLEVA A LA VICTORIA

                                    }

                            }else{

                                printf("\033[33m");
                                printf("Hay una salida bloqueada que me lleva a [%s]\n", p->sala[p->conexion[cont].id_destino - 1].nombre_sala);
                                printf("Quiza pueda hacer algo para desbloquear la salida\n\n");
                                printf("\033[0m");

                            }

                    }else if (p->conexion[cont].id_destino == p->sala[ubicacion_actual].id_sala){ //CONEXION ENCONTRADA


                        if(strcmp(p->conexion[cont].cond, "0")== 0){ //CONEXION ABIERTA, POSIBLE DESPLAZAMIENTO DEL JUGADOR

                                printf("\033[33m");
                                printf("Puedo ir a [%s]\n", p->sala[p->conexion[cont].id_origen -1].nombre_sala);
                                printf("\033[0m");
                                printf("Quieres ir por aqui? (s/n)\n");

                                    scanf(" %c", &respuesta);

                                    if (respuesta=='s' || respuesta=='S'){ //Actualizamos la posicion actual del jugador

                                        ubicacion_actual=p->sala[p->conexion[cont].id_origen -1].id_sala -1;
                                        break; //tampoco se donde lleva

                                    }

                        }else{
                            printf("\033[33m");
                            printf("Hay una salida bloqueada que me lleva a [%s]\n", p->sala[p->conexion[cont].id_origen].nombre_sala);
                            printf("Quiza pueda hacer algo para desbloquear la salida\n\n");
                            printf("\033[0m");
                            system("pause");
                        }


                    }
                }
            system("pause");
            system("cls");
            break;

        case 4: {//Coger objeto (si lo hay)
            int i, cont, num_actual;
            char op1, op2;
            char **inventario;

            printf("\033[33m");
            printf("Veamos que hay para coger...\n");
            printf("\033[0m");

            do {
                cont = 0;
                for (i = 0; i < num_objetos; i++) {
                    if (p->sala[ubicacion_actual].id_sala == p->objeto[i].id_sala) {
                        cont++;
                        printf("\033[33m");
                        printf("He encontrado un %s\n", p->objeto[i].nomb_obj);
                        printf("\033[0m");
                        printf("Quieres cogerlo? s/n\n");
                        scanf(" %c", &op1);


                        if (op1 == 's' || op1=='S') {
                            p->jugador[u].num_inventario++;
                            num_actual = p->jugador[u].num_inventario;

                            inventario = (char **)realloc(p->jugador[u].id_obj, num_actual * sizeof(char *));

                            if (inventario != NULL) {
                                p->jugador[u].id_obj = inventario;

                                p->jugador[u].id_obj[num_actual - 1] = strdup(p->objeto[i].id_obj);

                                printf("\nHas cogido el objeto: %s!\n", p->objeto[i].nomb_obj);
                                printf("%s\n\n", p->objeto[i].descrip);  // esto es pa ver la descripcion
                                p->objeto[i].id_sala = -1; // Lo quitamos de la sala


                                if (strcmp(p->jugador[u].id_obj[num_actual-1], p->objeto[3].id_obj)==0) mapa=1;

                            } else {
                                printf("Error de memoria.\n");
                                p->jugador[u].num_inventario--; // Deshacemos el incremento si falla
                            }


                        }
                    }
                }

                if (cont == 0){
                        printf("\033[33m");
                        printf("\nNo hay nada mas aqui.\n");
                        printf("\033[0m");
                        break;
                }

                printf("Quieres coger otro objeto? (s/n)\n");
                scanf(" %c", &op2);

            } while (op2 == 's' || op2=='S');

            system("pause");
            system("cls");
            break;
        }
        case 5: //Soltar objeto (si es que tienes)
            //AQUI LO UNICO QUE FALTA ES SI PONE OTRO NUMERO SE CIERRA EL PROGRAMA
            {
            int i,j,op;

            printf("\033[33m");
            printf("Veamos que objetos tengo en el inventario...\n");
            printf("\033[0m");

            if(p->jugador[u].num_inventario==0){
                printf("No tienes ningun objeto en el inventario para soltar\n\n");
                system("pause");
                system("cls");
                break;
            }
            else{
                printf("Que objeto quieres soltar?\n");
                for(i=0;i<p->jugador[u].num_inventario;i++){
                    for(j=0;j<num_objetos;j++){
                        if(strcmp(p->jugador[u].id_obj[i],p->objeto[j].id_obj)==0){
                            printf("%d. %s\n",i+1,p->objeto[j].nomb_obj);
                        }
                    }
                }


                //por si se introduce una letra
                if (scanf("%d", &op) != 1) {
                    printf("Error: Debes introducir un numero.\n");

                    fflush(stdin);

                    system("pause");
                    system("cls");
                    break;
                }


                if (op < 1 || op > p->jugador[u].num_inventario) {
                    printf("Error: Ese numero no corresponde a ningun objeto de tu inventario.\n");
                    system("pause");
                    system("cls");
                    break;
                }

                int indice=op-1;
                for(j=0;j<num_objetos;j++){ //para que el objeto se quede en la sala actual
                    if(strcmp(p->jugador[u].id_obj[indice],p->objeto[j].id_obj)==0){
                        p->objeto[j].id_sala=p->sala[ubicacion_actual].id_sala;
                        printf("Has soltado %s\n\n",p->objeto[j].nomb_obj);
                    }
                }

                //vaciar el inventario
                free(p->jugador[u].id_obj[indice]);
                for(i=indice;i<p->jugador[u].num_inventario;i++){
                    p->jugador[u].id_obj[i]=p->jugador[u].id_obj[i+1];
                }
                p->jugador[u].num_inventario--;

                //ajustar memoria
                if (p->jugador[u].num_inventario > 0) {
                    p->jugador[u].id_obj = (char **)realloc(p->jugador[u].id_obj, p->jugador[u].num_inventario * sizeof(char *));
                }
                    else {
                        free(p->jugador[u].id_obj);
                        p->jugador[u].id_obj = NULL;
            }
        }

            system("pause");
            system("cls");

            break;}

        case 6:  //Ver inventario - FUNCIONA
        {
            int i,j;

            if(p->jugador[u].num_inventario == 0)
            {
                printf("No tienes ningun objeto en el inventario.\n");
            } else
            {
                printf("Los objetos que tengo encima son:\n");

                for(i=0;i<p->jugador[u].num_inventario;i++)
                {
                    for(j=0;j<num_objetos;j++)
                    {
                        if(strcmp(p->jugador[u].id_obj[i], p->objeto[j].id_obj) == 0)
                        {
                            printf("%d. %s: %s\n\n",i+1, p->objeto[j].nomb_obj,  p->objeto[j].descrip);
                        }
                    }
                }
            }

            system("pause");
            system("cls");
            break;

        }

        case 7: //Usar objeto (Si es necesario en la sala)
        {
            int i, j, op, indice, pos_objeto = -1, usado = 0;
            char *id_usado;

            if (p->jugador[u].num_inventario==0)
            {
                printf("No tienes ningun objeto en el inventario.\n");
            } else
            {
                printf("Que objeto quieres usar?\n");   // Mostramos el inventario para elegir objeto

                for (i=0;i<p->jugador[u].num_inventario;i++)
                {
                    for (j=0;j<num_objetos;j++)
                    {
                        if (strcmp(p->jugador[u].id_obj[i], p->objeto[j].id_obj)==0)
                        {
                            printf("%d. %s\n", i + 1, p->objeto[j].nomb_obj);
                            break;
                        }
                    }
                }  //de aqui pa arriba bien

                if(scanf("%d",&op)!=1)
                {
                    printf("Opcion no valida.\n");
                    while(getchar()!='\n');
                } else
                {
                    while(getchar()!='\n');
                    indice=op-1;

                    if (indice<0 || indice>=p->jugador[u].num_inventario)
                    {
                        printf("Opcion no valida.\n");
                    } else
                    {
                        id_usado = p->jugador[u].id_obj[indice];   // Se guarda el id del objeto elegido

                        for (j=0;j<num_objetos;j++)
                        {
                            if (strcmp(id_usado, p->objeto[j].id_obj)==0)
                            {
                                pos_objeto = j;
                                break;
                            }
                        }

                        if (pos_objeto==-1)
                        {
                            printf("No se ha encontrado ese objeto.\n");
                        }
                        else if (strcmp(id_usado,"OB04")==0)   // MAPA
                        {
                            mapa = 1;
                            printf("Has usado %s.\n", p->objeto[pos_objeto].nomb_obj);
                            printf("%s\n", p->objeto[pos_objeto].descrip);
                            printf("Ahora puedes consultar el mapa antes de moverte.\n");
                        }
                        else if (strcmp(id_usado,"OB05")==0)   // MORSE
                        {
                            printf("Has usado %s.\n", p->objeto[pos_objeto].nomb_obj);
                            printf("%s\n", p->objeto[pos_objeto].descrip);
                            diccionario_morse();
                            printf("\n");
                        }
                        else
                        {
                            for (j=0;j<num_conexiones; j++)
                            {
                                if ((p->conexion[j].id_origen == p->sala[ubicacion_actual].id_sala || p->conexion[j].id_destino == p->sala[ubicacion_actual].id_sala) && strcmp(p->conexion[j].cond, id_usado) == 0)
                                {
                                    strcpy(p->conexion[j].cond, "0");
                                    strcpy(p->conexion[j].estado, "Activa");
                                    printf("Has usado %s.\n", p->objeto[pos_objeto].nomb_obj);
                                    printf("%s\n", p->objeto[pos_objeto].descrip);
                                    printf("\033[33m");
                                    printf("Parece que una salida se ha desbloqueado.\n");
                                    printf("\033[0m");
                                    usado = 1;
                                    break;
                                }
                            }

                            if (usado==0)
                            {
                                printf("No puedes usar %s aqui.\n", p->objeto[pos_objeto].nomb_obj);
                            }
                        }
                    }
                }
            }
            system("pause");
            system("cls");
            break;
        }

        case 8:{ //Resolver puzle (si hay puzle) FUNCIONA NO TOCAR

            char solucion[51];


            for(int cont=0;cont<6;cont++){ //Recorremos todos los puzles     OJO QUE SI METEMOS MÁS HAY QUE CAMBIAR ESTE BUCLE

                int conexion_asociada = -1; // lo pongo aqui pa que reinicie valor

                if(p->puzle[cont].id_sala == p->sala[ubicacion_actual].id_sala){ //puzle en esta sala

                        for (int k = 0; k < 17; k++) { //Recorremos las conexiones para ver en cual esta el puzle encontrado.
                            if (strcmp(p->conexion[k].cond, p->puzle[cont].id_puzles) == 0) {
                                conexion_asociada = k;
                                break;
                            }
                        }

                    //Si recorriendo las conexiones no encontramos ninguna, se pasa a lo siguiente y no se muestra el puzle otra vez

                if (conexion_asociada == -1 || strcmp(p->conexion[conexion_asociada].cond, "0") == 0) continue;

                    puzle=1;
                    printf("\033[33m");
                    printf("Parece que tenemos un puzle. Veamos...\n\n");
                    printf("\033[0m");
                    printf("Puzle: %s\n\n", p->puzle[cont].descrip);

                    scanf("%s", solucion);

                    if(strcmp(p->puzle[cont].sol, solucion)==0){ //METER QUE CONEXION ES LA QUE SE HA ABIERTO

                            printf("\033[33m");
                            printf("Genial! He resuelto el puzle y parece que una salida se ha desbloqueado. Deberia investigarlo.\n\n");
                            printf("\033[0m");


                            if (p->conexion[conexion_asociada].id_origen == p->sala[ubicacion_actual].id_sala) {    //ESTO ES PARA VER CUAL SE HA ABIERTO.

                                destino = p->conexion[conexion_asociada].id_destino - 1;

                            } else {

                                destino = p->conexion[conexion_asociada].id_origen - 1;

                            }


                            printf("Has abierto el camino a [%s]!\n\n", p->sala[destino].nombre_sala);

                            strcpy(p->conexion[conexion_asociada].cond, "0"); //cambiamos fichero
                            strcpy(p->conexion[conexion_asociada].estado, "Activa");
                            puzle=0;


                    }else{

                        printf("\033[33m");
                        printf("Parece que esta clave es incorrecta...\n");

                        printf("\033[0m");

                        if(strcmp(p->puzle[cont].id_puzles, "P06")==0){


                            alarma=alarma-1;
                            printf("\033[33m");
                            printf("Debo de tener cuidado! Solo me quedan %d intentos\n", alarma);
                            printf("\033[0m");

                            if(alarma==0){

                                printf("\033[33m");
                                printf("No me quedan intentos.\n");
                                printf("\033[0m");

                                final_malo();

                                break;
                            }

                        }

                    }


                }

            printf("\033[33m");

            }if(puzle==0) printf("Parece que no queda ningun puzle que resolver aqui.\n");
            printf("\033[0m");
            system("pause");
            system("cls");

            break;
        }

        case 9:  //guardar partida
        {
            FILE *f;
            int i, j, id_leido, resuelto;
            char linea[200];
            char *ids_puzles[] = {"P01","P02","P03","P04","P05","P06"}; //hay que actualizarlo si se ponen mas puzles
            int total_puzles = 6;

            char **lineas_guardadas = NULL;
            int num_lineas = 0;

            //mira si hay alguna partida anterior guardada en el fichero y la borra
            f=fopen("data/partida.txt","r");
            if (f != NULL) {
                while (fgets(linea, sizeof(linea), f) != NULL) {
                    if (sscanf(linea, "%d-", &id_leido) == 1) {
                        if (id_leido != p->jugador[u].id_jugador) {
                            char **temp = (char **)realloc(lineas_guardadas, (num_lineas + 1) * sizeof(char *));
                            if (temp != NULL) {
                                lineas_guardadas = temp;
                                lineas_guardadas[num_lineas] = strdup(linea);
                                num_lineas++;
                            } else {
                                printf("Error de memoria al leer el fichero.\n");
                            }
                        }
                    }
                }
                fclose(f);
            }
                //escribimos en el fichero
                f = fopen("data/partida.txt", "w");
                if (f == NULL) {
                    printf("Error al abrir el fichero para guardar.\n");
                } else {
                    // A) Volcamos las líneas de los otros jugadores
                    for (i = 0; i < num_lineas; i++) {
                        fprintf(f, "%s", lineas_guardadas[i]);
                        free(lineas_guardadas[i]); // Liberamos la memoria de la cadena ya usada
                    }

                    // Liberamos el vector principal ahora que está vacío
                    free(lineas_guardadas);

                    // B) Escribimos la NUEVA partida del jugador actual
                    fprintf(f, "%02d-%d", p->jugador[u].id_jugador, p->sala[ubicacion_actual].id_sala);

                    for (i = 0; i < p->jugador[u].num_inventario; i++) {
                        fprintf(f, "-%s", p->jugador[u].id_obj[i]);
                    }

                    fprintf(f,"-FININV");

                    for(i=0;i<num_objetos;i++)
                    {
                        if(p->objeto[i].id_sala==-1)
                        {
                            fprintf(f, "-%s-INV", p->objeto[i].id_obj);
                        } else
                        {
                            fprintf(f, "-%s-%d", p->objeto[i].id_obj, p->objeto[i].id_sala);
                        }
                    }

                    //conexiones abiertas
                    fprintf(f,"-FINCON");
                    for (i = 0; i < num_conexiones; i++)
                    {
                        if (strcmp(p->conexion[i].estado, "Activa") == 0)
                        {
                            fprintf(f, "-%s-%s", p->conexion[i].id_conexion, p->conexion[i].estado);
                        }
                    }

                    //Estado de los puzles
                    fprintf(f, "-FINPUZ");
                    for (i = 0; i < total_puzles; i++)
                    {
                        resuelto = 1;

                        for (j = 0; j < num_conexiones; j++)
                        {
                            if (strcmp(p->conexion[j].cond, ids_puzles[i]) == 0)
                            {
                                resuelto = 0;
                                break;
                            }
                        }

                        if (resuelto == 1)
                        {
                            fprintf(f, "-%s-Resuelto", ids_puzles[i]);
                        } else
                        {
                            fprintf(f, "-%s-Pendiente", ids_puzles[i]);
                        }
                    }

                    fprintf(f, "\n"); // El salto de línea fundamental

                    fclose(f);
                    printf("\nPartida guardada con exito.\n");
                }

                system("pause");
                system("cls");

                break;
        }

        case 10:  //volver - FUNCIONA NO TOCAR

            volver_menu=1;
            Bienvenida(p,u);  // he quitado la i inglesa pq bienvenida es con p y u
            break;

        default:

            printf("\033[33m");
            printf("No puedo hacer eso\n");
            printf("\033[0m");
            system("pause");
            system("cls");

        break;

    }



   }while(fin_de_juego==0 && volver_menu==0);

        if(fin_de_juego==1){

            printf("\033[33m");
            printf("-Nada mas abrir la puerta, eche a correr sin mirar atras, con miedo a que alguien pudiese haberme visto salir.-\n\n ");
            printf("-Ya estaba amaneciendo, asi que me escondi entre los arboles, esperando a que algun autobus con alumnos llegase.-\n");
            printf("\033[0m");
            printf("Pasada 1 hora, por fin viste llegar a un autobus de Cadiz, e incapaz de asistir ese dia a las clases de MP, decidiste irte a casa.\n");

            printf("\nENHORABUENA, HAS CONSEGUIDO ESCAPAR DE LA ESI\n");

        }


}

void mostrar_mapa(){


printf(
"          [AULA PRACTICAS]                     [PASILLO F]--[DESPACHO DEL PROFESOR]\n"
"                      |                          |\n"
"                      |                          |\n"
"    [AULA TEORIA]--[PASILLO B]--[P A S I L L O   P R I N C I P A L]--[BIBLIOTECA]\n"
"                      |           |       |              |       |\n"
"                      |           |       |              |       |\n"
"                      |           |       |              |       |\n"
"                     [WC]         |   [CAFETERIA]        | [CONSERJERIA]--[COPISTERIA]\n"
"                                  |       |              |       |\n"
"                                  |       |              |       |\n"
"                                  |  [CUARTO LIMPIEZA]   |     [HALL]--[ENTRADA DE LA ESI]\n"
"                                  |                      |\n"
"                              [PASILLO A]                |\n"
"                                  |                 [PASILLO C]\n"
"                                  |                      |\n"
"                             [AULA MAGNA]                |\n"
"                                                   [LABORATORIO C]\n"
);

}

void game_over(){


    printf("\033[31m");
    printf(" _____   ___  ___  ___ _____   _____  _   _ ___________ \n"
       "|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\\n"
       "| |  \\ / /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ /\n"
       "| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    / \n"
       "| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ \n"
       " \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|\n"
       "                                                         \n"
       "                                                        \n");

    printf("\033[0m");

}

void diccionario_morse(){

    printf("A = .-\nB = -...\nC = -.-.\nE = .\nI = ..\nO = ---\nU = ..-\nS = ...\n");

    printf("\033[33m");
    printf("\nParece que la parte de abajo se ha mojado, no puedo seguir leyendo.");
    printf("\033[0m");

}

void final_malo(){

    int opcion_final=2;

    system("cls");

    printf("De repente, empieza a sonar una alarma bastante ruidosa\n\n");

    printf("\033[33m");
    printf("Maldicion! He fallado demasiadas veces.\n");
    printf("\033[0m");

    system("pause");

    printf("De repente, a lo lejos podias ver una luz acercandose a ti, como si alguien estuviese corriendo en tu direccion.\n\n");

    printf("\033[36m");
    printf("Guarda de seguridad: Quien anda ahi?\n");
    printf("\033[0m");


    printf("Rapido! Te estan persiguiendo! Que quieres hacer?\n");
    printf("1. Correr\n2. Esconderse\n\n");
    scanf("%d", &opcion_final);

    switch(opcion_final){

    case 1: //Correr, FINAL MALO

        printf("Sin saber muy bien a donde, empiezas a correr por el pasillo principal\n\n");
        printf("Decides doblar la esquina en el pasillo B, para meterte en el baño.\n\n");

        printf("Para tu mala suerte, el guarda te habia visto entrar\n\n");

        printf("\033[36m");
        printf("Guarda de seguridad: No sirve de nada esconderse, le he visto.\n\n");
        printf("\033[0m");

        printf("Para evitar mas problemas de los que ya tienes encima, decides salir voluntariamente.\n\n");

        printf("El guarda decide esposarte como medida de seguridad y avisan a un coche patrulla que habia por la zona para llevarte a comisaria\n\n");

        printf("Una vez han tomado declaracion y tus datos, deciden dejarte ir, no sin comunicarlo a la junta directiva de tu universidad.\n\n");

        system("pause");

        printf("Pasado el fin de semana, habiendo respondido a algunos correos, se instrujo que debias asistir a una reunion con el director.\n");

        printf("Durante la reunion, intentas excusarte, contando que te despertaste en el aula encerrado, y que hiciste lo que pudiste para salir\n\n");

        printf("Los profesores decidieron no abrirte expediente vistas las circunstancias, pero si que te hicieron ayudar con algunas tareas, a lo que aceptaste sin mas remedio.\n");



        system("cls");
        game_over();

        break;

    case 2: //Esconderse, FINAL MENOS MALO

        printf("Sin mucho tiempo para pensar, decides esconderte detras de la maquina de recargo de tarjetas de autobus que hay al lado de la entrada.\n\n");

        printf("Intentaste por todos los medios aguantar la respiracion, con la esperanza de no ser visto y poder escapar por la puerta que el guarda acababa de abrir.\n\n");

        printf("Para tu mala suerte, el guarda habia anticipado esta posibilidad y te acabo viendo de todas maneras.\n\n");

        printf("El guarda decide esposarte como medida de seguridad y avisan a un coche patrulla que habia por la zona para llevarte a comisaria\n\n");

        printf("Una vez han tomado declaracion y tus datos, deciden dejarte ir, no sin comunicarlo a la junta directiva de tu universidad.\n\n");

        system("pause");

        printf("Pasado el fin de semana, habiendo respondido a algunos correos, se instrujo que debias asistir a una reunion con el director.\n\n");

        printf("Durante la reunion, intentas excusarte, contando que te despertaste en el aula encerrado, y que hiciste lo que pudiste para salir\n\n");

        printf("Los directivos deciden hablar con tus tutores legales, quienes se quejan por las curiosas medidas de seguridad que tiene el centro.\n\n");

        printf("Ante el argumento de 'como es que este lugar permite que un alumno se quede encerrado por la noche?' no pudieron decir mucho.\n\n");

        printf("Al final decidieron dejarte ir, pero no sin volverte alumno colaborativo de tu profesor de Metodologia de la programacion.\n\n");

        system("clear");
        game_over();

        break;

    default:

        printf("No puedo hacer eso.\n");
        break;

    }


}
