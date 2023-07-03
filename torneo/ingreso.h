#ifndef INGRESO_H
#define INGRESO_H

#define ARCHIVO_EQUIPOS "equipos.txt"
#define ARCHIVO_RESULTADOS "resultados.txt"
#define LIMPIAR_CONSOLA "clear"
#define MAX_EQUIPOS 100
#define MAX_GOLES 8
#define MAX_LINEA 255
#define MAX_NOMBRE_EQUIPO 50

void ingresarEquipos();
int ingresarNumero();
void mostrarEquipos();
int obtenerEquipos(char equipos[][MAX_NOMBRE_EQUIPO]);
int obtenerNumeroEquipos();
void pausarFlujoDelPrograma();

#endif /* INGRESO_H */