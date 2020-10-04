#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>
#include "errors.h"

#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREADS 64
// #define NUM_TERM_SERIES 1000000000
#define NUM_TERM_SERIES 1000000


pthread_t threads[NUM_THREADS];
double result[NUM_TERM_SERIES];

typedef struct {
    double * resultRef;
    int position;
	double operator;
} t_params;



void* calculatePI(t_params * params) {
	printf("position: %d\n", params->position);
	printf("operator: %.5f\n", params->operator);
	printf("calc: %.5f\n", params->operator*(4.0 / (3.0+2.0*params->position)));
	params->resultRef[params->position] = params->operator*(4.0 / (3.0+2.0*params->position));
	printf("this position ::%.8f::\n", params->resultRef[params->position]);
	printf("this position ::%.8f::\n", params->resultRef[params->position]);
}

/* int main() {
   printf("Calculando número PI usando série de Leibniz\n");
   printf("Este processo pode demorar um pouquinho, dependendo de sua CPU.\n");
   printf("O número PI é gerado através de sucessivas somas e subtrações 900 milhões de vezes!\n");


   double pi = 4;
   double operador = -1;

   double i;
   for(i = 0; i < NUM_TERM_SERIES; i++){
	   printf("%.2f::%.2f\n", pi, operador*(4/(3+2*i)));
      pi += operador*(4/(3+2*i));

      operador *= -1;
   }

   printf("Resultado: %.64f...\n", pi);

   return 0;
} */


int main(){
	printf("Calculando número PI usando série de Leibniz\n");
	printf("Este processo pode demorar um pouquinho, dependendo de sua CPU.\n");
	printf("O número PI é gerado através de sucessivas somas e subtrações 900 milhões de vezes!\n");


	double pi = 4;
	double operador = -1;

	for(int i = 0, j = 0; i < NUM_TERM_SERIES; i++, j++) {

		t_params params;
		params.position = i;
		params.resultRef = &result;
		params.operator = operador;

		printf("pre:%.2f\n", params.operator);

		if (j == NUM_THREADS - 1) j = 0;
		

		pthread_create(&threads[j], NULL, calculatePI, (void*)&params);

		operador *= -1;
	}
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	for (int i = 0; i < NUM_TERM_SERIES; i++) {
		pi+= result[i];
	}
	
	

	printf("Resultado: %.64f...\n", pi);

	return 0;
}


