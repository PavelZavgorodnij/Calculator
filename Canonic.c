#include <stdio.h>
#include <malloc.h>
//----------------------------------------------------------------------------------
int* Eratosphen(int N)
{
	int *A; 
	A = malloc (sizeof(int) * (N + 1));
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

int main ()
{
	int lalala;
	int N;
	FILE *f = fopen("input.txt", "r");
	fscanf(f, "%d", &lalala);
	FILE *g;
	g = fopen("Canonic.out", "w");
	int ik;
	for (ik = 0; ik < lalala; ik ++)
	{	
		int y = - 1;
		fscanf(f, "%d", &N);
		int *ar = SimpleDivisirs(N);
		int i;
		for ( i = 2; i <= N; i ++ ) 
		{
			if(ar[i] > 0)
			{
				if(y < 0)
				{
					y = 2;
				}
				else
					fprintf(g, " * ");
				fprintf(g, "%d^%d", i, ar[i]);
			}	
		}
		if (N == 1) 
			fprintf(g, "1");
		if (N == 0) 
			fprintf(g, "0");
		fprintf(g, "\n-------------------------------------------------------------------\n");
		free(ar);
	}	
	fclose(g);	
    return 0;
}
