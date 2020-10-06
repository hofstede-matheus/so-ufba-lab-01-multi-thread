/*
  O programa deve ser executado desta maneira:
    gcc calcpi.c -std=c99 -Wall -o calcpi -lm -lpthread

    ./calcpi

    // 1 - (1/3) + (1/5) - (1/7) + (1/9) ... = pi/4
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

long qtdThreads=100; // quantidade de threads
long long qtdTotalDeTermos=1000000000; //quantidade de termos
double pi;


void* calcPi(void* arg) {
   long copiaQtdThreads = (long) arg;
   double denominador;
   double somaDosValoresDePi;
   long long i;

   /*
      para entender a escolha das variaveis abaixo, faca o seguinte:
      execute o programa com qtdThread = 2 e qtdTotalDeTermos = 8, pois escolhendo numeros pequenos fica mais facil a visualizacao
      
      se executar conforme mencionei, o resultado será:

      copiaQtdThreads 1
      totalDeTermosPorThread 4
      inicioThread 4
      fimThread 8

      copiaQtdThreads 0
      totalDeTermosPorThread 4
      inicioThread 0
      fimThread 4

      isso quer dizer que:
      na linha 33, temos a copiaQtdThreads = 1, se escolher qtdThreads fica com um valor maior
      na linha 34, tem a quantidade de termos q ficou em cada thread, ou seja, qtdTotalDeTermos / qtdThreads
      na linha 35, temos o inicio do loop para cada thread, em vez de ser somente o i, tem q ser o incio de cada thread
      na linha 36, temos o final do loop para cada thread, ou seja, o limite da operacao da thread atual

      na outra parte temos:
      na linha 38, temos a copia de threads chegando ao fim, pois no exemplo foram so duas
      na linha 39, temos a outra thread, como dividiu 8/2, cada thread possui 4 termos
      na linha 40, ele pega o i inicial da outra thread, que no caso agora é 0
      na linha 41, ele pega o final dessa mesma thread

      resumindo:

      as threads sao divididas em duas, com 4 termos cada, ou seja 8/2 = 4
      entao tem q pegar o inicio e o fim das duas threads, para que seja feito a divisao correta dos termos

      nesse sentido, acaba ficando mais ou menos assim:

      1° thread = 5 6 7 8
      2° thread = 1 2 3 4
      
   */

   long long totalDeTermosPorThread = qtdTotalDeTermos / qtdThreads; // dividindo a quantidade total de termos pela quandtidade total de threads
   long long inicioThread = totalDeTermosPorThread * copiaQtdThreads;// setando o i inicial de cada thread
   long long fimThread = inicioThread + totalDeTermosPorThread;//setando o i final de cada thread

   // printf(" copiaQtdThreads %ld\n", copiaQtdThreads);
   // printf(" totalDeTermosPorThread %llu\n", totalDeTermosPorThread);
   // printf(" inicioThread %llu\n", inicioThread);
   // printf(" fimThread %llu\n\n", fimThread);
    

   // calculo de leibniz   1 - (1/3) + (1/5) - (1/7) + (1/9) ... = pi/4
   for(i=inicioThread; i<fimThread; i++){
      denominador = i * 2 + 1;

      if(i%2 == 0){
        somaDosValoresDePi -= (1/denominador);
      }else{
        somaDosValoresDePi += (1/denominador);
      }
    }
    pi += somaDosValoresDePi;
    
   return NULL;
}


int main(int argc, char* argv[]) {
   long i;
   pthread_t* thread;// criando a(s) thread(s)
   pi = 0.0;

   //declarando variaveis para medir o tempo
   struct timeval tempoInicio, tempoFinal;
   double tempoExecucaoTotal,tempoExecucao1,tempoExecucao2;

   printf("Executando...\n");

   gettimeofday( &tempoInicio, NULL );//pegando tempo inicial----------------------------------------

   thread = malloc (qtdThreads*sizeof(pthread_t)); 
   
   //executando as threads
   for (i = 0; i < qtdThreads; i++){
      pthread_create(&thread[i], NULL,calcPi, (void*)i);
   }    

   for (i = 0; i < qtdThreads; i++){
      pthread_join(thread[i], NULL);
   } 

   //pi *= 4;
   //printf("%g\n", pi);//testando pra ver se o valor esta correto

   gettimeofday( &tempoFinal, NULL );//pegando tempo final---------------------------------------------


   tempoExecucao1 = (tempoFinal.tv_sec - tempoInicio.tv_sec) * 1000.0; // de segundos para milisegundos
   tempoExecucao2 = (tempoFinal.tv_usec - tempoInicio.tv_usec) / 1000.0; // de microsegundos para milisegundos e somando tempo total

   tempoExecucaoTotal = tempoExecucao1 + tempoExecucao2;
   printf("Foram utilizadas %ld threads para calcular %lld termos de PI, com %.3lf segundos de execução.\n\n", qtdThreads, qtdTotalDeTermos, tempoExecucaoTotal/1000.0);

   free(thread);
   return 0;
}  