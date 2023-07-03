#ifndef TORNEO_H
#define TORNEO_H
#include "ingreso.h"

int calcularPuntos(int golesEquipo1, int golesEquipo2);
bool elEquipoHaJugado(int indices[], int numIndices, int indice);
void ingresarResultados();
int generarGolesAleatoriamente(int n);
void generarResultadosAutomaticamente();
void mostrarEquiposExcepto(char equipos[][MAX_NOMBRE_EQUIPO], int numEquipos, int indices[], int numIndices);

#endif /* TORNEO_H */