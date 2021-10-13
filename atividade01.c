#include<stdio.h>
#include<stdlib.h>
#define NUM_THREADS 4
#include<omp.h>
#include <time.h>

int generate_int(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int main()
{
    int TAM = 100, A[TAM], B[TAM], i, Gera[TAM], Result[TAM];
    char Operador[TAM], operacao = "", operadores[4] = {'+','-','*','/'}, operador = "";
    //Vetor de A
    printf(" A: \n");
    for (i = 0 ;  i < TAM; i++)
    {
        A[i] = rand()%TAM;
        printf("%d  ", A[i]);
    }
    //Vetor de Operações
    printf("\n\n Operadores:\n");
    for(i=0; i<TAM; i++) {
       Gera[i] = rand() %4;
        if(Gera[i] == 0){
          operacao= '+';
        } else if(Gera[i] == 1){
            operacao='-';
        } else if(Gera[i] == 2){
            operacao='*';
        } else{
            operacao='/';
        }

    Operador[i] = operacao;
    printf("%c ", Operador[i]);

    }
    //Vetor de B
    printf("\n B: \n");
    for (i = 0 ;  i < TAM; i++)
    {
        B[i] = rand()%TAM;
        printf("%d  ", B[i]);
    }

    printf("\n\nResultados: ");
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        printf("Thread %d de um total de %d \n", id, nt);
    #pragma omp for
    for(i = 0; i < TAM; i++){
        operador = Operador[i];

        switch(operador)
        {
            case '+': Result[i] = A[i] +  B[i];
                break;
            case '-': Result[i] = A[i] -  B[i];
                break;
            case '*': Result[i] = A[i] *  B[i];
                break;
            case '/': Result[i] = A[i] /  B[i];
                break;
        }

        printf("%d ",Result[i]);
    }
    printf("\n\n");
    }
    return 0;
}
