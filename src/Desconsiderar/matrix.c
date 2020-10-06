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

int m = 2, n = 2;

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
	double * A;
	double * B;
	double * C;
	int i;
	int j;
	int k;
} t_params;


void * calc(/* double A[m][n], double B[m][n], double C[m][n], int i, int j */ t_params * params ) {
	/* double ** Z = (double **) &params->C;
	printf("THREAD\n");
	printMatrix(params->A);
	Z[0][0] = 1;
	printMatrix(params->C); */

	double ** C = (double **) &params->C;
	double ** A = (double **) &params->A;
	double ** B = (double **) &params->B;
	printf("params->i:%d\n", params->i);
	printf("params->j:%d\n", params->j);
	printf("params->k:%d\n", params->k);

	printf("\n");


	for (int i = 0; i < params->k; i++) {
		/* printf("i:%d\n", i);
		printf("%.2f::%.2f\n", A[0][0], B[0][0]);
		printf("OI\n"); */
		printf("i:%d\n", i);
		double value1 = A[params->i][i];
		printf("value1:%.2f\n", value1);
		double value2 = B[i][params->j];
		printf("value2:%.2f\n", value2);


		C[0][0] = (double) (A[params->i][i] * B[i][params->j]);

		printf(":::::\n");
		printMatrix(C);
		printf(":::::\n");


	}
	




}

int main() {

	/* printf("Informe o número de linhas:\n");
	scanf("%d", &m);

	printf("Informe o número de colunas:\n");
	scanf("%d", &n); */

	double A[m][n];
	double B[m][n];
	double C[m][m];

	/* generateMatrix(&A);
	generateMatrix(&B); */
	A[0][0] = 1;
	A[0][1] = 2;
	A[1][0] = 3;
	A[1][1] = 4;

	B[0][0] = 1;
	B[0][1] = 2;
	B[1][0] = 3;
	B[1][1] = 4;



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
			params.A = &A;
			params.B = &B;
			params.C = &C;
			params.i = i;
			params.j = j;
			params.k = m;

			pthread_create(&threads[CURRENT_THREAD], NULL, calc, &params);
			pthread_join(threads[CURRENT_THREAD], NULL);
			CURRENT_THREAD++;
		}
	}

	printf("OK\n");
	printMatrix(C);

	return 0;
}


