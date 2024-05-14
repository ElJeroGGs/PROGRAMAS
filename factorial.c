#include <stdio.h>
#include <omp.h>

int factorial(int n){
    int i;
    int fact = 1;

    //Multiplica de forma paralela desde el 1 a n
    #pragma omp parallel for reduction(*:fact)
    for(i=1;i<=n;i++){
        fact *= i;
    }
    return fact;
}

int main(){
    int n = 5;
    int fact = factorial(n);
    printf("Factorial de %d = %d\n", n, fact);
    return 0;
}