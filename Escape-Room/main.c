#include <stdio.h>
#include "main.h"
#include "ficheros.h"
#include "configuracion.h"

void mostrar_titulo();

int main(){

    char usuario[10], clave[8];         //En el fichero jugadores.txt  usuario = campo "jugador"
    int user=0, password=0;             //Booleanos
    int opcion;

    mostrar_titulo();


// LOGIN DE USUARIO O REGISTRO -----------------------------------------------------------


    printf("Inicie sesion o registrese para continuar\n");

    printf("\nUsuario: ");
    scanf("%s", usuario);

    user=comprobar_usuario(usuario);

    if(user==1){

        printf("\nClave: ");
        scanf("%s", clave);

        pasword=comprobar_clave(clave);  //si la clave es correcta password=1

    }else{

        printf("Usuario no encontrado.");
        printf("Vamos a registrarte en la base de datos");

        void registro();
    }


// BIENVENIDA Y COMIENZO --------------------------------------------------------


    if (password==1){

        system(clear);
        printf("\n\n\n ¡Bienvenido a Escape Room ESI!\n\n\n");


        printf("Introduce lo que quieras hacer\n");

        printf("1. Nueva Partida\n");
        printf("2. Cargar Partida\n");
        printf("3. Salir\n");

        scanf("%d", &opcion);

        switch(opcion){

            case 1:

                Nueva_partida();

                break;

            case 2: //Cargar partida



                break;

            case 3: //Salir


                break;

            default:

                printf("Opcion no valida");

                break;

        }

    }

}

void mostrar_titulo(){

    // Azul
    printf("\033[34m");
    printf("   ____    ____     ___     __     ____    ____      ____     __      __     _  _ \n");
    printf("  (  __)  / ___)   / __)   / _\\   (  _ \\  (  __)    (  _ \\   /  \\    /  \\   ( \\/ )\n");
    printf("   ) _)   \\___ \\  ( (__   /    \\   ) __/   ) _)      )   /  (  O )  (  O )  / \\/ \\\n");
    printf("  (____)  (____/   \\___)  \\_/\\_/  (__)    (____)    (__\\_)   \\__/    \\__/   \\_)(_/\n");

    // Amarillo
    printf("\033[33m");
    printf("                           ____  ____  __                                         \n");
    printf("     ___  ___  ___  ___   (  __)/ ___)(  )   ___  ___  ___  ___                   \n");
    printf("    (___)(___)(___)(___)   ) _) \\___ \\ )(   (___)(___)(___)(___)                  \n");
    printf("                          (____)(____/(__)                                        \n\n\n");

    printf("\033[0m");

}

void registro(){ //me hace falta la estructura de lucia en configuracion


    char Nomb_comp[20], usuario[10], clave[8];


    printf("Introduce tu nombre completo: ");



    printf("Introduce tu nombre de usuario (10 caracteres maximo): ");



    printf("Introduce una clave (8 caracteres maximo): ");



}
