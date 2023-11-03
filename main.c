#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "Usuarios.h"
#include "calendario.h"


#define archivoIngreso "\archivos\ingresos.bin"

#define archivoPacientes "\archivos\pacientes.bin"

#define archivoUsuarios "\archivos\usuarios.bin"



/// PROTOTIPADO ///

void muestraUnPaciente(Paciente elPaciente);
void cargarIngresoArchivo(IngresoLab unIngreso);  /// Carga un ingreso en un archivo de Ingresos;
void muestraIngreso(IngresoLab unIngreso); /// Muestra un ingreso
void muestraUnaPractica(int numero, char practica[]);  /// Muestra una Practica
void agregarPaciente(int dni); /// Agrega Pacientes al archivo de pacientes
int cuentaRegistros(); /// Cuenta la cantidad de registros en el archivo

int main()
{
    int dia, mes, anio;
    obtenerFechaHoraActual(&dia,&mes,&anio);
    printf("\t\t\t Bienvenidos a SysLab \n\n\n");

   // crearAdmin();
    login();
    //muestraArchivoPacientes();
    //muestraPracticas();

    //mostrarArchivoIngresos();



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
    FILE* bufferAdmin=fopen("usuarios.bin","ab");

    if(bufferAdmin)
    {
        fwrite(&Admin1,sizeof(Empleado),1,bufferAdmin);
        fwrite(&Admin2,sizeof(Empleado),1,bufferAdmin);
        fwrite(&Admin3,sizeof(Empleado),1,bufferAdmin);
        fclose(bufferAdmin);
    }
    else
    {
        printf("No se ha podido crear el archivo\n");
    }

}


Empleado crearUsuario() /// Crea un Usuario
{
    Empleado unEmpleado;
    printf("Por favor ingrese el nombre y apellido del Usuario \n");
    fflush(stdin);
    gets(unEmpleado.apellidoYnombre);
    printf("Por favor ingrese el DNI del empleado \n");
    fflush(stdin);
    scanf("%d",&unEmpleado.DNI);
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
    /*
    printf("Por favor ingrese la fecha de ingreso \n");
    fflush(stdin);
    gets(unIngreso.fechaIngreso);
    */
    obtenerFechaHoraActual(&unIngreso.fechaIngreso[0],&unIngreso.fechaIngreso[1],&unIngreso.fechaIngreso[2]);
    printf("Fecha de Ingreso %d %d %d",unIngreso.fechaIngreso[0],unIngreso.fechaIngreso[1],unIngreso.fechaIngreso[2]);
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
    //gets(unIngreso.fechaRetiro);
    ingresarFechaRetiroEstudio(&unIngreso.fechaRetiro[0],&unIngreso.fechaRetiro[1],&unIngreso.fechaRetiro[2]);

    unIngreso.nroIngreso=cuentaRegistros()+1;
    muestraIngreso(unIngreso);
    cargarIngresoArchivo(unIngreso);

    return unIngreso;

}

int cuentaRegistros() /// Cuenta la cantidad de registros en el archivo
{
    int cantRegistros=0;
    FILE* archivo=fopen("ingresos.bin","rb");
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
    scanf("%d",&nuevoPaciente.edad);

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

    FILE *archi=fopen("archivoPacientes.bin","r+b");
    Paciente aux, aux1;

    int flag=0;
    if(archi)
    {
        while(fread(&aux,sizeof(Paciente),1,archi)>0&& flag==0)
        {
            if(aux.DNI==dni)
            {
                flag=1;
            }
        }
        if(flag==0)
        {
            fseek(archi,0,SEEK_END);
            aux1=cargarPaciente(dni);
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
    printf("Fecha de Ingreso: %d/%d/%d \n",unIngreso.fechaIngreso[0],unIngreso.fechaIngreso[1],unIngreso.fechaIngreso[2]);
    printf("Num Ingreso: %d \n",unIngreso.nroIngreso);
    printf("Fecha de Egreso: %d/%d/%d \n",unIngreso.fechaRetiro[0],unIngreso.fechaRetiro[1],unIngreso.fechaRetiro[2]);

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

void cargaEmpleadoArchivo()
{
    FILE* elbuffer=fopen("usuarios.bin","ab");
    Empleado aux;
    aux=crearUsuario();
    if(elbuffer)
    {
        fwrite(&aux,sizeof(Empleado),1,elbuffer);
        fclose(elbuffer);
    }
    else
    {
        printf("No se pudo abrir el archivo \n");
    }
}


void muestraArchivoPacientes()
{
    FILE* elbuffer=fopen("archivoPacientes.bin","rb");
    Paciente aux;
    if(elbuffer)
    {
        while(fread(&aux,sizeof(Paciente),1,elbuffer)>0)
        {
            muestraUnPaciente(aux);
        }
        fclose(elbuffer);
    }
    else
    {
        printf("No se puede abrir el archivo \n");
    }
}

void muestraUnPaciente(Paciente elPaciente)
{
    printf("//////////////////////////////////////////////////\n");
    printf("Apellido y Nombre: %s\n",elPaciente.apellidoYnombre);
    printf("Direccion: %s\n",elPaciente.direccion);
    printf("DNI: %d \n",elPaciente.DNI);
    printf("Edad: %d \n",elPaciente.edad);
    printf("Num de Telefono: %s \n",elPaciente.Telefono);
    printf("//////////////////////////////////////////////////\n\n");
}
