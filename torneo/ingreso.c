#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ingreso.h"

int ingresarNumero() {
    char input[100];
    int num = -1;

    fgets(input, 100, stdin);
    if(sscanf(input, "%d\n", &num) != 1) {
        printf("Error: Ingresa un número válido.\n");
        getchar();
        system(LIMPIAR_CONSOLA);
        return num;
    }

    return num;
}

void pausarFlujoDelPrograma() {
    printf("Pulsa ENTER para continuar...");
    getchar();
    system(LIMPIAR_CONSOLA);
}

void ingresarEquipos() {
    char equipos[MAX_EQUIPOS][MAX_NOMBRE_EQUIPO];
    char nombreEquipo[MAX_NOMBRE_EQUIPO];
    FILE *archivoEquipos;
    int num_equipos = obtenerNumeroEquipos();

    archivoEquipos = fopen(ARCHIVO_EQUIPOS, "a");

    if (archivoEquipos == NULL) {
        printf("Error al abrir el archivo de equipos.\n");
        pausarFlujoDelPrograma();
        return;
    }

    printf("Ingrese los nombres de los equipos (escriba 'finalizar' para finalizar):\n");

    do {
        printf("Equipo %d: ", num_equipos + 1);
        scanf(" %[^\n]s", nombreEquipo);

        if (strcmp(nombreEquipo, "finalizar") == 0) {
            break;
        }

        strcpy(equipos[num_equipos], nombreEquipo);
        fprintf(archivoEquipos, "%s\n", equipos[num_equipos]);
        num_equipos++;
    } while (strcmp(nombreEquipo, "finalizar") != 0);

    fclose(archivoEquipos);

    printf("Se han ingresado %d equipos.\n", num_equipos);
    printf("Pulsa ENTER para continuar...");
    getchar(); getchar();
    system(LIMPIAR_CONSOLA);
}

void mostrarEquipos() {
    char equipos[MAX_EQUIPOS][MAX_NOMBRE_EQUIPO];
    int num_equipos = obtenerEquipos(equipos);

    if (num_equipos == 0) {
        printf("No se ha ingresado ningún equipo aún.\n");
    } else {
        printf("Equipos ingresados:\n");
        for (int i = 0; i < num_equipos; i++) {
            printf("%d. %s\n", i + 1, equipos[i]);
        }
    }
}

int obtenerEquipos(char equipos[][MAX_NOMBRE_EQUIPO]) {
    FILE *archivoEquipos;
    char nom_equipo[MAX_NOMBRE_EQUIPO];
    int num_equipo = 0;

    archivoEquipos = fopen(ARCHIVO_EQUIPOS, "r");
    if(archivoEquipos == NULL) {
        printf("No se encontró el archivo de equipos.\n");
        pausarFlujoDelPrograma();
        return 0;
    }

    while(fgets(nom_equipo, MAX_NOMBRE_EQUIPO, archivoEquipos) != NULL) {
        // Eliminar el salto de línea al final del nombre del equipo
        nom_equipo[strcspn(nom_equipo, "\n")] = '\0';
        strcpy(equipos[num_equipo], nom_equipo);
        num_equipo++;
    }

    fclose(archivoEquipos);
    return num_equipo;
}

int obtenerNumeroEquipos() {
    FILE *archivoEquipos;
    char nom_equipo[MAX_NOMBRE_EQUIPO];
    int num_equipos = 0;

    archivoEquipos = fopen(ARCHIVO_EQUIPOS, "r");
    if(archivoEquipos == NULL) {
        return 0;
    }

    while(fgets(nom_equipo, MAX_NOMBRE_EQUIPO, archivoEquipos) != NULL) {
        num_equipos++;
    }

    fclose(archivoEquipos);
    return num_equipos;
}