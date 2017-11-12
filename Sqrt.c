#include <stdio.h>
#include <malloc.h>
//----------------------------------------------------------------------------------
int* Eratosphen(int N)
{
	int *A; 
	A = malloc (sizeof(int) * N + 1);
	int i;
	for ( i = 2; i <= N; i ++ ) 
		A[i] = 1;
	int k = 2; 
	while ( k*k <= N ) 
	{ 
		if ( A[k] ) 
		{ 
			i = k*k; 
			while ( i <= N ) 
			{ 
				A[i] = -1; 
				i += k; 
			} 
		} 
		k ++; 
	}
	return A;
}
//---------------------------------------------------------------------------------
int* SimpleDivisirs(int N)
{
	int *A = Eratosphen(N);
	int M = N;
	int i;
	for ( i = 2; i <= N; i ++ ) 
	{
		if(A[i] > 0)
		{	
			A[i] = 0;
			while (M % i == 0)
			{
			A[i] ++;
			M /= i;
			}
		}
		
	}
	return A;
}
//---------------------------------------------------------------------------------
int Stepenj (int osn, int pok)
{
	int ASA;
	ASA = 1;
	int iii;
	for(iii = 1; iii <= pok; iii ++)
	{
		ASA *= osn;	
	}
	return ASA;
}
//---------------------------------------------------------------------------------
int* Irrational(int N, int grade)
{
	int* A = SimpleDivisirs(N);
	int *B; 
	B = malloc (sizeof(int) * 2);
	B[0] = 1;
	B[1] = 1;
	int i;
	for ( i = 2; i <= N; i ++ ) 
	{
		if(A[i] > 0)
		{
			if(A[i] % grade != 0)
			{
				B[1] *= Stepenj(i, A[i] % grade);
				A[i] -= A[i] % grade;
			}
			A[i] /= grade;
			int l;
			for (l = 0; l < A[i]; l ++)
			{
			B[0] *= i;	
			}
				
		}
	}
	return B;	
}
//------------------------------------------------------------------------------
int main ()
{
	int lalala;
	FILE *f = fopen("input2.txt", "r");
	fscanf(f, "%d", &lalala);
	int i;
	FILE *g;
	g = fopen("Sqrt.out", "w");
	for (i = 0; i < lalala; i ++)
	{
		int N;
		int SAS;
		fscanf(f, "%d%d", &N, &SAS);
		int *ar = SimpleDivisirs(N);
		int *Runduc = Irrational(N, SAS);
		if(Runduc[0] != 1) 
			fprintf(g, "%d", Runduc[0]);
		if(Runduc[0] != 1 && Runduc[1] != 1)
			fprintf(g, "*");
		if(Runduc[0] == 1 && Runduc[1] == 1)
			fprintf(g, "1");
		if(Runduc[1] != 1)
			fprintf(g, "(%d)^1/%d ", Runduc[1], SAS);
		fprintf(g, "\n-------------------------------------------------------------------\n");
		free(ar);
		free(Runduc);
	}	
	fclose(g);
    return 0;
}
