#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define L0 10000
int Allocs;
int Frees;
//#################################################################################
int Min(int A, int B)
{
	if(A < B)
		return A;
	else
		return B;
}
//#########################################
int Max(int A, int B)
{
	if(A < B)
		return B;
	else
		return A;
}
//#########################################
struct Stack_
{
	int N;
	int P;
	int *Data;
	
};
typedef struct Stack_ Stack;
//###########################################################
Stack* InitStack(int N)
{
	Stack* New = (Stack*)malloc(sizeof(Stack));
	New -> N = N;
	New -> P = 0;
	New -> Data = (int*)malloc(N * sizeof(int));
	Allocs += 2;
	return New;
}
//###########################################################
void FreeStack(Stack *MyStack)
{
	free (MyStack -> Data);
	free (MyStack);
	Frees += 2;
}
//###########################################################
int PushStack(Stack* A, int Val)
{
	if(A -> P == A -> N)
		return 1;
	else
	{
		A -> Data[A -> P] = Val;
		A -> P ++;
	}
	return 0;
}
//###########################################################
int PopStack(Stack* A)
{
	if(A -> P > 0)
	{
		A -> P --;
		return 0;
	}
	else
		return 1;
}
//###########################################################
void PrintStack(Stack* A)
{
	int i;
	for (i = 0; i < A -> P; i ++)
		printf("%d", A -> Data[i]);
}
//###########################################################
void Inversia(Stack* A)
{
	int Aux;
	int i;
	for(i = 0; i < A -> P / 2; i ++)
	{
		Aux = A -> Data[A -> P - i - 1];
		A -> Data[A -> P - i - 1] = A -> Data[i];
		A -> Data[i] = Aux;	
	}
}
//###########################################################
Stack* FromString(char* Str)
{
	Stack* Ans = InitStack(strlen(Str) + 1);
	int i;
	for(i = 0; i < strlen(Str); i ++)
		PushStack(Ans, Str[i] - '0');
	return Ans;
}
//############################################################################
Stack* Summ(Stack* A, Stack* B)
{
	Stack* Ans = InitStack(A -> N + B -> N + 1);
	int InBrain = 0;
	int i;
	int MIN = Min(A -> P, B -> P);
	int MAX = Max(A -> P, B -> P);
	for(i = 0; i < MIN; i ++)
	{
		PushStack(Ans, (A -> Data[i] + B -> Data[i] + InBrain) % 10);
		InBrain = (A -> Data[i] + B -> Data[i] + InBrain) / 10;
	}
	for(i = MIN; i < MAX; i ++)
		if(MAX == B -> P)
		{
			PushStack(Ans, (B -> Data[i] + InBrain) % 10);
			InBrain = (B -> Data[i] + InBrain) / 10;
		}
		else
		{
			PushStack(Ans, (A -> Data[i] + InBrain) % 10);
			InBrain = (A -> Data[i] + InBrain) / 10;
		}
	if(InBrain > 0)
		PushStack(Ans, InBrain);
	return Ans;
}
//#############################################################################
Stack* AuxMult(Stack* A, int B, int Step)
{
	Stack* Ans = InitStack(A -> P + 1 + Step);
	int InBrain = 0;
	int i;
	for(i = 0; i < Step; i ++)
		PushStack(Ans, 0);
	for(i = 0; i < A -> P; i ++)
	{
		PushStack(Ans, (A -> Data[i] * B + InBrain) % 10);
		InBrain = (A -> Data[i] * B + InBrain) / 10;
	}
	if(InBrain > 0)
		PushStack(Ans, InBrain);	
	return Ans;
}
//#############################################################################
Stack* Multiply(Stack* A, Stack* B)
{
	Stack* Ans = InitStack(A -> P + 1 + B -> P);
	Ans -> P = 1;
	Ans -> Data[0] = 0;
	int i = 0;
	for(i = 0; i < B -> P; i ++)
	{
		Stack* Aux1 = AuxMult(A, B -> Data[i], i);
		Stack* Aux2 = Summ(Aux1, Ans);
		FreeStack(Ans);
		Ans = Aux2;
		FreeStack(Aux1);
	}
	return Ans;	
}
//##############################################################################
Stack* Degree(Stack* A, int Deg)
{
	Stack* Ans = AuxMult(A, 1, 0);
	int i;
	for(i = 1; i < Deg; i ++)
	{
		Stack* Aux = Multiply(Ans, A);
		FreeStack(Ans);
		Ans = Aux;
	}
	return Ans;
}
//##############################################################################
int Compare(Stack* A, Stack* B, int Step)
{
	if(A -> P == B -> P)
		if(A -> Data[A -> P - Step] > B -> Data[A -> P - Step])
			return 1;
		else
			if(A -> Data[A -> P - Step] < B -> Data[A -> P - Step])
				return -1;
			else
				if(A -> P > 1)
					return Compare(A, B, Step + 1);
				else
					return 0;
	else if(A -> P > B -> P)
		return 1;
	return -1;
}
//##############################################################################
Stack* Difference(Stack* A, Stack* B)
{
	Stack* Ans = InitStack(A -> P);
	int InBrain = 0;
	int i;
	int MIN = Min(A -> P, B -> P);
	int MAX = Max(A -> P, B -> P);
	for(i = 0; i < MIN; i ++)
	{
		if(A -> Data[i] - B -> Data[i] - InBrain >= 0)
		{
			PushStack(Ans, A -> Data[i] - B -> Data[i] - InBrain);
			InBrain = 0;	
		}
		else
		{
			PushStack(Ans, 10 + A -> Data[i] - B -> Data[i] - InBrain);
			InBrain = 1;		
		}
	}
	for(i = MIN; i < MAX; i ++)
		if(MAX == B -> P)
			if(A -> Data[i] - InBrain >= 0)
			{
				PushStack(Ans, A -> Data[i] - InBrain);
				InBrain = 0;	
			}
			else
			{
				PushStack(Ans, 10 + A -> Data[i] - InBrain);
				InBrain = 1;		
			}
		else
			if(B -> Data[i] - InBrain >= 0)
			{
				PushStack(Ans, B -> Data[i] - InBrain);
				InBrain = 0;	
			}
			else
			{
				PushStack(Ans, 10 + B -> Data[i] - InBrain);
				InBrain = 1;		
			}
	return Ans;
}
//#########################################################################
int LONG()
{
	char* A = (char*)malloc(L0 * sizeof(char));
	char* B = (char*)malloc(L0 * sizeof(char));
	Allocs += 2;
	Frees += 2;
	printf("Enter first number: ");
	scanf("%s", A);
	printf("Enter second number: ");
	scanf("%s", B);
	Stack* MA = FromString(A);
	Stack* MB = FromString(B);
	Inversia(MA);
	Inversia(MB);
	Stack* MC;
	printf("Summ: ");
	MC = Summ(MA, MB);
	Inversia(MC);
	PrintStack(MC);
	FreeStack(MC);
	printf("\nMultiply: ");
	MC = Multiply(MA, MB);
	Inversia(MC);
	PrintStack(MC);
	FreeStack(MC);
	printf("\nDegree: ");
	MC = Degree(MA, 40);
	Inversia(MC);
	PrintStack(MC);
	FreeStack(MC);
	printf("\nRaznost': ");
	MC = Difference(MA, MB);
	Inversia(MC);
	PrintStack(MC);
	FreeStack(MC);	
	free(A);
	free(B);
	FreeStack(MA);
	FreeStack(MB);
	printf("\n");
	return 1;
}
