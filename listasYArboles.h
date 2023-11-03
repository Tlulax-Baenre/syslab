#ifndef LISTASYARBOLES_H_INCLUDED
#define LISTASYARBOLES_H_INCLUDED
#include "Usuarios.h"

typedef struct Nodo {
    IngresoLab ingresoLab;
    struct Nodo *siguiente;
} Nodo;

// Definici�n de la estructura para el arreglo de listas
typedef struct {
    Nodo *cabeza;  // Puntero al primer nodo de la lista
} ArregloListas;


typedef struct NodoArbol {
    Paciente paciente;
    struct NodoArbol *izquierdo;
    struct NodoArbol *derecho;
} NodoArbol;

// Definici�n de la estructura para el �rbol binario
typedef struct {
    NodoArbol *raiz;
} ArbolBinario;

NodoArbol* crearNodo(Paciente unPaciente);
NodoArbol* inicializarArbol() ;

#endif // LISTASYARBOLES_H_INCLUDED
