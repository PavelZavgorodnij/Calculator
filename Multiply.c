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
int main()
{
	int lalala;
	FILE *f = fopen("input.txt", "r");
	fscanf(f, "%d", &lalala);
	int ili;
	FILE *g;
	g = fopen("Multiply.out", "w");
	for (ili = 0; ili < lalala; ili ++)
	{
		int i, j;
		int M, N, Q, P;
		double **A;
		fscanf(f, "%d%d", &M, &N);
		A = malloc(M * sizeof(double *));
		for(i = 0; i < M; i++) 
			A[i] = (double *)malloc(N * sizeof(double));		
		for(i = 0; i < M; i++) 
			for(j = 0; j < N; j++)
				fscanf(f, "%lf", &A[i][j]);
		double **B;
		fscanf(f, "%d%d", &Q, &P);
		B = malloc(Q * sizeof(double *));
		for(i = 0; i < Q; i++) 
			B[i] = (double *)malloc(P * sizeof(double));
		for(i = 0; i < Q; i++) 
			for(j = 0; j < P; j++)
				fscanf(f, "%lf", &B[i][j]);	
		double** C = MatrixMultiply(M, N, Q, P, A, B);
		for(i = 0; i < M; i++) 
		{
			for(j = 0; j < P; j++)
				fprintf(g, "%lf ", C[i][j]);
			fprintf(g, "\n");
		}
		for(i = 0; i < M; i++) 
		{
  		  	free(A[i]);
		}
		free(A);
		for(i = 0; i < Q; i++) 
		{
  		  	free(B[i]);
		}
		free(B);
		for(i = 0; i < M; i++) 
		{
  		  	free(C[i]);
		}
		free(C);
		fprintf(g, "\n-------------------------------------------------------------------\n");	
	}
	fclose(g);
	
	return 0;
}
