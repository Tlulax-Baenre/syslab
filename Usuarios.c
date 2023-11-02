#include "Usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

void login()
{
    Empleado aux;
    Empleado elEmpleado;
    char letra;

    int j=0;
    int logeadoOno=0;
    printf("\t\t\t Login: ");
    fflush(stdin);
    gets(aux.usuario);
    printf("\n \t\t\t Password: ");
    fflush(stdin);
    while(letra = getch())
    {
        if(letra==13)
        {
            aux.contrasenia[j]='\0';
            printf("\n");
            break;
        }
        else if(letra==8)
        {
            if(j>0)
            {
                j--;
                printf("\b \b");
            }
        }
        else
        {
            if(j<10)
            {
                printf("*");
                aux.contrasenia[j]=letra;
                j++;
            }
        }
    }
    elEmpleado=compruebaEmpleado(aux,&logeadoOno);
    if(logeadoOno==1)
    {
        printf("El usuario es correcto!\n");
        switch(elEmpleado.permisos)
        {
        case 0:
            MenuAdmin(elEmpleado);
            break;
        case 1:
            MenuEmpleado(elEmpleado);
            break;
        }
    }

    else
    {
        printf("Usuario o Contrasenia Incorrecto\n");
    }
}

Empleado compruebaEmpleado(Empleado unEmpleado, int* logeado)
{
    Empleado buscaEmpleado;

    FILE* Buffer = fopen ("usuarios.bin","rb");

    if (Buffer)
    {
        while(fread(&buscaEmpleado,sizeof(Empleado),1,Buffer)>0)
        {

            if(strcmp(unEmpleado.usuario,buscaEmpleado.usuario)==0 && strcmp(unEmpleado.contrasenia,buscaEmpleado.contrasenia)==0)
            {
                (*logeado)=1;
                fclose(Buffer);
                return buscaEmpleado;

            }
            else
            {
                (*logeado)=0;
            }
        }
        fclose (Buffer);
    }
    else
    {
        printf("El archivo no pudo abrirse/n");
    }

}

void MenuEmpleado(Empleado elEmpleado)
{

    int opcion;
    char continuar='s';

    do
    {
        printf("Bienvenido a Syslab, %s",elEmpleado.apellidoYnombre);
        printf("Por Favor ingrese la opcion deseada \n\n");
        printf("1)Crear un Ingreso\n");

        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            crearIngreso();
            break;
        case 2:
            printf("En construccion! =) \n");
            break;
        case 3:
            printf("En construccion! =) \n");
            break;
        case 4:
            printf("En construccion! =) \n");
            break;
        case 5:
            printf("En construccion! =) \n");
            break;
        }
        printf("Desea realizar otra operacion? \n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    while(continuar=='s');

}

void MenuAdmin(Empleado elAdmin)
{
    system("cls");
    int opcion;
    char continuar='s';

    do
    {
        printf("\t\tBienvenido a Syslab, Admin %s\n\n",elAdmin.apellidoYnombre);
        printf("Por Favor ingrese la opcion deseada \n\n");
        printf("1)Gestion de Usuarios\n2)Listado de Pacientes\n3)Listado de Ingresos segun Criterio\n");

        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            gestionDeUsuarios(elAdmin);
            break;
        case 2:
            printf("En construccion! =) \n");
            break;
        case 3:
            printf("En construccion! =) \n");
            break;
        case 4:
            printf("En construccion! =) \n");
            break;
        case 5:
            printf("En construccion! =) \n");
            break;
        }
        printf("Desea realizar otra operacion? \n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    while(continuar=='s');


}

void gestionDeUsuarios(Empleado elAdmin)
{
    int opcion;
        printf("\t\tBienvenido a Syslab, Admin %s\n\n",elAdmin.apellidoYnombre);
        printf("Por Favor ingrese la opcion deseada \n\n");
        printf("1)Crear Usuario\n2)Modificar Usuario\n3)Listado de Usuarios\n");

        fflush(stdin);
        scanf("%d",&opcion);
    switch(opcion)
    {
    case 1:
        cargaEmpleadoArchivo();
        break;
    case 2:
        printf("En construccion! =) \n");
        break;
    case 3:
        printf("En construccion! =) \n");
        break;
    case 4:
        printf("En construccion! =) \n");
        break;
    case 5:
        printf("En construccion! =) \n");
        break;
    }
}
