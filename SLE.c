#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------------------
//gauss algoritm to search the solution of systems of linear equations
//also search the rang of matrix


int gauss_right(float **a, int *J, int m, int n);
void gauss_back(float **a, int *J, int m, int n, int r);
int test_0_column(float **a, int m,  int j, int m1);
void revers_strings(float **a, int n, int i1, int i2);
void comp_string(float **a, int n, int i, float l);
void sum_strings(float **a, int n, int i1, int i2, float l);
void print_matrix(FILE* f, float **a, int m, int n);
void scan_matrix(FILE* f, float **a, int m, int n);
int test_matrix_0(float **a, int m, int n);  /* without the last column!!! */
void print_solutions(FILE* f, float **a, int *J, int m, int n, int r);

int SLE() {
    FILE *fin, *fout;
    float **a;
	int *J; /* array of numbers of columns j which are not include in E matrix*/
	int m, n;  /* m - number of equations ||| n - number of variables*/
    int i, rang;
    int flag = 0;
    char str[1000];
    //===========
    printf("where is information about SLE?\nWrite the file name or write # to write SLE in standart input\n");
    while(flag == 0)
    {
    	scanf("%s", str);
    	if(str[0] == '#')
    	{
    		flag = 1;
    		fin = stdin;
    		break;
    	}
    	fin = fopen(str, "r");
    	if(fin == NULL)
    		printf("there is not file named %s\nTry again\n", str);
    	else
    		flag = 2;
	}
    //===========
    if(flag == 1)
    {
    	printf("write number of equations and number of variables\n");
    	printf("then write the coefficients in the order:\nfor the first equation:\n");
    	printf("coefficients of the equation for variables, free term;\nthen for the next equation...\n");
    	printf("for example: for the equations:\nx+2y+3z = 0\n6x-3y=10\n ");
    	printf("you should write:\n1 2 3 0\n6 -3 0 10\n");
    	printf("please, write number of equations and number of variables\n");
	}
    //===========
    putchar('\n');
    fscanf(fin, "%d %d", &m, &n);
    a = malloc(sizeof(float*)*m);
    J = malloc(sizeof(float)*n);
    for(i = 0; i < n; i++)
    	J[i] = -1;
	for(i = 0; i < m; i++)
    	a[i] = malloc(sizeof(float)*(n + 1));
    //===========
    scan_matrix(fin, a, m, n);
	rang = gauss_right(a, J, m, n);
	gauss_back(a, J, m, n, rang);
	//===========
	printf("where to print solutions?\nWrite the file name or write # to print solutions in standart output\n");
    scanf("%s", str);
    if(str[0] == '#')
    	fout = stdout;
    else
    	fout = fopen(str, "w");
    //===========
    if(rang == 0 && test_0_column(a, m, n, 0) == 0)
		fprintf(fout, "R - all real numbers\n");
	else
		if(test_matrix_0(a, m, n) == 0)
			fprintf(fout, "No solutions\n");
		else
			print_solutions(fout, a, J, m, n, rang);
	//===========
	for(i = 0; i < m; i++)
		free(a[i]);
    free(a);
    free(J);
    if(fin != stdin)
    	fclose(fin);
    if(fout != stdout)
    	fclose(fout);
    return 1;
}

int gauss_right(float **a, int *J, int m, int n) {
	int k, j, i;
	for(k = 0; k < n, k < m; k++) 
	{
		for(j = k; j < n; j++)
			if(test_0_column(a, m, j, k)) break;
		if(j == n) break;	
		for(i = k; i < m; i++)
			if(a[i][j] != 0)
			{
				revers_strings(a, n, i, k);
				break;
			}
		J[k] = j;
		comp_string(a, n, k, 1/a[k][j]);
		for(i = k + 1; i < m; i++)
			sum_strings(a, n, i, k, -a[i][j]);	
	}
	return k;
}

void gauss_back(float **a, int *J, int m, int n, int r) {
	int k, j, i;
	for(k = r-1; k >= 0; k--)
		{
			comp_string(a, n, k, 1/a[k][J[k]]);
			for(i = k-1; i >= 0; i--)
				sum_strings(a, n, i, k, -a[i][J[k]]);
		}
}

int test_0_column(float **a, int m, int j, int m1) {
	int i, count = 0;
	for(i = m1; i < m; i++)
		if(a[i][j] != 0)  count++;
	return count;
}

void revers_strings(float **a, int n, int i1, int i2) {
	int j;
	float b;
	for(j = 0; j <= n; j++)
	{
		b = a[i1][j];
		a[i1][j] = a[i2][j];
		a[i2][j] = b;
	}
}

void comp_string(float **a, int n, int i, float l) {
	int j;
	for(j = 0; j <= n; j++)
		a[i][j] *= l;
}

void sum_strings(float **a, int n, int i1, int i2, float l) {
	int j;
	for(j = 0; j <= n; j++)
		a[i1][j] += a[i2][j]*l;
}

void print_matrix(FILE* f, float **a, int m, int n) {
int i, j;
	for(i = 0; i < m; i++)
	{
		fprintf(f, "||\t%f\t", a[i][0]);
		for(j = 1; j < n; j++)
			printf("%f\t", a[i][j]);
		fprintf(f, "|  %f\t||\n", a[i][n]);	
	}
}

void scan_matrix(FILE *f, float **a, int m, int n) {
	if(f == stdin)
		printf("write the coefficients...\n");
	int i, j;
	for(i = 0; i < m; i++)
		for(j = 0; j < n+1; j++)
			fscanf(f, "%f", &a[i][j]);
}

int test_matrix_0(float **a, int m, int n) {
	int i, j, count = 0;
	for(i = 0; i < m; i++)
	{
		count = 0;
		for(j = 0; j < n; j++)
			if(a[i][j] != 0) count++;
		if(count == 0 && a[i][n] != 0) return 0;
	}
	return 1;
}

void print_solutions(FILE* f, float **a, int *J, int m, int n, int r){
	int i, j, k = 0, d;
	float** b = malloc(sizeof(float*)*n);
	for(j = 0; j < n; j++)
		b[j] = malloc(sizeof(float)*(n-r+1));
	/* make supporting matrix*/
	for(i = 0; i < n; i++)
		if(i == J[k])
		{
			d = 0;
			for(j = 0; j < n; j++)
				if(j != J[d])
					b[i][j - d] = -a[i][j];
				else
					d++;
			b[i][n-r] = a[k][n];
			k++;
		}
		else
		{
			for(j = 0; j < n; j++)
				b[i][j] = 0;
			b[i][n-r] = 0;
			b[i][i-k] = 1;
		}	
	/* printing solutions with supporting matrix */
	for(i = 0; i < n; i++)
	{
		printf(" x%d = ", i+1);
		for(j = 0; j < n - r; j++)
		{
			if(b[i][j] > 0)
				printf(" + %f * t%d", b[i][j], j+1);
			if(b[i][j] < 0)
				printf(" - %f * t%d", -b[i][j], j+1);
		}
		if(b[i][n-r] >= 0)
			printf(" + %f\n", b[i][n-r]);
		if(b[i][n-r] < 0)
			printf(" - %f\n", -b[i][n-r]);
	}
	for(i = 0; i < n; i++)
		free(b[i]);
	free(b);
}
