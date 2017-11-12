#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
double Extr(double A, double B, int min)
{
	if((A - B) * min > 0)
		return B;
	else
		return A;
}
double** ElementarySwap(int m, int n, double** A, int s1, int s2, int stolb)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < m; i++) 
	for(j = 0; j < n; j++)
		C[i][j] = A[i][j];
	if(stolb == 0)
		for(j = 0; j < n; j++)
		{
			C[s1][j] = A[s2][j];
			C[s2][j] = A[s1][j];
		}
	else
		for(i = 0; i < m; i++) 
		{
			C[i][s1] = A[i][s2];	
			C[i][s2] = A[i][s1];
		}
	return C;	
}
//#####################################################################################
double** ElementaryCombo(int m, int n, double** A, int s1, int s2, double Lambda, int stolb)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < m; i++) 
	for(j = 0; j < n; j++)
		C[i][j] = A[i][j];
	if(stolb == 0)
		for(j = 0; j < n; j++)
			C[s1][j] += Lambda * A[s2][j];
	else
		for(i = 0; i < m; i++) 
			C[i][s1] += Lambda * A[i][s2];	
		
	return C;	
}
//######################################################################################
double** ElementaryMulty(int m, int n, double** A, int s1, double Lambda, int stolb)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < m; i++) 
	for(j = 0; j < n; j++)
		C[i][j] = A[i][j];
	if(stolb == 0)
		for(j = 0; j < n; j++)
			C[s1][j] *= Lambda;
	else
		for(i = 0; i < m; i++) 
			C[i][s1] *= Lambda;	
		
	return C;	
}
//###################################################################################


int main()
{
	int m, n;
	scanf("%d%d", &m, &n);
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < m; i++) 
	for(j = 0; j < n; j++)
		if(i == j)
			C[i][j] = 1;
		else
			C[i][j] = 0;
	C = ElementaryCombo(m, n, C, 0, 1, 0.434, 0);	
	for(i = 0; i < m; i++) 
	{
		for(j = 0; j < n; j++)
			printf("%lf ", C[i][j]);
		printf("\n");
	}
		
	for(i = 0; i < m; i++) 
	{
  		 	free(C[i]);
	}
		free(C);
	return 0;
}















