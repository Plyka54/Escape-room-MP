#include <stdio.h>
#include <windows.h>
#include "puzles.h"

void puzle_morse(partida *p){

    char respuesta;


    printf("Me acerque al ordenador, parece que hay algo en la pantalla.\n");
    printf("Hay un audio en el centro, quieres reproducirlo? (s/n)\n");

    scanf(" %c", &respuesta);

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

    printf("Eso es todo al parecer... Parece codigo morse.\n");
    printf("Debe de haber algo que me ayude a traducirlo...\n\n\n");

}

void puzle_switch (partida *p){
    printf("Es raro que haya cables conectados a este switch lleno de polvo...\n");
    printf("Hay un cable azul conectado al puerto 1, un cable amarillo conectado al puerto 2, un cable verde conectado al puerto 5 y un cable rojo conectado al puerto 2\n");
    printf("Esto es muy raro...\n\n\n");
    //8152
}

void puzle_despacho(partida *p){
    printf("Parece que hay un panel de acceso para entrar al despacho de mi profesor...\n");
    printf("Me pregunto cual sera el pin, alomejor ahi dentro hay una forma de salir...\n");
    printf("Es raro que arriba del panel de acceso hay como unos circulos de colores,\nel primero es rojo, el segundo azul, el tercero verde y el ultimo amarillo\n\n\n");
}
