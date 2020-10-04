/*
  O programa deve ser executado desta maneira:
    gcc estatistica.c -std=c99 -Wall -o estatistica -lm -lpthread
   ./estatistica 90 81 78 95 79 75 85

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numThreads=3;
int *vetorValores;
int tamanhoInstancia;
int valorMaior = 0;
int valorMenor = 1000000; 
int valorMedio = 0;

//funcao para pegar o menor valor
void *menor(){
    int i;

    for(i = 1; i < tamanhoInstancia; i++){
        if(valorMenor > vetorValores[i]){
            valorMenor = vetorValores[i];
        }   
 
    }
    printf("O valor mínimo é %d\n",valorMenor);

    return 0;
}

//funcao para pegar o maior valor
void *maior(){
    int i;

    for(i = 1; i < tamanhoInstancia; i++){
        
        if(valorMaior < vetorValores[i]){
            valorMaior = vetorValores[i];
        }   
        
    }
    printf("O valor máximo é %d\n",valorMaior);

    return 0;
}

//funcao para pegar o valor medio
void *medio(){
    int i;
    int soma=0;

    for(i = 1; i < tamanhoInstancia; i++){
        soma+=vetorValores[i];      
    }
    printf("O valor médio é %d\n",soma/(tamanhoInstancia-1));

    return 0;
}

/*void * estatistica(){
    //int *array, int tamanhoInstancia
    menor();
    maior();
    medio();

    return 0;
}*/


int main( int argc, char *argv[] ){
  int i;

  tamanhoInstancia = argc;
  pthread_t * threads;
  char *value;
 
vetorValores = (int *) malloc((argc-1) * sizeof(int));
 //pegando valores  da linha de comando
    for(i = 1; i < argc; i++){
        value = argv[i];
        //funcao para transformar texto em numero
        vetorValores[i] = atoi(value);
    }

  threads = (pthread_t *) malloc( numThreads * sizeof(pthread_t) );

  //criando threads
  pthread_create( &threads[0], NULL, medio, NULL );
  pthread_create( &threads[1], NULL, menor, NULL );
  pthread_create( &threads[3], NULL, maior, NULL );
  //thread1 = pthread_create( &threads[0], NULL, menor, (void *)tid );


  for ( i = 0; i < numThreads; i++) {
    pthread_join( threads[i], NULL );
  }
  free(vetorValores);
  pthread_exit(0);
  return 0;
}