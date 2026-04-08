#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "ficheros.h"
#include "configuracion.h"

void mostrar_titulo();

int main(){

    char usuario[11], clave[9];         //En el fichero jugadores.txt  usuario = campo "jugador"
    int user=0, password=0;             //Booleanos para el login
    int opcion;
    partida p; //= {0};


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

        getchar();
        registro(&p);
        password=1;
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
void registro(partida *p) //aqui deberias cambiar la estructura y cargar partida no jugadores deberias poner (partida *p)
{
    int i,j;
    int pos=-1;
    int max_id=0;  // esto es para calcular el siguiente id
    partida *reg;
    FILE *f;

    reg=(partida *)malloc(sizeof(partida)); //Angela verifica he puesto malloc pero pusiste realloc

    if(reg==NULL)
    {
        printf("Error: no se pudo asignar memoria.\n");
    } else
    {
       *reg=*p;

       for(i=0; i<20; i++)
       {
           if(reg->jugador[i].id_jugador == 0 && pos == -1)
           {
               pos=i;
           }

           if(reg->jugador[i].id_jugador > max_id)
           {
               max_id = reg->jugador[i].id_jugador;
           }
       }

       if(pos==-1)
       {
           printf("No hay espacio para más jugadores.\n");
       } else
       {
           reg->jugador[pos].id_jugador = max_id+1;

           printf("Introduce tu nombre:");
           fgets(reg->jugador[pos].nomb_jugador, sizeof(reg->jugador[pos].nomb_jugador),stdin);
           reg->jugador[pos].nomb_jugador[strcspn(reg->jugador[pos].nomb_jugador, "\n")] = '\0';

           printf("\nIntroduce tu nombre de usuario (10 caracteres max): ");
           fgets(reg->jugador[pos].jugador, sizeof(reg->jugador[pos].jugador),stdin);
           reg->jugador[pos].jugador[strcspn(reg->jugador[pos].jugador, "\n")] = '\0';


           printf("\nIntroduce una contraseña (8 caracteres max):");
           fgets(reg->jugador[pos].contrasena, sizeof(reg->jugador[pos].contrasena),stdin);
           reg->jugador[pos].contrasena[strcspn(reg->jugador[pos].contrasena, "\n")] = '\0';

           //inventario vacio habria que hacer creo una funcion para añadir los objetos -> ya esta hecha -> vale angelita :)
           reg->jugador[pos].num_inventario=0;
           reg->jugador[pos].id_obj = NULL;

           f=fopen("data/jugadores.txt","a");

           if(f==NULL)
           {
               printf("Error al abrir el fichero.\n");
           } else
           {
               fflush(stdin);
               fprintf(f, "%02d-%s-%s-%s-\n",
                        reg->jugador[pos].id_jugador,
                        reg->jugador[pos].nomb_jugador,
                        reg->jugador[pos].jugador,
                        reg->jugador[pos].contrasena);

               fclose(f);

               *p=*reg;

               printf("Jugador registrado con exito.\n");
           }
       }
    }
    free(reg);
}
