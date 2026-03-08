#include <stdio.h>
#include "main.h"

void mostrar_titulo();

int main(){

    char usuario[15], clave[20];

    mostrar_titulo();

    printf("Inicie sesion o registrese para continuar\n");

    printf("\nUsuario: ");
    //scanf("%s", usuario);

    printf("\nClave: ");
    //scanf("%s", clave);


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
