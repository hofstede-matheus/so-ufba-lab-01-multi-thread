/*
  O programa deve ser executado desta maneira:
    gcc primos.c -std=c99 -Wall -o primos -lm -lpthread

    ./primos <numero>, onde <numero> é o limite para mostrar os numeros primos, menores ou igual a ele

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define numThreads 2 // setar quantidade de threads q serao utilizadas

//funcao para checar se o numero dado é primo
void *ePrimo(void *numeroParaTestar) {
   int i,j,limiteDeChecagem = atoi(numeroParaTestar);

   //inicio do laco para checar se um número é primo
   for(i = 2; i <= limiteDeChecagem; i++) {
   int naoEprimo = 0;

      //checar cada numero pra ver se é divisivel
      for(j = 2; j < i; j++) {
         int resultadoDaChecagem = i % j;

         //se encontrar algum que divide, pode sair do loop pois não é primo
         if(resultadoDaChecagem == 0) {
            naoEprimo = 1;
            break;
         }
      }

      //se nao existe nenhum divisivel, ele é primo
      if(naoEprimo == 0) {
         printf("%d ", i);
      }
   }

   pthread_exit(0);
}

int main(int argc, char *argv[]) {

   //verificando se foram passados poucos argumentos
   if(argc < 2) {
      fprintf(stderr, "Voce esta utilizando poucos argumentos. Utilize: ./primos <numeroAqui>\n");
      exit(1);
   }
   //verificando se foram passados muitos argumentos
   else if(argc > 2){
      fprintf(stderr, "Voce esta utilizando muitos argumentos. Utilize: ./primos <numeroAqui>\n");
      exit(1);
   }

   //verificando se o numero passado é menor do 2
   if(atoi(argv[1]) < 2) {
      fprintf(stderr, "O numero utilizado deve ser maior ou igual a 2.\n");
      exit(1);
   }

   //criando threads
   pthread_t *threads;
   threads = (pthread_t *) malloc( numThreads * sizeof(pthread_t) );

   printf("Esses são os numeros primos menores ou igual a %d:\n", atoi(argv[1]));

   pthread_create( &threads[0], NULL, ePrimo, argv[1] );
   pthread_join( threads[0], NULL );

   printf("\n");
  
}

