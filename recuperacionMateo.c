#include <stdio.h>
#include <string.h>

#define NUM_NADADORES 5
#define NUM_COMPETENCIAS 3
#define MAX_NOMBRE 50

int main() {
    char nombres[NUM_NADADORES][MAX_NOMBRE];
    float tiempos[NUM_NADADORES][NUM_COMPETENCIAS];
    float totales[NUM_NADADORES];
    int opcion;
    int datosIngresados = 0;

    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Ingresar datos de nadadores\n");
        printf("2. Mostrar matriz de tiempos\n");
        printf("3. Mostrar ganadores por competencia\n");
        printf("4. Mostrar ganador general\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                for (int i = 0; i < NUM_NADADORES; i++) {
                    printf("\nIngrese el nombre del nadador %d: ", i + 1);
                    scanf(" %[^\n]", nombres[i]);
                    totales[i] = 0;

                    for (int j = 0; j < NUM_COMPETENCIAS; j++) {
                        float tiempo;
                        do {
                            printf("  Tiempo en competencia %d (segundos, positivo): ", j + 1);
                            scanf("%f", &tiempo);
                            if (tiempo < 0)
                                printf("  ⚠️ El tiempo no puede ser negativo.\n");
                        } while (tiempo < 0);

                        tiempos[i][j] = tiempo;
                        totales[i] += tiempo;
                    }
                }
                datosIngresados = 1;
                break;

            case 2:
                if (!datosIngresados) {
                    printf(" Primero debes ingresar los datos.\n");
                    break;
                }
                printf("\n%-15s", "Nadador");
                for (int j = 0; j < NUM_COMPETENCIAS; j++) {
                    printf("Comp %d\t", j + 1);
                }
                printf("Total\n");

                for (int i = 0; i < NUM_NADADORES; i++) {
                    printf("%-15s", nombres[i]);
                    for (int j = 0; j < NUM_COMPETENCIAS; j++) {
                        printf("%.2f\t", tiempos[i][j]);
                    }
                    printf("%.2f\n", totales[i]);
                }
                break;

            case 3:
                if (!datosIngresados) {
                    printf("Primero debes ingresar los datos.\n");
                    break;
                }
                for (int j = 0; j < NUM_COMPETENCIAS; j++) {
                    int ganador = 0;
                    for (int i = 1; i < NUM_NADADORES; i++) {
                        if (tiempos[i][j] < tiempos[ganador][j]) {
                            ganador = i;
                        }
                    }
                    printf("\n Ganador competencia %d: %s con %.2f segundos\n", 
                            j + 1, nombres[ganador], tiempos[ganador][j]);
                }
                break;

            case 4:
                if (!datosIngresados) {
                    printf(" Primero debes ingresar los datos.\n");
                    break;
                }
                int ganadorGeneral = 0;
                for (int i = 1; i < NUM_NADADORES; i++) {
                    if (totales[i] < totales[ganadorGeneral]) {
                        ganadorGeneral = i;
                    }
                }
                printf("\n Ganador general: %s con %.2f segundos acumulados\n", 
                        nombres[ganadorGeneral], totales[ganadorGeneral]);
                break;

            case 5:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf(" Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}