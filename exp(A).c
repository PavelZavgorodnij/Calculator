#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
double** MatrixMultiply (int m, int n, int p, int q, double** A, double** B)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(q * sizeof(double));		
	for(i = 0; i < m; i++) 
		for(j = 0; j < q; j++)
		{
			C[i][j] = 0;
			int k;
			for(k = 0; k < n; k++) 
				C[i][j] += A[i][k] * B[k][j];
		} 
	return C;	
}
//---------------------------------------------------------------------------------
double** MatrixSumm (int m, int n, double** A, double** B)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));		
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			C[i][j] = A[i][j] + B[i][j];
	return C;	
}
//---------------------------------------------------------------------------------
double** MatrixDiv (int m, int n, double** A, double B)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));		
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			C[i][j] = A[i][j] / B;
	return C;	
}
//---------------------------------------------------------------------------------
double ** Exponent(int n, double** A, int step)
{
	double** B;
	B = malloc(n * sizeof(double *));
	int i,j;
	for(i = 0; i < n; i++) 
		B[i] = (double *)malloc(n * sizeof(double));		
	for(i = 0; i < n; i++) 
		for(j = 0; j < n; j++)
			if(i == j)
				B[i][j] = 1;
			else
				B[i][j] = 0;
	double** C;
	C = malloc(n * sizeof(double *));
	for(i = 0; i < n; i++) 
		C[i] = (double *)malloc(n * sizeof(double));		
	for(i = 0; i < n; i++) 
		for(j = 0; j < n; j++)
			C[i][j] = A[i][j];
	for (i = 1; i <= step; i ++)
	{
		C = MatrixDiv (n, n, C, (double)i);
		B = MatrixSumm (n, n, C, B);
		C = MatrixMultiply (n, n, n, n, C, A);
	}
	return B;
}
int main()
{
	int lalala;
	FILE *f = fopen("input.txt", "r");
	fscanf(f, "%d", &lalala);
	int ili;
	FILE *g;
	g = fopen("exp(A).out", "w");
	for (ili = 0; ili < lalala; ili ++)
	{
		int i, j;
		int MyStep;
		int N;
		double **A;
		fscanf(f, "%d%d", &MyStep, &N);
		A = malloc(N * sizeof(double *));
		for(i = 0; i < N; i++) 
			A[i] = (double *)malloc(N * sizeof(double));		
		for(i = 0; i < N; i++) 
			for(j = 0; j < N; j++)
				fscanf(f, "%lf", &A[i][j]);
		double** C = Exponent(N, A, MyStep);
		for(i = 0; i < N; i++) 
		{
			for(j = 0; j < N; j++)
				fprintf(g, "%lf ", C[i][j]);
			fprintf(g, "\n");
		}
		
		for(i = 0; i < N; i++) 
		{
  		  	free(A[i]);
		}
		free(A);
		for(i = 0; i < N; i++) 
		{
  		  	free(C[i]);
		}
		free(C);
		fprintf(g, "\n-------------------------------------------------------------------\n");

	}
	fclose(g);
	return 0;
}
