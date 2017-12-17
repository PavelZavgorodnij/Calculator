#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
//#################################################################################
double Extr(double A, double B, int min)
{
	if((A - B) * min > 0)
		return B;
	else
		return A;
}
//#################################################################################
int mod2(int A)
{
	if(A % 2 == 0)
		return 1;
	else
		return -1;
}
//#################################################################################
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
double Trace(int n, double** A)
{
	double Tr = 0;
	int i;
	for(i = 0; i < n; i ++)
		Tr += A[i][i];
	return Tr;
}
//#########################################################################################
double** Obratnaja(int n, double** A)
{
	double **C;
	C = malloc(n * sizeof(double *));
	int i,j;
	for(i = 0; i < n; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < n; i++) 
		for(j = 0; j < n; j++)
			C[i][j] = A[i][j];
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	double **E;
	E = malloc(n * sizeof(double *));
	for(i = 0; i < n; i++) 
		E[i] = (double *)malloc(n * sizeof(double));
	for(i = 0; i < n; i++) 
		for(j = 0; j < n; j++)
			if (i == j)
				E[i][j] = 1;
			else
				E[i][j] = 0;
	//^^^^^^^^^^^^^^^^^^^pryamoj hod^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	int left = 0;
	int top = 0;
	while (left < n && top < n)
	{
		int left2 = left;
		while (left2 < n)
		{
			int NONULL = 0;
			for(i = top; i < n; i ++)
				if(C[i][left2] != 0)
				{
					NONULL = 1;
					E = ElementarySwap(n, n, E, top, i, 0);
					C = ElementarySwap(n, n, C, top, i, 0);
					E = ElementaryMulty(n, n, E, top, 1 / C[top][left2], 0);					
					C = ElementaryMulty(n, n, C, top, 1 / C[top][left2], 0);
					for(j = top + 1; j < n; j ++)
					{
						E = ElementaryCombo(n, n, E, j, top, - C[j][left2], 0);	
						C = ElementaryCombo(n, n, C, j, top, - C[j][left2], 0);											
					}
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
			for(i = n - 1; i >= 0; i --)
				if(C[i][left2] != 0)
				{
					NONULL = 1;
					for(j = i - 1; j >= 0; j --)
					{
						E = ElementaryCombo(n, n, E, j, i, - C[j][left2], 0);
						C = ElementaryCombo(n, n, C, j, i, - C[j][left2], 0);	
					}
					break;
				}
			left2 --;
			if(NONULL > 0)
				break;
		}
		left = left2;
	}
	//^^^^^^^^^^^^^^^^^^^^^^^^^give back the memory^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	for(i = 0; i < n; i++) 
		for(j = 0; j < n; j++)
			A[i][j] = E[i][j];
	for(i = 0; i < n; i++) 
	{
  		free(E[i]);
	}
	free(E);
	for(i = 0; i < n; i++) 
	{
  		free(C[i]);
	}
	free(C);
	return A;	
}
//#########################################################################################
int MATRIX()
{
	int m, n;
	printf("Enter height and width:  ");
	scanf("%d%d", &m, &n);
	double **C;
	C = malloc(m * sizeof(double *));
	int i,j;
	for(i = 0; i < m; i++) 
		C[i] = (double *)malloc(n * sizeof(double));
	printf("Enter the matrix:\n");
	for(i = 0; i < m; i++) 
		for(j = 0; j < n; j++)
			scanf("%lf", &C[i][j]);	
	printf("\ndet(A) = %lf\n\n", Determinant(n, C));
	printf("Inverse matrix:\n");
	C = Obratnaja(n, C);	
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
	return 1;
}
//#############################################################################
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
//##############################################################################
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
//##############################################################################
int CANONIC()
{
	int N;	
	int y = - 1;
	printf("Enter the number:  ");
	scanf("%d", &N);
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
				printf(" * ");
			printf("%d^%d", i, ar[i]);
		}	
	}
	if (N == 1) 
		printf("1");
	if (N == 0) 
		printf("0");
	printf("\n");
	free(ar);
    return 1;
}
//###################################################################################
char str[1000];
int step;
//###################################################################################
int NOD( int a, int b)
{
	if(b != 0)
		return NOD(b, a % b);
	else
		return a;
}
//###################################################################################
struct Frac
{
	int a;
	int b;
	void (*Standardize)(struct Frac*);
};
//###################################################################################
void Standardize(struct Frac* fff)
{
	if(fff -> b < 0)
	{
		fff -> b = - fff -> b ;
		fff -> a = - fff -> a;
	}
	int nod = NOD(fff -> a, fff -> b);
	fff -> a = fff -> a / nod;
	fff -> b = fff -> b / nod;
}
//###################################################################################
struct Frac HeHe(struct Frac f1, struct Frac f2, int sign)
{
	if(sign == '/')
	{
		struct Frac Result = { f1.a * f2.b, f1.b * f2.a, &Standardize };
		Result.Standardize(&Result);
		return Result;
	}
	if(sign == '*')
	{
		struct Frac Result = { f1.a * f2.a, f1.b * f2.b, &Standardize };
		Result.Standardize(&Result);
		return Result;
	}
	if(sign == '+')
	{
		struct Frac Result = { f1.a * f2.b + f2.a * f1.b, f1.b * f2.b, &Standardize };
		Result.Standardize(&Result);
		return Result;
	}
	if(sign == '-')
	{
		struct Frac Result = { f1.a * f2.b - f2.a * f1.b, f1.b * f2.b, &Standardize };
		Result.Standardize(&Result);
		return Result;
	}
	else 
		return f1;
	
}
//########################################################################################
int priority(int a)
{
	if(a == '+' || a == '-')
		return 1;
	if(a == '*' || a == '/')
		return 2;
	if(a == '^')
		return 3;
	if(a == 'L')
		return 1000;
	else
		return 1000;
}
int Azkaban(int left)
{
	int i = 1;
	while (i)
	{
		if(str[left] == '(')
			i ++;
		if(str[left] == ')')
			i --;
		left++;	
	}
	return left;
}
//###################################################################################
struct Frac Process2(int left, int right)
{
	struct Frac First = { 0, 0, &Standardize };
	struct Frac Second = { 0, 0, &Standardize };
	int sign = 1;
	if(str[left] == '-')
	{
		sign = - 1;
		left ++;	
	}
	if (str[left] == '(')
	{
		left ++;
		int delta = Azkaban(left);
		First = Process2(left, delta-1);
		left = delta;
		First.a *= sign;
	} 
	while (str[left] >= '0' && str[left] <= '9')
	{
		First.b = sign;
		First.a *= 10;
		First.a += str[left] - '0';
		left ++;
	}
	int type;
	if (left < right)
			type = str[left];
	while (left < right)
	{
		int aux = left;
		int auxtype = 'L';
		int sobrat = 0;
		while (!sobrat && aux < right)
		{
			aux ++;
			if (str[aux] == '(')
				aux = Azkaban(aux+1);
			if(aux == right)
				break;
			if (str[aux] == '+' || str[aux] == '*' || str[aux] == '-' || str[aux] == '/' || str[aux] == '^')
				auxtype = str[aux];
			if (priority(auxtype) <= priority(type))
				sobrat = 1;
		}
		if (str[aux-1] == ')' && str[left+1] == '(')
			Second = Process2(left+2, aux-1); 
		else
			Second = Process2(left+1, aux);
		left = aux;	
		if(Second.b != 0)
		{
			First = HeHe(First, Second, type);
			Second.a = 0;
			Second.b = 0;			
		}
			if (left < right)
				type = str[left];
	}
	First.Standardize(&First);
	return First;
}
//---------------------------------------------------------------------------------------------
int CALC()
{
	printf("Enter numeric expression:  ");
	scanf("%s", str);
	printf("\n");
	struct Frac fa = Process2(0, strlen(str));
	if (fa.b != 1)
		printf("%d/%d\n", fa.a, fa.b);
	else
		printf("%d\n", fa.a);
	return 1;
}




