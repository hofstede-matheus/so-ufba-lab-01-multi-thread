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

int m, n;

void generateMatrix(double matrix[m][n]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (double) rand();
		}
	}
}

void fillMatrixWithZeros(double matrix[m][m]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
}

void printMatrix(double matrix[m][n]) {
	for (int i = 0; i < m; i++) {
		printf("|");
		for (int j = 0; j < n; j++) {
			printf(" %.2f,", matrix[i][j]);
		}
		printf("|,\n");	
	}
	printf(":::::::::::::::::::\n");
}

typedef struct {
	double ** A;
	double ** B;
	double * C;
	int i;
	int j;
} t_params;


void * calc(/* double A[m][n], double B[m][n], double C[m][n], int i, int j */ t_params * params ) {
	double ** Z = (double **) params->C;
	printf("THREAD\n");
	printMatrix(params->A);
	printMatrix(params->C);
	Z[0][0] = 1;
}

int main() {
	

	printf("Informe o número de linhas:\n");
	scanf("%d", &m);

	printf("Informe o número de colunas:\n");
	scanf("%d", &n);


	double A[m][n];
	double B[m][n];
	double C[m][m];

	generateMatrix(&A);
	generateMatrix(&B);
	fillMatrixWithZeros(C);

	printMatrix(A);
	printMatrix(B);
	printMatrix(C);

	int NUM_THREADS = m * n;
	printf("%d\n", NUM_THREADS);

	pthread_t threads[NUM_THREADS];

	int CURRENT_THREAD = 0;


	for (int i = 0; i < m; i++) { // Percorre a linha
		for (int j = 0; j < n; j++) {

			t_params params;
			params.A = A;
			params.B = B;
			params.C = &C;
			params.i = i;
			params.j = j;

			pthread_create(&threads[CURRENT_THREAD], NULL, calc, &params);
			pthread_join(threads[CURRENT_THREAD], NULL);
			CURRENT_THREAD++;
		}
	}

	

	return 0;
}


