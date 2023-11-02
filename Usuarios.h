#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED\


typedef struct
{
     int nroPractica;
    char nombrePractica[30];
    int eliminado;
} Practica;


typedef struct
{
    int nroIngreso;
    char fechaIngreso[10];
    char fechaRetiro[10];
    int DNI;
    int Matricula;
    int eliminado;
    ///int numPractica[20];   Se borro numero practica y se anido la estructura Practica
    Practica practica[20];   ///Es un arreglo de practicas
    int cantPracticas;///    Se iguala a los validos al momento de la carga de las practicas, asi se saben la cantidad para mostrarlas.
} IngresoLab;


typedef struct
{
    char apellidoYnombre[40];
    int edad;
    int DNI;
    char direccion[30];
    char Telefono[15];
    int eliminado;
} Paciente;

typedef struct
{
    int DNI;
    char apellidoYnombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
    int permisos;
} Empleado;

typedef struct
{
    int nroIngreso;
    int nroPractica;
    char resultado[30];
} resultados;

Empleado crearUsuario();
IngresoLab crearIngreso();
Practica buscaPractica(int numero);
Empleado compruebaEmpleado(Empleado unEmpleado, int* logeado);


#endif // USUARIOS_H_INCLUDED
