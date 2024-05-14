#include <stdio.h>
#include <omp.h>
#include <string.h> // Include the header file for 'String' type
#include <stdlib.h> // Include the header file for 'malloc' function
#include <math.h> // Include the header file for 'rand' function

void reverse(int Vector[], int size){
    int temp;
    #pragma omp parallel for synchronized
    for(int i = 0; i < size/2; i++){
        temp = Vector[i];
        Vector[i] = Vector[size - i - 1];
        Vector[size - i - 1] = temp;
    }
}



char* toString(int Vector[], int size){
    // Asumiendo que cada número tiene menos de 10 dígitos, necesitamos al menos size*10 caracteres
    // Además, necesitamos espacio para los caracteres '[', ']', ',' y ' '

    char* str = malloc((size * 10 + size + 2) * sizeof(char));
    str[0] = '['; // Inicializar la cadena con un corchete de apertura
    str[1] = '\0'; // Asegurarse de que la cadena es una cadena de caracteres válida

#pragma omp parallel for synchronized

    for(int i = 0; i < size; i++){
        char temp[12]; // Necesitamos espacio para el número, la coma y el espacio
        if (i != size - 1) {
            sprintf(temp, "%d, ", Vector[i]); // Formatear el número con una coma y un espacio si no es el último número
        } else {
            sprintf(temp, "%d", Vector[i]); // No añadir una coma y un espacio después del último número
        }
        strcat(str, temp);
    }

    strcat(str, "]"); // Añadir un corchete de cierre al final

    
    return str;
}

int main(){
    int N = 10;
    int Vector[N];
    for(int i = 0; i < N; i++){
        Vector[i] = rand() % 100;
    }
    //Imprime el vector original
    char* str = toString(Vector, N);
    printf("Vector:           %s", str);
    printf("\n");

    free(str); // Liberar la memoria

    //Cambia el vector
    reverse(Vector, 10);

    //Imprime el vector cambiado
    str = toString(Vector, N);
    printf("Vector invertido: %s", str);
    free(str);

    return 0;
}



