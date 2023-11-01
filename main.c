#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define archivoIngreso "\archivos\ingresos.bin"

#define archivoPacientes "\archivos\pacientes.bin"

#define archivoUsuarios "\archivos\usuarios.bin"

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

/// PROTOTIPADO ///

Empleado crearUsuario();
IngresoLab crearIngreso();
Practica buscaPractica(int numero);

int main()
{
    //crearUsuario();
    //crearIngreso();
    muestraPracticas();
    //Practica esaPractica;
    //esaPractica=buscaPractica(143);
    //crearIngreso();
    //mostrarArchivoIngresos();
    //muestraPracticas();
    //muestraUnaPractica(esaPractica.nroPractica,esaPractica.nombrePractica);

    return 0;
}


void crearAdmin() ///Crea a los admin
{
    Empleado Admin1,Admin2,Admin3;

    strcpy(Admin1.apellidoYnombre,"Luis Echeverria");
    strcpy(Admin1.usuario,"EchevLu");
    strcpy(Admin1.contrasenia,"147258");
    Admin1.DNI=34472931;
    Admin1.permisos=0;

    strcpy(Admin2.apellidoYnombre,"Gian Vietta");
    strcpy(Admin2.usuario,"GianV");
    strcpy(Admin2.contrasenia,"123456");
    Admin2.DNI=46420089;
    Admin2.permisos=0;

    strcpy(Admin3.apellidoYnombre,"Lautaro Chillemi");
    strcpy(Admin3.usuario,"Lauti");
    strcpy(Admin3.contrasenia,"lauti17");
    Admin3.DNI=46012767;
    Admin3.permisos=0;
}


Empleado crearUsuario() /// Crea un Usuario
{
    Empleado unEmpleado;
    printf("Por favor ingrese el nombre y apellido del Usuario \n");
    fflush(stdin);
    gets(unEmpleado.apellidoYnombre);
    printf("Por favor ingrese el DNI del empleado \n");
    fflush(stdin);
    gets(unEmpleado.DNI);
    printf("Por favor ingrese el password del usuario \n");
    fflush(stdin);
    gets(unEmpleado.contrasenia);
    printf("Por favor ingrese el nombre de Usuario \n");
    fflush(stdin);
    gets(unEmpleado.usuario);
    unEmpleado.permisos=1;
    return unEmpleado;
}

IngresoLab crearIngreso() ///Crea un ingreso
{
    IngresoLab unIngreso;
    Practica pracAux;
    int numPractica;
    char seguir='s';
    int i=0;

    printf("Por favor ingrese el DNI del paciente \n");
    fflush(stdin);
    scanf("%d",&unIngreso.DNI);
    agregarPaciente(unIngreso.DNI);

    printf("Por favor ingrese la matricula del profesional solicitante \n ");
    fflush(stdin);
    scanf("%d",&unIngreso.Matricula);

    printf("Por favor ingrese la fecha de ingreso \n");
    fflush(stdin);
    gets(unIngreso.fechaIngreso);

    while(seguir=='s' && i<20)
    {
        printf("Por favor ingrese el ID de la practica \n");
        fflush(stdin);
        scanf("%d",&numPractica);
        printf("el num de practica es: %d \n",numPractica);

        pracAux=buscaPractica(numPractica);
        muestraUnaPractica(pracAux.nroPractica,pracAux.nombrePractica);
        unIngreso.practica[i]=pracAux;
        i++;

        printf("Desea cargar otra practica?s/n \n");
        fflush(stdin);
        scanf("%c",&seguir);
    }
    unIngreso.cantPracticas=i;
    printf("Ingrese la fecha estimada de retiro \n");
    fflush(stdin);
    gets(unIngreso.fechaRetiro);

    unIngreso.nroIngreso=cuentaRegistros()+1;

    muestraIngreso(unIngreso);
    cargarIngresoArchivo(unIngreso);

    return unIngreso;

}

int cuentaRegistros() /// Cuenta la cantidad de registros en el archivo
{
    int cantRegistros=0;
    FILE* archivo=fopen(archivoIngreso,"rb");
    if(archivo)
    {
        fseek(archivo,0,SEEK_END);
        cantRegistros=ftell(archivo)/sizeof(IngresoLab);
        fclose(archivo);
    }
    return cantRegistros;
}

Paciente cargarPaciente(int dni) /// Carga Pacientes
{
    Paciente nuevoPaciente;
    nuevoPaciente.DNI=dni;
    printf("El DNI ingresado no se encuentra asociado a ningun paciente cargado con anterioridad porfavor carge los datos del nuevo paciente.\n\n");
    printf("Ingrese el apellido y nombre del paciente: ");
    fflush(stdin);
    gets(nuevoPaciente.apellidoYnombre);
    printf("ingrese la edad del paciente: ");
    fflush(stdin);
    scanf("%i",&nuevoPaciente.edad);
    printf("Ingrese la direccion del paciente: ");
    fflush(stdin);
    gets(nuevoPaciente.direccion);
    printf("Ingrese un numero telefonico: ");
    fflush(stdin);
    gets(nuevoPaciente.Telefono);
    return nuevoPaciente;
}

void agregarPaciente(int dni) /// Agrega Pacientes al archivo de pacientes
{
    FILE *archi=fopen(archivoPacientes,"r+b");
    Paciente aux, aux1;
    if(archi)
    {
        while(!feof(archi)&&dni!=aux.DNI)
        {
            fread(&aux,sizeof(Paciente),1,archi);
        }
        if(feof(archi))
        {
            fseek(archi,0,SEEK_END);
//            aux1=cargarPaciente();
            fwrite(&aux1,sizeof(Paciente),1,archi);
        }
        fclose(archi);
    }
}

void muestraPracticas() /// Muestra el listado de practicas
{
 FILE* elbuffer=fopen("lasPracticas.bin","rb");
 Practica unaPractica;
 if(elbuffer)
 {
     while(fread(&unaPractica,sizeof(Practica),1,elbuffer)>0)
     {
         printf("Numero de Practica:%d: \nNombre de practica %s\n\n",unaPractica.nroPractica,unaPractica.nombrePractica);
     }
     fclose(elbuffer);
 }
 else
 {
     printf("No se pudo abrir el archivo \n");
 }
}

Practica buscaPractica(int numero) /// Busca una practica por Numero de Practica
{
 FILE* elbuffer= fopen("lasPracticas.bin","rb");
 Practica unaPractica;
 if(elbuffer)
 {
     while(fread(&unaPractica,sizeof(Practica),1,elbuffer)>0) /// Ver que hacer cuando no encuentre el numero de practica
     {
        if(unaPractica.nroPractica==numero)
        {

            fclose(elbuffer);
            return unaPractica;
        }
     }

     fclose(elbuffer);
 }
 else
 {
     printf("No se pudo abrir el archivo \n");
 }
}

void muestraUnaPractica(int numero, char practica[])  /// Muestra una Practica
{
    printf("Numero de Practica:%d: \nNombre de practica %s\n\n",numero,practica);
}

void muestraIngreso(IngresoLab unIngreso) /// Muestra un ingreso
{
    printf("DNI: %d \n",unIngreso.DNI);
    printf("Matricula del Profesional: %d \n",unIngreso.Matricula);
    printf("Fecha de Ingreso: %s \n",unIngreso.fechaIngreso);
    printf("Num Ingreso: %d \n",unIngreso.nroIngreso);
    for(int i=0;i<unIngreso.cantPracticas;i++)
    {
        muestraUnaPractica(unIngreso.practica[i].nroPractica, unIngreso.practica[i].nombrePractica);
    }

}
void cargarIngresoArchivo(IngresoLab unIngreso)  /// Carga un ingreso en un archivo de Ingresos
{
    FILE* buffer =fopen("ingresos.bin","ab");

    if(buffer)
    {
        fwrite(&unIngreso,sizeof(IngresoLab),1,buffer);
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }
}

void mostrarArchivoIngresos()  /// Carga un ingreso en un archivo de Ingresos
{
    FILE* buffer =fopen("ingresos.bin","rb");
    IngresoLab elIngreso;
    if(buffer)
    {
        while(fread(&elIngreso,sizeof(IngresoLab),1,buffer)>0)
        {
            muestraIngreso(elIngreso);
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }
}
