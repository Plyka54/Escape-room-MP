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
