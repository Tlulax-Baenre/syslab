#include  "calendario.h"

void ingresarFechaRetiroEstudio(int* diaRetiro, int* mesRetiro, int* anioRetiro) {
    int mes, anio, dia_retiro;

    printf("Ingrese el mes de retiro (1-12): ");
    scanf("%d", &mes);

    printf("Ingrese el año de retiro: ");
    scanf("%d", &anio);

    imprimirCalendario(mes, anio);

    printf("Ingrese el día de retiro del estudio: ");
    scanf("%d", &dia_retiro);

    printf("Fecha de retiro del estudio: %d/%d/%d\n", dia_retiro, mes, anio);

    // Asignar la fecha de retiro a través de punteros
    *diaRetiro = dia_retiro;
    *mesRetiro = mes;
    *anioRetiro = anio;


}

void imprimirCalendario(int mes, int anio) {
    int dias_mes = obtenerDiasMes(mes, anio);
    int dia_inicio = obtenerDiaSemana(1, mes, anio);

    printf("    Calendario - %d/%d\n", mes, anio);
    printf("   DOM  LUN  MAR  MIE  JUE  VIE  SAB\n");

    int dia = 1;
    int fila, columna;

    for (fila = 0; fila < FILAS; fila++) {
        for (columna = 0; columna < COLUMNAS; columna++) {
            if ((fila == 0 && columna < dia_inicio) || dia > dias_mes) {
                printf("     ");
            } else {
                printf("%5d", dia++);
            }
        }
        printf("\n");
    }
}

int obtenerDiaSemana(int dia, int mes, int anio) {
    struct tm tiempo = {0};
    tiempo.tm_mday = dia;
    tiempo.tm_mon = mes - 1;
    tiempo.tm_year = anio - 1900;

    time_t t = mktime(&tiempo);

    struct tm *tiempo_descompuesto = localtime(&t);

    return tiempo_descompuesto->tm_wday;
}

int obtenerDiasMes(int mes, int anio) {
    int dias_mes;

    if (mes == 2) {
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
            dias_mes = 29;
        } else {
            dias_mes = 28;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        dias_mes = 30;
    } else {
        dias_mes = 31;
    }

    return dias_mes;
}

void obtenerFechaHoraActual(int *dia, int *mes, int *anio) {
    // Obtener la hora y fecha actual
    time_t tiempo_actual = time(NULL);
    struct tm *info_tiempo = localtime(&tiempo_actual);

    // Extraer el día, mes y año de la estructura tm
    *dia = info_tiempo->tm_mday;
    *mes = info_tiempo->tm_mon + 1;  // tm_mon comienza en 0
    *anio = info_tiempo->tm_year + 1900;  // tm_year es el año actual menos 1900

    // Formatear la hora y fecha actual
    char fecha[20];
    strftime(fecha, sizeof(fecha), "%d/%m/%Y", info_tiempo);

    char hora[10];
    strftime(hora, sizeof(hora), "%H:%M:%S", info_tiempo);

    // Mostrar la hora y fecha actual
    printf("Fecha actual: %s\n", fecha);
    printf("Hora actual: %s\n", hora);
}
