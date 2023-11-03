#include "listasYArboles.h"
#include <stdlib.h>
#include <stdio.h>


/// Inicializa una lista en el arreglo de listas
void inicializarLista(ArregloListas* arregloListas, int nroIngreso) {
    // Aquí puedes inicializar la lista correspondiente al nroIngreso
    // Esto podría incluir asignar memoria para el primer nodo y configurar el puntero cabeza.
}

/// Agrega un nuevo elemento (IngresoLab) a la lista correspondiente
void agregarElemento(ArregloListas* arregloListas, int nroIngreso, IngresoLab nuevoIngreso) {
    // Aquí debes buscar la lista correspondiente a nroIngreso y agregar el nuevoIngreso a esa lista.
}

/// Busca un elemento en la lista correspondiente
IngresoLab* buscarElemento(ArregloListas* arregloListas, int nroIngreso, int DNI) {
    /// Busca el elemento con DNI en la lista correspondiente a nroIngreso y retorna un puntero a ese elemento.
    /// Si no se encuentra, retorna NULL.
}

/// Elimina un elemento de la lista correspondiente
void eliminarElemento(ArregloListas* arregloListas, int nroIngreso, int DNI) {
    // Busca y elimina el elemento con DNI en la lista correspondiente a nroIngreso.
}

void muestraIngresosRecursivos(Nodo* lista)
{
    if(lista==NULL)
    {
        return;
    }
    else
    {
        muestraIngreso(lista->ingresoLab);
        muestraIngresosRecursivos(lista->siguiente);
    }
}


// Inicializa el árbol
NodoArbol* inicializarArbol() {
    return  NULL;
}

// Inserta un paciente en el árbol según su DNI
void insertarPaciente(ArbolBinario *arbolBinario, Paciente nuevoPaciente) {
    // Aquí debes implementar la inserción del paciente en el árbol según su DNI.

}

// Busca un paciente en el árbol según su DNI
Paciente* buscarPaciente(ArbolBinario *arbolBinario, int DNI) {
    // Busca al paciente con el DNI dado en el árbol y retorna un puntero a ese paciente.
    // Si no se encuentra, retorna NULL.
}

// Elimina un paciente del árbol según su DNI
void eliminarPaciente(ArbolBinario *arbolBinario, int DNI) {
    // Busca y elimina al paciente con el DNI dado del árbol.
}

NodoArbol* crearNodo(Paciente unPaciente) /// Crea un nodo listo para insertar en el arbol
{
    NodoArbol* nuevoNodo=(NodoArbol*)malloc(sizeof(NodoArbol));
    nuevoNodo->paciente=unPaciente;
    nuevoNodo->derecho=NULL;
    nuevoNodo->izquierdo=NULL;
    return nuevoNodo;
}

NodoArbol* insertarEnArbol(NodoArbol* elArbol, Paciente elPaciente) ///Inserta en el Arbol
{
    if(elArbol==NULL)
    {
        return crearNodo(elPaciente);
    }
    else
    {
        if((elPaciente.DNI)<(elArbol->paciente.DNI))
        {
            elArbol->izquierdo=insertarEnArbol(elArbol->izquierdo,elPaciente);
        }
        else
        {
            elArbol->derecho=insertarEnArbol(elArbol->derecho,elPaciente);
        }
    }
    return elArbol;
}

Paciente buscaPacienteArbol(NodoArbol* elArbol, int DNI, int* encontradoOno) /// Pendiente de Desarrollo
{
    if(elArbol==NULL)
    {
        (*encontradoOno)=0;
        return;
    }
    else
    {
        if(elArbol->paciente.DNI==DNI)
        {
            (*encontradoOno)=1;
            return elArbol->paciente;
        }/*
        if(buscaPacienteArbol(elArbol->izquierdo,DNI,&encontradoOno) || buscaPacienteArbol(elArbol->derecho,DNI,&encontradoOno))
        {
            return elArbol->paciente;
        }
        */
    }

}


NodoArbol* cargarArbol(NodoArbol* elArbol)
{
    FILE* elBuffer=fopen("archivoPacientes.bin","rb");
    Paciente unPaciente;

    if(elBuffer)
    {
        while(fread(&unPaciente,sizeof(Paciente),1,elBuffer)>0)
        {
            elArbol=insertarEnArbol(elArbol,unPaciente);
        }
        fclose(elBuffer);
    }
    else
    {
        printf("No se puede leer el archivo \n");
    }
    return elArbol;
}

void mostrarPacientesRecursivos(NodoArbol* elArbol) /// Muestra el arbol de pacientes en InORder
{
    printf("Entra \n");
    if(elArbol)
    {
        mostrarPacientesRecursivos(elArbol->izquierdo);
        muestraUnPaciente(elArbol->paciente);

        mostrarPacientesRecursivos(elArbol->derecho);
    }

}
