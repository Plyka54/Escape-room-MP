#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "ficheros.h"
#include "configuracion.h"

void mostrar_titulo();

int main(){

    char usuario[10], clave[8];         //En el fichero jugadores.txt  usuario = campo "jugador"
    int user=0, password=0;             //Booleanos para el login
    int opcion;
    partida p;


    mostrar_titulo();

    //CARGAMOS LOS FICHEROS
    int total_usuarios;
    carga(&p,&total_usuarios);
    //printf("%s\n",p.jugador[]);  -> para ir comprobando que se cargan bien los ficheros

// LOGIN DE USUARIO O REGISTRO -----------------------------------------------------------
    int u;

    printf("Inicie sesion o registrese para continuar\n"); //habra que poner para elegir una

    printf("\nUsuario: ");
    scanf("%s", usuario);
    fflush(stdin);

    user=comprobar_usuario(p,usuario,total_usuarios,&u);

    if(user==1){

        printf("\nClave: ");
        scanf(" %s", &clave[0]);

        password=comprobar_clave(p,clave,u);  //si la clave es correcta password=1
        if(password) printf("\nContrasena correcta\n");
        else {printf("\nContrasena incorrecta\n");}

    }else{

        printf("Usuario no encontrado.");
        printf("Vamos a registrarte en la base de datos\n");

        void registro();
    }


// BIENVENIDA Y COMIENZO --------------------------------------------------------

    if (password==1){   //EL CONTENIDO DEL IF TIENE QUE SER UNA FUNCION APARTE

        printf("\n");
        system("pause");
        Bienvenida(&p,u);

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


//Cabecera: void registro()
//Precondicion:
//Postcondicion: Se rellena la estructura "Jugadores" con los datos del nuevo jugador
void registro(jugadores *nuevo) //aqui deberias cambiar la estructura y cargar partida no jugadores deberias poner (partida *p)
{
   /* partida *reg=(partida *)realloc(sizeof(partida));
    //verifica si se reservo bien
    if(reg==NULL){
        printf("Error: no se pudo asignar memoria.\n");
    }
    else{
    FILE *f;*/
    //te falta abrir el fichero f=fopen...

    printf("Introduce tu nombre:");
    fgets(nuevo->nomb_jugador, sizeof(nuevo->nomb_jugador),stdin);

    printf("\nIntroduce tu nombre de usuario (10 caracteres max): ");
    fgets(nuevo->jugador, sizeof(nuevo->jugador),stdin);

    printf("\nIntroduce una contraseña (8 caracteres max):");
    fgets(nuevo->contrasena, sizeof(nuevo->contrasena),stdin);

    // falta lo del inventario vacio y tal mañana lo hago ._.

    //aqui hay que hacer memoria dinamica
    //}
}
