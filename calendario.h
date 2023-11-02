#ifndef CALENDARIO_H_INCLUDED
#define CALENDARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 6
#define COLUMNAS 7

///***********************************************///

void ingresarFechaRetiroEstudio(int* diaRetiro, int* mesRetiro, int* anioRetiro);
void imprimirCalendario(int mes, int anio);
int obtenerDiaSemana(int dia, int mes, int anio);
int obtenerDiasMes(int mes, int anio);
void obtenerFechaHoraActual(int *dia, int *mes, int *anio);

///***********************************************///

#endif // CALENDARIO_H_INCLUDED
