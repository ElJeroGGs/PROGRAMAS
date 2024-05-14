#include <string.h> 
#include <omp.h>
#include <stdio.h>

int N;
int M;

void pintaMatriz(int orden1, int orden2, int matriz[orden1][orden2]) {
   // Imprimir la matriz
    #pragma omp synchronized parallel for
    for (int i = 0; i < orden1; i++) {
        for (int j = 0; j < orden2; j++) {
            printf("[%d]", matriz[i][j]);
        }
        printf("\n");
    }
}

int sumaHijos(int renglon[M]){
    int suma = 0;
    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < M; i++) {
        suma += renglon[i];
    }
    return suma;
}

int SumaPadre(int renglon[N]){
    int suma = 0;
    #pragma omp master
    for (int i = 0; i < 1; i++) {
        suma += renglon[0] + renglon[1];
    }
    return suma;
}


    void renglonHijo(int suma, int N, int renglon[]) {
       
        renglon[0] = suma;
        #pragma omp parallel for 
        for (int i = 1; i < N - 1; i++) {
            renglon[i] = suma / 2;
        }
    }

void pintarRenglon(int renglon[N]){
    #pragma omp synchronized parallel for 
    for (int i = 0; i < N; i++) {
        printf("[%d]", renglon[i]);
    }
    printf("\n");
}

int main() {
    printf("Cual es el orden de tu matriz\n");
    scanf("%d", &N);
    M = N - 1;
    // Definir la matriz
    
    int matriz[N][N];

    // Llenar la matriz
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = i+1;
        }
    }

    pintaMatriz(N,N, matriz);

    // Calcular la suma de los primeros dos elementos de la matriz por renglon 
    int MatrizReducida[N][M];
    int Resultado[N];
#pragma omp synchronized parallel for
   for (int i = 0; i < N; i++){

    for (int j = 0; j < M; j++) {
        int suma = SumaPadre(matriz[i]);
        int renglon[M];
        //Modificar el renglon
        renglonHijo(suma, N, renglon);

        //Guardar el renglon en la matriz de prueba
        
        MatrizReducida[i][j] = renglon[j];

        //Suma el renglon
        int sumaRenglon = sumaHijos(renglon);
        Resultado[i] = sumaRenglon;
        }

   }
   
    printf("Matriz reducida\n");
    pintaMatriz(N,M, MatrizReducida);
    printf("Resultado\n");
    pintarRenglon(Resultado);
    return 0;
}






