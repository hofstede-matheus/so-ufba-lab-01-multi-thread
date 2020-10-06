/*
  O programa deve ser executado desta maneira:
    gcc multmatriz.c -std=c99 -Wall -o mulmatriz -lm -lpthread
    ./multmatriz MatrizA MatrizB
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>

#define SIZE 1000   // setando os valores da matriz NxN

int numThreads=32;
double **mat1, **mat2, **mat3;

double ** alocarMatriz(){
  // alocando o SIZE * SIZE double
  double * tamanho = (double *) malloc( SIZE * SIZE * sizeof(double) );

  //alocando array de double
  double ** array = (double **) malloc( SIZE * sizeof(double*) );

  int i;
  for (i = 0; i < SIZE; i++) {
    array[ i ] = &tamanho[ i * SIZE ];
  }
  return array;
}

void iniciarMatriz(double **mat){
  int i, j;
    
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      mat[ i ][ j ] = rand() % 10; //setando valores aleatorios
    }
  }
}

/**
 * Rotina do thread
 * Cada thread com uma porcao da matriz 1 (ou A)
 * o inicio e o fim depende do arg, que no caso é o ID atribuido a cada thread sequencialmente
 */
void * multiplicarMatriz(void *arg ){
  int i, j, k, tid, inicioLinha, fimLinha;
  double soma;
  
  tid = *(int *)(arg); // pega o ID atribuido a cada thread sequencialmente
  inicioLinha = (tid *SIZE)/ numThreads;  // dividindo cada thread para o inicio da linha
  fimLinha = ((tid+1) *SIZE)/ numThreads; //  dividindo cada thread para o final da linha
  
  for (i = inicioLinha; i < fimLinha; i++) { 
    for (j = 0; j < SIZE; j++) { 
      soma = 0; 

      for (k = 0; k < SIZE; k++) { 
	        soma += mat1[ i ][ k ] * mat2[ k ][ j ];
      }
      mat3[ i ][ j ] = soma;
    }
  }
  pthread_exit(0);
}

/*void mostrarMatriz( double **mat){
  int i, j;

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE-1; j++) {
      printf( "%lf, ", mat[ i ][ j ] );
    }
    printf( "%lf", mat[ i ][ j ] );
    putchar( '\n' );
  }
}*/

int main( int argc, char *argv[] ){
  int i;
  struct timeval tempoInicio, tempoFinal;
  double tempoExecucaoTotal,tempoExecucao1,tempoExecucao2;
  pthread_t * threads;

  if (argc != 3) {
    printf("O comando deve ser ./multmatriz MatrizA MatrizB\n" );
    return -1;
  }

  printf("Executando...\n");

  /*SIZE = atoi( argv[1] );
  numThreads = atoi( argv[2] );
*/

  threads = (pthread_t *) malloc( numThreads * sizeof(pthread_t) );

  mat1 = alocarMatriz();
  mat2 = alocarMatriz();
  mat3 = alocarMatriz();
  
  iniciarMatriz(mat1);
  iniciarMatriz(mat2);

    /*printf( "Matriz 1:\n" );
    mostrarMatriz( mat1);
    printf( "Matriz 2:\n" );
    mostrarMatriz( mat2);*/

  gettimeofday( &tempoInicio, NULL );//pegando tempo inicial
  for ( i = 0; i < numThreads; i++) {
    int *tid;
    tid = (int *) malloc( sizeof(int) );
    *tid = i;
    pthread_create( &threads[i], NULL, multiplicarMatriz, (void *)tid );
  }

  for ( i = 0; i < numThreads; i++) {
    pthread_join( threads[i], NULL );
  }
  gettimeofday( &tempoFinal, NULL );//pegando tempo final
  

    /*printf( "Matriz 3:\n" );
    mostrarMatriz(mat3);*/
  
  tempoExecucao1 = (tempoFinal.tv_sec - tempoInicio.tv_sec) * 1000.0; // de segundo para milisegundos
  tempoExecucao2 = (tempoFinal.tv_usec - tempoInicio.tv_usec) / 1000.0; // de microsegundos para milisegundos 

  tempoExecucaoTotal = tempoExecucao1 + tempoExecucao2;// somando tempo total
  printf("Foram utilizadas %d threads na multiplicação da matriz 1000x1000, com %.3lf segundos de execução.\n", numThreads, tempoExecucaoTotal/1000.0);

  free(mat1);
  free(mat2);
  free(mat3);

  return 0;
}
