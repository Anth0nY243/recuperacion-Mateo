#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_NADADORES 5
#define NUM_COMPETENCIAS 3
#define MAX_NOMBRE 50

int main() {
    char nombres[NUM_NADADORES][MAX_NOMBRE];
    float tiempos[NUM_NADADORES][NUM_COMPETENCIAS];
    float totales[NUM_NADADORES];
    int distancias[NUM_COMPETENCIAS] = {50, 100, 200};
    int opcion;
    int datosIngresados = 0;

    char entrada[100];
    char *finptr;

    do {
        printf("\n--- MENÚ ---\n");
        printf("1. Ingresar datos de nadadores\n");
        printf("2. Mostrar matriz de tiempos\n");
        printf("3. Mostrar ganadores por competencia\n");
        printf("4. Mostrar ganador general\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");

        fgets(entrada, sizeof(entrada), stdin);
        opcion = strtol(entrada, &finptr, 10);
        while (finptr == entrada || (*finptr != '\0' && *finptr != '\n')) {
            printf("  ⚠️ Entrada inválida. Ingrese una opción numérica: ");
            fgets(entrada, sizeof(entrada), stdin);
            opcion = strtol(entrada, &finptr, 10);
        }

        switch (opcion) {
            case 1:
                for (int i = 0; i < NUM_NADADORES; i++) {
                    printf("\nIngrese el nombre del nadador %d: ", i + 1);
                    scanf(" %[^\n]", nombres[i]);
                    getchar(); // limpiar salto de línea
                    totales[i] = 0;

                    for (int j = 0; j < NUM_COMPETENCIAS; j++) {
                        float tiempo;
                        int valido = 0;

                        while (!valido) {
                            printf("  Tiempo en competencia %d (%d metros): ", j + 1, distancias[j]);
                            fgets(entrada, sizeof(entrada), stdin);
                            tiempo = strtof(entrada, &finptr);

                            if (finptr == entrada || (*finptr != '\0' && *finptr != '\n')) {
                                printf("   Entrada inválida. Ingrese un número válido.\n");
                            } else if (tiempo < 0) {
                                printf("   El tiempo no puede ser negativo.\n");
                            } else {
                                valido = 1;
                                tiempos[i][j] = tiempo;
                                totales[i] += tiempo;
                            }
                        }
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
                    printf("%3dm\t", distancias[j]);
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
                    printf(" Primero debes ingresar los datos.\n");
                    break;
                }

                for (int j = 0; j < NUM_COMPETENCIAS; j++) {
                    int ganador = 0;
                    for (int i = 1; i < NUM_NADADORES; i++) {
                        if (tiempos[i][j] < tiempos[ganador][j]) {
                            ganador = i;
                        }
                    }
                    printf("\nGanador competencia %d (%d metros): %s con %.2f segundos\n",
                           j + 1, distancias[j], nombres[ganador], tiempos[ganador][j]);
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
                printf(" Saliendo del programa.\n");
                break;

            default:
                printf(" Opción inválida. Intente de nuevo.\n");
        }

    } while (opcion != 5);

    return 0;
}
