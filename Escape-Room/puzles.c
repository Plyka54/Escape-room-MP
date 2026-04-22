#include <stdio.h>
#include <windows.h>
#include "puzles.h"

//Cabecera: void puzle_morse(partida *p)
//Precondicion: Elegir la opcion examinar sala en el aula de practicas B
//Postcondicion: Muestra la descripcion del ordenador por pantalla y, si el usuario acepta, reproduce un audio en codigo morse ('UCA') mediante pitidos del sistema
void puzle_morse(partida *p){

    char respuesta;

    printf("\033[33m");
    printf("Me acerque al ordenador, parece que hay algo en la pantalla.\n");
    printf("\033[0m");
    printf("Hay un audio en el centro, quieres reproducirlo? (s/n)\n");

    scanf(" %c", &respuesta);

    //se reproduce un sonido
    if (respuesta=='s'){


        Beep(750, 300);
        Beep(750, 300);     //U     ..-
        Beep(750, 600);

        system("pause");

        Beep(750, 600);
        Beep(750, 300);
        Beep(750, 600);     //C     -.-.
        Beep(750, 300);

        system("pause");

        Beep(750, 300);
        Beep(750, 600);     //A     .-

    }

    printf("\033[33m");
    printf("Eso es todo al parecer... Parece codigo morse.\n");
    printf("Debe de haber algo que me ayude a traducirlo...\n\n\n");
    printf("\033[0m");

}

//Cabecera: void puzle_switch(partida *p)
//Precondicion:
//Postcondicion: Imprime por pantalla las pistas visuales sobre los cables y los puertos conectados al switch para que el jugador deduzca el codigo (8152).
void puzle_switch (partida *p){

    printf("\033[33m");
    printf("Es raro que haya cables conectados a este switch lleno de polvo...\n");
    printf("Hay un cable azul conectado al puerto 1, un cable rojo conectado al puerto 2, un cable verde conectado al puerto 5 y un cable amarillo conectado al puerto 8\n");
    printf("Esto es muy raro...\n\n\n");
    printf("\033[0m");

    //8152
}

//Cabecera: void puzle_despacho(partida *p)
//Precondicion:
//Postcondicion: Muestra al jugador la pista descriptiva sobre el orden de los circulos de colores en el panel de acceso del despacho.
void puzle_despacho(partida *p){

    printf("\033[33m");
    printf("Parece que hay un panel de acceso para entrar al despacho de mi profesor...\n");
    printf("Me pregunto cual sera el pin, alomejor ahi dentro hay una forma de salir...\n");
    printf("Es raro que arriba del panel de acceso hay como unos circulos de colores,\nel primero es amarillo, el segundo azul, el tercero verde y el ultimo rojo\n\n\n");
    printf("\033[0m");
}

//Cabecera: void puzle_final(partida *p)
//Precondicion:
//Postcondicion: Imprime un texto narrativo seguido de un grafico ASCII que simula una nota de papel con el codigo final (4869) y la advertencia de los intentos.
void puzle_final(partida *p){ //cuando entras a conserjeria 16

    printf("\033[33m");
    printf("Ahora que me fijo... Esta sala tiene muchos documentos, no habra algo que me ayude a salir?\n\n");
    printf("\033[0m");
    printf("Como ultima esperanza, esperas encontrar algo que te ayude a escapar por fin de este sitio.\n");
    printf("Ya empiezas a estar harto de dar vueltas sin saber muy bien que hacer...\n\n");

    printf("...\n\n");
    system("pause");
    printf("\033[33m");
    printf("Que es esto?\n\n");
    printf("\033[0m");
    printf("Despues de estar toqueteando un rato, te encuentras una agenda al fondo de un cajon\n");

    printf("La hojeas un poco por encima hasta que abres una pagina con una doblez en la parte superior\n\n");

    printf("\033[36m"); //celestito
    printf(
        "  _______________________________\n"
        "/_______________________________/|\n"
        "|                              | |\n"
        "|  Hey Lucia, no deberias      | |\n"
        "|  volver a olvidar el codigo  | |\n"
        "|  de la puerta. Ya sabes      | |\n"
        "|  como se pone el guarda de   | |\n"
        "|  seguridad cada vez que      | |\n"
        "|  suena la alarma por fallar  | |\n"
        "|  el codigo 3 veces.          | |\n"
        "|                              | |\n"
        "|            4869              | |\n"
        "|                              | |\n"
        "|  No lo olvides, no quiero    | |\n"
        "|  que nos bajen el sueldo.    | /\n"
        "|______________________________|/\n");

        printf("\033[0m");

}

//Cabecera: void llave_biblioteca()
//Precondicion:
//Postcondicion: Imprime la descripcion narrativa de los objetos encontrados en el despacho (libro de algoritmos y tarjeta) para dar contexto de la historia.
void llave_biblioteca(){
    printf("\033[33m");
    printf("\nWow, jamas he estado en el despacho de un profesor, hay bastantes documentos y cosas...\n");
    printf("Mira este es el libro de verificacion de algoritmo del que Esther siempre habla.\n");
    printf("En la portada hay un post-it que pone 'Porfavor devuelvelo a la Biblioteca' \n");
    printf("Y al lado esta la tarjeta de Esther que abre las salas a las que solo pueden entrar los profes\n");
    printf("Me pregunto si me servira de algo...\n");
    printf("\033[0m");
}







