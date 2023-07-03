#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "ingreso.h"
#include "torneo.h"

bool elEquipoHaJugado(int indicesEquipos[], int numIndices, int indice) {
    for(int i = 0; i < numIndices; i++) {
        if (indicesEquipos[i] == indice) {
            return true;
        }
    }
    return false;
}

void mostrarEquiposExcepto(char equipos[][MAX_NOMBRE_EQUIPO], int numEquipos, int indices[], int numIndices) {
    int i, j;
    bool mostrar;

    for (i = 0; i < numEquipos; i++) {
        mostrar = true;
        for (j = 0; j < numIndices; j++) {
            if (indices[j] == i) {
                mostrar = false;
                break;
            }
        }
        if(mostrar) {
            printf("%d. %s\n", i + 1, equipos[i]);
        }
    }
}

int calcularPuntos(int golesEquipo1, int golesEquipo2) {
    if(golesEquipo1 == golesEquipo2) {
        return 0;
    } else if(golesEquipo1 > golesEquipo2) {
        return 3;
    } else {
        return 1;
    }
}

void ingresarResultados() {
    FILE *archivoResultados;

    char nombreEquipo1[MAX_NOMBRE_EQUIPO];
    char nombreEquipo2[MAX_NOMBRE_EQUIPO];
    int indiceEquipo2;
    int golesEquipo1, golesEquipo2;
    int puntosEquipo1, puntosEquipo2;

    char equipos[MAX_EQUIPOS][MAX_NOMBRE_EQUIPO];
    int numEquipos = obtenerEquipos(equipos);
    int numPartido = 0, vueltas = numEquipos - 1;
    int partidosJugados[numEquipos];
    int ultimaVuelta = 0;

    archivoResultados = fopen(ARCHIVO_RESULTADOS, "w");
    if(archivoResultados == NULL) {
        printf("Error al abrir el archivo de resultados.\n");
        return;
    }
    
    printf("Ingrese los resultados de los partidos:\n");
    pausarFlujoDelPrograma();

    for (int numEquipo = 0; numEquipo < numEquipos; numEquipo++) {
        for (int equipoQueYaJugo = 0; equipoQueYaJugo < numEquipo; equipoQueYaJugo++) {
            partidosJugados[numPartido++] = equipoQueYaJugo;
        }
        for (int vuelta = numEquipo; vuelta < vueltas; vuelta++) {
            strcpy(nombreEquipo1, equipos[numEquipo]);
            if(ultimaVuelta == numEquipo) {
                partidosJugados[numPartido++] = numEquipo;
                ultimaVuelta++;
            }
            do {
                system(LIMPIAR_CONSOLA);
                printf(
                    "El equipo #%d %s ha jugado con el equipo:\n",
                    numEquipo + 1, nombreEquipo1
                );
                mostrarEquiposExcepto(equipos, numEquipos, partidosJugados, numPartido);
                printf("---------------\n");
                printf("Número del otro equipo: ");
                indiceEquipo2 = ingresarNumero();
            } while (indiceEquipo2 < 1 || indiceEquipo2 > numEquipos || elEquipoHaJugado(partidosJugados, numPartido, indiceEquipo2 - 1));
            strcpy(nombreEquipo2, equipos[indiceEquipo2 - 1]);

            partidosJugados[numPartido++] = (indiceEquipo2 - 1);

            do {
                system(LIMPIAR_CONSOLA);
                printf("Goles Equipo 1: ");
                golesEquipo1 = ingresarNumero();
            } while (golesEquipo1 < 0);

            do {
                system(LIMPIAR_CONSOLA);
                printf("Goles Equipo 2: ");
                golesEquipo2 = ingresarNumero();
            } while (golesEquipo2 < 0);

            puntosEquipo1 = calcularPuntos(golesEquipo1, golesEquipo2);
            puntosEquipo2 = calcularPuntos(golesEquipo2, golesEquipo1);

            fprintf(
                archivoResultados,
                "Partido: %s vs. %s. Goles: %d - %d. Puntos: %d - %d.\n",
                nombreEquipo1, nombreEquipo2,
                golesEquipo1, golesEquipo2,
                puntosEquipo1, puntosEquipo2
            );
            system(LIMPIAR_CONSOLA);
        }
        numPartido = 0; // reiniciar equipos que han jugado despues de cada ronda.
        for (int i = 0; i < numEquipos; i++) {
            partidosJugados[i] = -1;
        }
    }
    
    fclose(archivoResultados);
    printf("Resultados ingresados correctamente.\n");
}

int generarGolesAleatoriamente(int n) {
    int numRandom;
    numRandom = rand() % n;
    return numRandom;
}

void generarResultadosAutomaticamente() {
    FILE *archivoResultados;
    char nombreEquipo1[MAX_NOMBRE_EQUIPO];
    char nombreEquipo2[MAX_NOMBRE_EQUIPO];
    int golesEquipo1, golesEquipo2;
    int puntosEquipo1, puntosEquipo2;

    char equipos[MAX_EQUIPOS][MAX_NOMBRE_EQUIPO];
    int numEquipos = obtenerEquipos(equipos);
    int numPartido = 0, vueltas = numEquipos - 1;
    int ultimaVuelta = 0;
    int partidosJugados[numEquipos];

    archivoResultados = fopen(ARCHIVO_RESULTADOS, "w");
    if(archivoResultados == NULL) {
        printf("Error al abrir el archivo de resultados.\n");
        return;
    }

    for (int numEquipo = 0; numEquipo < numEquipos; numEquipo++) {
        for (int equipoQueYaJugo = 0; equipoQueYaJugo < numEquipo; equipoQueYaJugo++) {
            partidosJugados[numPartido++] = equipoQueYaJugo;
        }
        for (int vuelta = numEquipo; vuelta < vueltas; vuelta++) {
            strcpy(nombreEquipo1, equipos[numEquipo]);
            if(ultimaVuelta == numEquipo) {
                partidosJugados[numPartido++] = numEquipo;
                ultimaVuelta++;
            }

            strcpy(nombreEquipo2, equipos[vuelta + 1]);
            partidosJugados[numPartido++] = (vuelta + 1);

            golesEquipo1 = generarGolesAleatoriamente(MAX_GOLES);
            golesEquipo2 = generarGolesAleatoriamente(MAX_GOLES);
            puntosEquipo1 = calcularPuntos(golesEquipo1, golesEquipo2);
            puntosEquipo2 = calcularPuntos(golesEquipo2, golesEquipo1);

            fprintf(
                archivoResultados,
                "Partido: %s vs. %s. Goles: %d - %d. Puntos: %d - %d.\n",
                nombreEquipo1, nombreEquipo2,
                golesEquipo1, golesEquipo2,
                puntosEquipo1, puntosEquipo2
            );
        }
        numPartido = 0; // Reiniciar el numero de partidos que se jugaron en cada ronda
        for (int i = 0; i < numEquipos; i++) {
            partidosJugados[i] = -1;
        }
    }
    fclose(archivoResultados);
    printf("Resultados generados automáticamente.\n");
}