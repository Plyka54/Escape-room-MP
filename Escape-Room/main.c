#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "ficheros.h"
#include "configuracion.h"

void mostrar_titulo();
void registro(partida *, int *, int *);

int main(){

    char usuario[11], clave[9];         //En el fichero jugadores.txt  usuario = campo "jugador"
    int user=0, password=0;             //Booleanos para el login
    int opcion;
    partida p;


    mostrar_titulo();

    //CARGAMOS LOS FICHEROS
    int total_usuarios;
    carga(&p,&total_usuarios);

// LOGIN DE USUARIO O REGISTRO -----------------------------------------------------------
    int u;

    printf("Inicie sesion o registrese para continuar\n");

    printf("\nUsuario: ");
    scanf("%s", usuario);
    fflush(stdin);
    //comprobamos el usuario
    user=comprobar_usuario(p,usuario,total_usuarios,&u);

    if(user==1){
        do{
        printf("\nClave: ");
        scanf(" %s", &clave[0]);
        //comprobamos la contrasena
        password=comprobar_clave(p,clave,u);
        if(password) printf("\nContrasena correcta\n");
        else {printf("\nContrasena incorrecta\n");}
        }while(password==0);
    }else{

        printf("Usuario no encontrado.");
        printf("Vamos a registrarte en la base de datos\n");

        getchar();
        registro(&p,&total_usuarios,&u);
        password=1;

    }


// BIENVENIDA Y COMIENZO --------------------------------------------------------

    if (password==1){

        printf("\n");
        system("pause");
        Bienvenida(&p,u);

    }

}

//Cabecera: void mostrar_titulo()
//Precondicion:
//Postcondicion: Muestra por pantalla el titulo del juego y el logo mediante arte ASCII.
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
void registro(partida *p, int *total_usuarios, int *u)
{
    int i,j;
    int n=*total_usuarios;
    int max_id=0;  // esto es para calcular el siguiente id
    FILE *f;

    jugadores *reg=(jugadores *)realloc(p->jugador, (n+1)*sizeof(jugadores));
    if(reg==NULL)
    {
        printf("Error: no se pudo asignar memoria.\n");
    } else
    {
       p->jugador=reg;

        //busco el ID mas alto para sumarle 1 (y asi no se repiten)
       for(i=0; i<n; i++)
       {
           if(p->jugador[i].id_jugador>max_id){
            max_id=p->jugador[i].id_jugador;
           }
       }

           p->jugador[n].id_jugador = max_id+1;

           printf("Introduce tu nombre:");
           fgets(p->jugador[n].nomb_jugador, sizeof(p->jugador[n].nomb_jugador),stdin);
           p->jugador[n].nomb_jugador[strcspn(p->jugador[n].nomb_jugador, "\n")] = '\0';

           printf("\nIntroduce tu nombre de usuario (10 caracteres max): ");
           fgets(p->jugador[n].jugador, sizeof(p->jugador[n].jugador),stdin);
           p->jugador[n].jugador[strcspn(p->jugador[n].jugador, "\n")] = '\0';


           printf("\nIntroduce una contrasena (8 caracteres max):");
           fgets(p->jugador[n].contrasena, sizeof(p->jugador[n].contrasena),stdin);
           p->jugador[n].contrasena[strcspn(p->jugador[n].contrasena, "\n")] = '\0';

           //inventario vacio
           p->jugador[n].num_inventario=0;
           p->jugador[n].id_obj = NULL;

           f=fopen("data/jugadores.txt","a");

           if(f==NULL)
           {
               printf("Error al abrir el fichero.\n");
           } else
           {
               fflush(stdin);
               fprintf(f, "%02d-%s-%s-%s-\n",
                        p->jugador[n].id_jugador,
                        p->jugador[n].nomb_jugador,
                        p->jugador[n].jugador,
                        p->jugador[n].contrasena);

               fclose(f);



               printf("Jugador registrado con exito.\n");
           }

           //actualizo las variables
           *u=n;
           (*total_usuarios)++;
       }
    }


