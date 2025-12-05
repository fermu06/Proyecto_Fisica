#include "pfisica.h"
#include <stdio.h>

int main() {

    Punto p;
    float m, b;
    int op;
    char ux[20], uy[20], vx[20], vy[20];

    printf("============================================================\n");
    printf("                 CALCULADORA DE MODELO MATEMATICO           \n");
    printf("============================================================\n");
    printf("\nDESCRIPCION:\n");
    printf("Este programa calcula el modelo matematico lineal basado en\n");
    printf("un conjunto de datos experimentales ingresados por el usuario.\n");
    printf("Permite trabajar con modelos del tema: capacidades termicas\n");
    printf("especificas, y tambien crear un modelo personalizado.\n");
    printf("============================================================\n");

    printf("\nSeleccione el tipo de modelo que desea crear:\n");
    printf("  1) Modelo Q en funcion del incremento de temperatura (ΔT)\n");
    printf("  2) Modelo Q en funcion de la temperatura absoluta (T)\n");
    printf("  3) Modelo personalizado (variables y unidades propias)\n");
    printf("------------------------------------------------------------\n");
    printf("Opcion: ");
    scanf("%i", &op);

    while (op != 1 && op != 2 && op != 3) {
        printf("Opcion invalida. Ingrese 1, 2 o 3: ");
        scanf("%i", &op);
    }

    if (op == 3) {
        printf("\nVARIABLES DEL MODELO PERSONALIZADO\n");
        printf("----------------------------------\n");

        printf("Nombre de la variable dependiente (Y): ");
        scanf("%s", vy);

        printf("Nombre de la variable independiente (X): ");
        scanf("%s", vx);

        printf("Unidades de X: ");
        scanf("%s", ux);

        printf("Unidades de Y: ");
        scanf("%s", uy);
    }

    printf("\n============================================================\n");
    printf("INGRESO DE DATOS EXPERIMENTALES\n");
    printf("============================================================\n");

    printf("¿Cuantos puntos desea ingresar? (minimo 2, máximo 20): ");
    scanf("%i", &p.n);

    for (int i = 0; i < p.n; i++) {
        printf("Punto %i (formato x,y): ", i + 1);
        scanf("%f,%f", &p.x[i], &p.y[i]);
    }

    m = pendiente(&p, p.n);
    b = ordenada(&p, p.n);

    printf("\n============================================================\n");
    printf("                   RESULTADO DEL MODELO\n");
    printf("============================================================\n");

    switch (op)
    {
    case 1:
        printf("MODELO 1: Q vs ΔT\n");
        printf("Qsum [J] = %.4f [J/K] * ΔT[K]  %+ .4f [J]\n", m, b);
        break;

    case 2:
        printf("MODELO 2: Q vs T\n");
        printf("Qsum [J] = %.4f [J/K] * T[K]   %+ .4f [J]\n", m, b);
        break;

    case 3:
        printf("MODELO PERSONALIZADO\n");
        printf("Variable independiente:  %s [%s]\n", vx, ux);
        printf("Variable dependiente:    %s [%s]\n\n", vy, uy);

        printf("Modelo final:\n");
        printf("%s[%s] = %.4f [%s/%s] * %s[%s]  %+ .4f [%s]\n",
               vy, uy, m, uy, ux, vx, ux, b, uy);
        break;
    }

    printf("============================================================\n");
    printf("Calculo completado correctamente.\n");
    printf("============================================================\n");

    return 0;
}



// FUNCIONES DEL MODELO 

float pendiente(Punto *p, int n) {
    float sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0;

    for (int i = 0; i < n; i++) {
        sumx  += p->x[i];
        sumy  += p->y[i];
        sumxy += p->x[i] * p->y[i];
        sumx2 += p->x[i] * p->x[i];
    }

    return (n * sumxy - sumx * sumy) /
           (n * sumx2 - sumx * sumx);
}

float ordenada(Punto *p, int n) {
    float sumx = 0, sumy = 0;

    for (int i = 0; i < n; i++) {
        sumx += p->x[i];
        sumy += p->y[i];
    }

    float m = pendiente(p, n);
    return (sumy - m * sumx) / n;
}
