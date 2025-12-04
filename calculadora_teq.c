#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>



// Lista de 10 sustancias predefinidas
typedef struct {
    char nombre[30];
    double capacidad_termica;  // J/(kg·°C)
    double densidad_kgm3;      // kg/m^3
    double densidad_kgL;      // kg/l
} Sustancia;

Sustancia sustancias[10] = {
    {"Agua", 4186, 1000.0, 1.000},
    {"Acetona", 2150, 784.6, 0.785},
    {"Gasolina", 2220, 737.0, 0.737},
    {"Alcohol isopropilico", 2680, 785.0, 0.785},
    {"Amoniaco", 4700, 824.0, 0.824},
    {"Glicerina", 2400, 1259.0, 1.259},
    {"Acido Sulfurico", 1380, 1490.0, 1.490},
    {"Mercurio", 140, 13595.0, 13.595},
    {"Cloruro", 960, 1560.0, 1.560},
    {"Aceite de maiz", 2000, 926.0, 0.926}
};

// Función para mostrar el menú de sustancias
void mostrarSustancias() {
    printf("\n=== SUSTANCIAS DISPONIBLES ===\n");
    printf("     Capacidad termica en [J/(kg*C)]    |       Densidad en [kg/m^3] y [kg/L]\n");
    for(int i = 0; i < 10; i++) {
        //double densidad_kgL = sustancias[i].densidad_kgm3 / 1000.0;
        printf("%2d. %-20s  Cp: %6.0f  Dens: %7.1f kg/m^3  (%5.3f kg/L)\n", 
               i+1, sustancias[i].nombre, 
               sustancias[i].capacidad_termica, 
               sustancias[i].densidad_kgm3,
               sustancias[i].densidad_kgL);
    }
    printf("================================\n");
}

// Función para validar entrada de números
int leerEntero(char* mensaje, int min, int max) {
    int valor;
    while(1) {
        printf("%s", mensaje);
        if(scanf("%d", &valor) == 1 && valor >= min && valor <= max) {
            // Limpiar buffer
            while(getchar() != '\n');
            return valor;
        }
        printf("Error: Debe ingresar un numero entre %d y %d\n", min, max);
        // Limpiar buffer en caso de error
        while(getchar() != '\n');
    }
}

// Función para leer número decimal
double leerDecimal(char* mensaje) {
    double valor;
    while(1) {
        printf("%s", mensaje);
        if(scanf("%lf", &valor) == 1) {
            // Limpiar buffer
            while(getchar() != '\n');
            return valor;
        }
        printf("Error: Ingrese un numero valido (1 entero con 1 decimal)\n");
        // Limpiar buffer en caso de error
        while(getchar() != '\n');
    }
}

double calcularTeqDiferentes(double m1, double cp1, double t1, 
                            double m2, double cp2, double t2) {
    double numerador = (m1 * cp1 * t1) + (m2 * cp2 * t2);
    double denominador = (m1 * cp1) + (m2 * cp2);
    
    if(denominador == 0) {
        return (t1 + t2) / 2;
    }
    return numerador / denominador;
}

double calcularTeqMisma(double m1, double t1, double m2, double t2) {
    return (m1 * t1 + m2 * t2) / (m1 + m2);
}

int main() {
    
    setlocale(LC_ALL, "");
    
    int op1, op2, misma_sustancia;
    double temp1, temp2, volumen1, volumen2, masa1, masa2;
    
    printf("=====================================================\n");
    printf("        CALCULADORA DE TEMPERATURA DE EQUILIBRIO\n");
    printf("=====================================================\n");
    printf("\nDESCRIPCION:\n");
    printf("Este programa calcula la temperatura de equilibrio termico\n");
    printf("resultante de mezclar dos sustancias liquidas.\n");
    printf("=====================================================\n");
    printf("\nEl calculo se basa en el principio de conservacion de energia:\n");
    printf("Q_perdido = Q_ganado  ->  m1*c1*(Teq-T1) = m2*c2*(T2-Teq)\n");

    mostrarSustancias();
    
    // Preguntar si son la misma sustancia
    misma_sustancia = leerEntero("\nSe trata de la misma sustancia? (1=si, 2=no): ", 1, 2);
    
    // Seleccionar líquido 1
    printf("\n--- LIQUIDO 1 ---\n");
    op1 = leerEntero("Seleccione sustancia (1-10): ", 1, 10);
    volumen1 = leerDecimal("Volumen [L] (1 entero y 1 decimal): ");
    temp1 = leerDecimal("Temperatura inicial [*C]: ");
    
    // Calcular masa 1 (volumen L * densidad kg/L)
    masa1 = volumen1 * (sustancias[op1-1].densidad_kgL);
    
    // Seleccionar líquido 2
    printf("\n--- LIQUIDO 2 ---\n");
    if(misma_sustancia == 2) {
        op2 = leerEntero("Seleccione sustancia (1-10): ", 1, 10);
    } else {
        op2 = op1;
        printf("Misma sustancia: %s\n", sustancias[op1-1].nombre);
    }
    
    volumen2 = leerDecimal("Volumen [L] (1 entero y 1 decimal): ");
    temp2 = leerDecimal("Temperatura inicial [*C]: ");
    
    // Calcular masa 2 (volumen L * densidad kg/L)
    masa2 = volumen2 * (sustancias[op2-1].densidad_kgL);
    
    // Obtener datos
    Sustancia s1 = sustancias[op1-1];
    Sustancia s2;
    if (misma_sustancia == 1) {
        s2 = s1;  // Misma sustancia
    } else {
        s2 = sustancias[op2-1];  // Sustancia diferente
    }
    
    // Calcular temperatura de equilibrio
    double teq;
    if(misma_sustancia == 1) {
        teq = calcularTeqMisma(masa1, temp1, masa2, temp2);
    } else { // misma_sustancia == 2
        teq = calcularTeqDiferentes(masa1, s1.capacidad_termica, temp1,
                                masa2, s2.capacidad_termica, temp2);
    }
    
    // Mostrar resultados
    printf("\n");
    printf("=========================================================================\n");
    printf("                     RESULTADOS DEL CALCULO\n");
    printf("=========================================================================\n");
    printf("PARAMETRO               LIQUIDO 1                LIQUIDO 2\n");
    printf("-------------------------------------------------------------------------\n");
    printf("Sustancia           %-20s  %-20s\n",    s1.nombre,    s2.nombre);
    printf("Volumen [L]          %9.3f             %9.3f\n", volumen1, volumen2);
    printf("Masa [kg]            %9.3f             %9.3f\n", masa1, masa2);
    printf("Temp. inicial [*C]   %9.1f             %9.1f\n", temp1, temp2);
    printf("Cap. termica [J/kg*C] %9.0f             %9.0f\n",
           s1.capacidad_termica, s2.capacidad_termica);
    printf("Densidad [kg/m^3]    %9.0f             %9.0f\n", 
           s1.densidad_kgm3, s2.densidad_kgm3);
    printf("-------------------------------------------------------------------------\n");
    printf("TEMPERATURA DE EQUILIBRIO TERMICO: %.2f [*C]\n", teq);
    printf("=========================================================================\n");
    
    printf("\nPresione Enter para salir...");
    getchar();
    
    return 0;
}