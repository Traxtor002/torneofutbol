#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ingreso.h"
#include "torneo.h"
#include "resultados.h"

//David Cabrera, Michael Tipantuña, Johan Meza

void mostrarMenu() {
    printf("------ Menú ------\n");
    printf("1. Ingresar equipos\n");
    printf("2. Visualizar equipos\n");
    printf("3. Crear Resultados\n");
    printf("4. Ingresar resultados\n");
    printf("5. Tabla de posiciones\n");
    printf("6. Resultados de los partidos\n");
    printf("7. Cerrar\n");
    printf("------------------\n");
}

int main() {
    int opcion, num_equipos;

    do {
        num_equipos = obtenerNumeroEquipos();

        mostrarMenu();

        printf("Elige una Opcion: ");
        opcion = ingresarNumero();

        switch(opcion) {
            case 1:
                system(LIMPIAR_CONSOLA);
                ingresarEquipos();
                break;
            case 2:
                system(LIMPIAR_CONSOLA);
                mostrarEquipos();
                pausarFlujoDelPrograma();
                break;
            case 3:
                system(LIMPIAR_CONSOLA);
                if(num_equipos == 0) {
                    printf("Ingrese los Equipos.\n");
                    pausarFlujoDelPrograma();
                    break;
                }
                srand(time(NULL));
                generarResultadosAutomaticamente();
                pausarFlujoDelPrograma();
                break;
            case 4:
                system(LIMPIAR_CONSOLA);
                if(num_equipos == 0) {
                    printf("Ingrese los Equipos.\n");
                    pausarFlujoDelPrograma();
                    break;
                }
                ingresarResultados();
                pausarFlujoDelPrograma();
                break;
            case 5:
                system(LIMPIAR_CONSOLA);
                if(num_equipos == 0) {
                    printf("Ingrese los Equipos.\n");
                    pausarFlujoDelPrograma();
                    break;
                }
                mostrarTablaDePosiciones();
                pausarFlujoDelPrograma();
                break;
            case 6:
                system(LIMPIAR_CONSOLA);
                if(num_equipos == 0) {
                    printf("Ingrese los Equipos.\n");
                    pausarFlujoDelPrograma();
                    break;
                }
                mostrarResultados();
                pausarFlujoDelPrograma();
                break;
            case 7:
                system(LIMPIAR_CONSOLA);
                printf("¡Adios!\n");
                pausarFlujoDelPrograma();
                exit(0);
            default:
                system(LIMPIAR_CONSOLA);
                printf("Opción inválida, ingrese una opción válida.\n");
                pausarFlujoDelPrograma();
        }
    } while(opcion != 7);

    return 0;
}