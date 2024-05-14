#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main() {
    omp_set_num_threads(6);
    srand(time(NULL));

    int num1 = rand() % 10;
    int num2 = rand() % 10;
    int suma, multiplicacion, division;

    printf("Numero 1: %d\n", num1);
    printf("Numero 2: %d\n\n", num2);

    #pragma omp parallel 
    {
        #pragma omp single
        {
            suma = num1 + num2;
            printf("Suma: %d\n", suma);
            _sleep(1000);
        }


        #pragma omp single
        {
            multiplicacion = num1 * num2;
            printf("Multiplicacion: %d\n", multiplicacion);
            _sleep(1000);
        }

        #pragma omp single
        {
            if (num2 != 0) {
                division = num1 / num2;
                printf("Division: %d", division);
                printf("    Residuo: %d\n", num1 % num2);
            } else {
                printf("Division: No se puede dividir por cero\n");
            }
            _sleep(1000);
        }
    }

    return 0;
}