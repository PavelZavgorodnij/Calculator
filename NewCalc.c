#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char str[1000];
int step;
//---------------------------------------------------------------------------------------------
int NOD( int a, int b)
{
	if(b != 0)
		return NOD(b, a % b);
	else
		return a;
}
//---------------------------------------------------------------------------------------------
struct Frac
{
	int a;
	int b;
	void (*Standardize)(struct Frac*);
};
//---------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------
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
int main()
{
	int lalala;
	FILE *f = fopen("input.txt", "r");
	fscanf(f, "%d", &lalala);
	int i;
	FILE *g;
	g = fopen("NewCalc.out", "w");
	for (i = 0; i < lalala; i ++)
	{
		fscanf(f, "%s", &str);
		struct Frac fa = Process2(0, strlen(str));
		if (fa.b != 1)
			fprintf(g, "%d/%d\n", fa.a, fa.b);
		else
			fprintf(g, "%d\n", fa.a);
		fprintf(g, "\n-------------------------------------------------------------------\n");
	}
	fclose(g);
	return 0;
}
