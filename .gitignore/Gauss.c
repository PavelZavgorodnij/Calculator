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
int mod2(int A)
{
	if(A % 2 == 0)
		return 1;
	else
		return -1;
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
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			A[i][j] = C[i][j];
	for(i = 0; i < m; i++) 
	{
  		 	free(C[i]);
	}
	free(C);
	return A;	
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
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			A[i][j] = C[i][j];
	for(i = 0; i < m; i++) 
	{
  		 	free(C[i]);
	}
	free(C);
	return A;	
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
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			A[i][j] = C[i][j];
	for(i = 0; i < m; i++) 
	{
  		 	free(C[i]);
	}
	free(C);
	return A;	
}
//###################################################################################
double** Gauss(int m, int n, double** A)
{
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			C[i][j] = A[i][j];
	//^^^^^^^^^^^^^^^^^^^pryamoj hod^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	int left = 0;
	int top = 0;
	while (left < n && top < m)
	{
		int left2 = left;
		while (left2 < n)
		{
			int NONULL = 0;
			for(i = top; i < m; i ++)
				if(C[i][left2] != 0)
				{
					NONULL = 1;
					C = ElementarySwap(m, n, C, top, i, 0);
					C = ElementaryMulty(m, n, C, top, 1 / C[top][left2], 0);
					for(j = top + 1; j < m; j ++)
						C = ElementaryCombo(m, n, C, j, top, - C[j][left2], 0);
					break;
				}
			left2 ++;
			if(NONULL > 0)
				break;
		}
		left = left2;
		top ++;	
	}
	//^^^^^^^^^^^^^^^^^^^^^^^^^obratnij hod^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	left = n - 1;
	while (left >= 0)
	{
		int left2 = left;
		while (left2 >= 0)
		{
			int NONULL = 0;
			for(i = m - 1; i >= 0; i --)
				if(C[i][left2] != 0)
				{
					NONULL = 1;
					for(j = i - 1; j >= 0; j --)
						C = ElementaryCombo(m, n, C, j, i, - C[j][left2], 0);
					break;
				}
			left2 --;
			if(NONULL > 0)
				break;
		}
		left = left2;
	}
	//^^^^^^^^^^^^^^^^^^^^^^^^^give back the memory^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			A[i][j] = C[i][j];
	for(i = 0; i < m; i++) 
	{
  		 	free(C[i]);
	}
	free(C);
	return A;	
}
//#########################################################################################
int MatrixRange(int m, int n, double** A)
{
	int Ans = 0;
	A = Gauss(m, n, A);
	int left = 0;
	int top = 0;
	while (left < n && top < m)
	{
		int i;
		for (i = left; i < n; i ++)
			if(A[top][i] != 0)
			{
				Ans ++;
				left = i + 1;
				break;
			}
		top ++;
	}
	return Ans;
}
//#########################################################################################
double** Minor(int m, int n, double** A, int stolb, int stroka)
{
	double **C;
	C = malloc((m - 1) * sizeof(double *));
	int i,j;
	for(i = 0; i < m - 1; i++) 
		C[i] = (double *)malloc((n - 1) * sizeof(double));
	int SKIPY = 0;
	for(i = 0; i < m; i++) 
	{
		int SKIPX = 0;
		if(i != stroka)
			for(j = 0; j < n; j++)
				if(j != stolb)
					C[i - SKIPY][j - SKIPX] = A[i][j];	
				else
					SKIPX = 1;	
		else
			SKIPY = 1;
	}
	return C;	
}
//##########################################################################################
double Determinant(int n, double** A)
{
	double Det = 0;
	int i;
	for(i = 0; i < n; i ++)
	{
		if(n > 1)
		{
			double** Mina = Minor(n, n, A, i, 0);
			Det += (double)mod2(i) * A[0][i] * Determinant(n - 1, Mina);	
			int ii;
			for(ii = 0; ii < n - 1; ii ++) 
			{
				free(Mina[ii]);
			}
			free(Mina);
		}
		else
			Det = A[0][0];

	}
	return Det;
	
}
//#########################################################################################
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
			scanf("%lf", &C[i][j]);	
	printf("\ndet(A) = %lf\n\n", Determinant(n, C));
	C = Gauss(m, n, C);	
	for(i = 0; i < m; i++) 
	{
		for(j = 0; j < n; j++)
			printf("%lf ", C[i][j]);
		printf("\n");
	}
	printf("\n");
	printf("rg(A) = %d", MatrixRange(m, n, C));
	printf("\n\n");
	for(i = 0; i < m; i++) 
	{
  		 	free(C[i]);
	}
		free(C);
	return 0;
}















