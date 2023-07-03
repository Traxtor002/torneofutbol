#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingreso.h"
#include "resultados.h"
void mostrarResultados() {
    FILE *archivoResultados;
    char linea[MAX_LINEA];
    char nom_equipo1[MAX_NOMBRE_EQUIPO];
    char nom_equipo2[MAX_NOMBRE_EQUIPO];
    int gol_equipo1, gol_equipo2;
    int puntosEquipo1, puntosEquipo2;

    archivoResultados = fopen(ARCHIVO_RESULTADOS, "r");
    if (archivoResultados == NULL) {
        printf("Error al abrir el archivo de resultados.\n");
        return;
    }

    printf("PARTIDO ----- GOLES ------ PUNTOS\n");

    while (fgets(linea, MAX_LINEA, archivoResultados) != NULL) {
        sscanf(
            linea,
            "Partido: %[^( v)] vs. %[^.]. Goles: %d - %d. Puntos: %d - %d.\n",
            nom_equipo1, nom_equipo2,
            &gol_equipo1, &gol_equipo2,
            &puntosEquipo1, &puntosEquipo2
        );

        printf(
            "| %s vs. %s | %d - %d | %d - %d |\n",
            nom_equipo1, nom_equipo2,
            gol_equipo1, gol_equipo2,
            puntosEquipo1, puntosEquipo2
        );
    }

    fclose(archivoResultados);
}

void mostrarTablaDePosiciones() {
    FILE *archivoResultados;
    char linea[MAX_LINEA];
    char nom_equipo1[MAX_NOMBRE_EQUIPO];
    char nom_equipo2[MAX_NOMBRE_EQUIPO];
    int gol_equipo1, gol_equipo2;
    int puntosEquipo1, puntosEquipo2;

    char equipos[MAX_EQUIPOS][MAX_NOMBRE_EQUIPO];
    int numEquipos = obtenerEquipos(equipos);
    int puntos[numEquipos];
    int golesAFavor[numEquipos];
    int golesEnContra[numEquipos];

    for (int i = 0; i < numEquipos; i++) {
        puntos[i] = 0;
        golesAFavor[i] = 0;
        golesEnContra[i] = 0;
    }

    archivoResultados = fopen(ARCHIVO_RESULTADOS, "r");
    if (archivoResultados == NULL) {
        printf("Error al abrir el archivo de resultados.\n");
        return;
    }

    while (fgets(linea, MAX_LINEA, archivoResultados) != NULL) {
        sscanf(
            linea,
            "Partido: %[^( v)] vs. %[^.]. Goles: %d - %d. Puntos: %d - %d.\n",
            nom_equipo1, nom_equipo2,
            &gol_equipo1, &gol_equipo2,
            &puntosEquipo1, &puntosEquipo2
        );

        for (int i = 0; i < numEquipos; i++) {
            if (strcmp(equipos[i], nom_equipo1) == 0) {
                puntos[i] += puntosEquipo1;
                golesAFavor[i] += gol_equipo1;
                golesEnContra[i] += gol_equipo2;
            } else if (strcmp(equipos[i], nom_equipo2) == 0) {
                puntos[i] += puntosEquipo2;
                golesAFavor[i] += gol_equipo2;
                golesEnContra[i] += gol_equipo1;
            }
        }
    }

    fclose(archivoResultados);

    
    for (int i = 0; i < numEquipos - 1; i++) {
        for (int j = i + 1; j < numEquipos; j++) {
            if (puntos[i] < puntos[j]) {
                // cambia los equipos
                char tempNombre[MAX_NOMBRE_EQUIPO];
                strcpy(tempNombre, equipos[i]);
                strcpy(equipos[i], equipos[j]);
                strcpy(equipos[j], tempNombre);

                int tempPuntos = puntos[i];
                puntos[i] = puntos[j];
                puntos[j] = tempPuntos;

                int tempGolesAFavor = golesAFavor[i];
                golesAFavor[i] = golesAFavor[j];
                golesAFavor[j] = tempGolesAFavor;

                int tempGolesEnContra = golesEnContra[i];
                golesEnContra[i] = golesEnContra[j];
                golesEnContra[j] = tempGolesEnContra;
            }
        }
    }

    printf("Tabla de posiciones:\n");
    for (int i = 0; i < numEquipos; i++) {
        printf(
            "%d.\t%s - %d puntos\t(%d Goles a favor, %d Goles en contra)\n",
            i + 1,
            equipos[i],
            puntos[i],
            golesAFavor[i],
            golesEnContra[i]
        );
    }
}