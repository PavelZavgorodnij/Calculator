#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// functions with float
//return 1 if ==, 0 if !=
int cmpstr_simple(char *a, char *b) {
	int la, lb, i;
	la = strlen(a);
	lb = strlen(b);
	if(la != lb)
		return 0;
	for(i = 0; i < la; i++)
		if(a[i] != b[i])
			return 0;
	return 1;
}

int cmpstr_char(char *s, char c) {
	int i, l;
	l = strlen(s);
	for(i = 0; i < l; i++)
		if(s[i] == c)
			return i;
	return 0;
}

char* copy_str(char*s, unsigned int a, unsigned int b) {
	unsigned int l;
	l = strlen(s);
	char*q;
	int i;
	q = (char*)malloc(sizeof(char)*(l + 1));
	if(b >= l)
		b = l-1;
	if(a > b)
	{
		free(q);
		return NULL;
	}
	for(i = a; i <= b; i++)
		q[i-a] = s[i];
	q[b+1-a] = '\0';
	return q;
}

float str_to_float(char*s) {
	int i, l, n, val, sign, first;
	float x = 0;
	l = strlen(s);
	for(i = 0; i < l; i++)
		if(s[i] == '.')
			break;
	if(s[0] == '-')
	{
		sign = -1;
		first = 1;
	}
	else
	{
		sign = 1;
		first = 0;
	}
	n = i-1;
	for(i = first; i <= n; i++)
	{
		val = s[i] - 48;
		x += val*pow(10, (n-i));
	}
	for(i = n+2; i < l; i++)
	{
		val = s[i] - 48;
		x += val*pow(10, (n+1-i));
	}
	return (x*sign);
}

//============HELP===========
void HELP_FUNC() {
	printf("You can use these functions:\n");
	printf("sin(x)\tcos(x)\ttan(x)\tsinh(x)\tcosh(x)\ttanh(x)\n");
	printf("asin(x)\tacos(x)\tatan(x)\texp(x)\tabs(x)\tpow(x)\n");
	printf("x+y\tx-y\tx*y\tx^y\tx/y\t\n");
	printf("ln(x)\tlog(x)\tlogab(x)(y)\tsqrt(x)\n");
	printf("!!! 'x' and 'y' -- are your float numbers !!!\n!!! they shuold be in ()brackets if needed !!!\n");
	printf("help -- you can see all functions\n");
	printf("close -- exit from this process to main calculator menu\n");
}

int process3() {
	char str[1000];
	char *q1, *q2, *q3;
	float x, y;
	int n;
	printf("User->function->  ");
	scanf("%s", str);
	//---sin(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "sin"))
	{
		q2 = copy_str(str, 4, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", sin(x));
		return 1;
	}
	//---cos(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "cos"))
	{
		q2 = copy_str(str, 4, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", cos(x));
		return 1;
	}
	//---tan(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "tan"))
	{
		q2 = copy_str(str, 4, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", tan(x));
		return 1;
	}
	//---sinh(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "sinh"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", sinh(x));
		return 1;
	}
	//---cosh(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "cosh"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", cosh(x));
		return 1;
	}
	//---tanh(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "tanh"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", tanh(x));
		return 1;
	}
	//---asin(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "asin"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		if(abs(x) > 1)
			printf("!!! ERROR! argument module more than 1");
		else
			printf(" = %f\n", asin(x));
		return 1;
	}
	//---acos(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "acos"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		if(abs(x) > 1)
			printf("!!! ERROR! argument module more than 1");
		else
			printf(" = %f\n", acos(x));
		return 1;
	}
	//---atan(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "atan"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", atan(x));
		return 1;
	}
	//---abs(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "abs"))
	{
		q2 = copy_str(str, 4, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", fabs(x));
		return 1;
	}
	//---exp(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "exp"))
	{
		q2 = copy_str(str, 4, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", exp(x));
		return 1;
	}
	//---x^y---
	if((n = cmpstr_char(str, '^')) != 0)
	{
		q1 = copy_str(str, 0, n-1);
		q2 = copy_str(str, n+1, strlen(str));	
		x = str_to_float(q1);
		y = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", pow(x, y));
		return 1;
	}
	//---x+y---
	if((n = cmpstr_char(str, '+')) != 0)
	{
		
		q1 = copy_str(str, 0, n-1);
		q2 = copy_str(str, n+1, strlen(str));	
		x = str_to_float(q1);
		y = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", x+y);
		return 1;
	}
	//---x-y---
	if((n = cmpstr_char(str, '-')) != 0)
	{
		q1 = copy_str(str, 0, n-1);
		q2 = copy_str(str, n+1, strlen(str));	
		x = str_to_float(q1);
		y = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", x-y);
		return 1;
	}
	//---x/y---
	if((n = cmpstr_char(str, '/')) != 0)
	{
		q1 = copy_str(str, 0, n-1);
		q2 = copy_str(str, n+1, strlen(str));	
		x = str_to_float(q1);
		y = str_to_float(q2);
		free(q1);
		free(q2);
		if(y != 0)
			printf(" = %f\n", x/y);
		else
			printf("!!! ERROR! division by 0!\n");
		return 1;
	}
	//---x*y---
	if((n = cmpstr_char(str, '*')) != 0)
	{
		q1 = copy_str(str, 0, n-1);
		q2 = copy_str(str, n+1, strlen(str));	
		x = str_to_float(q1);
		y = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", x*y);
		return 1;
	}
	//---ln(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 1), "ln"))
	{
		q2 = copy_str(str, 3, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		if(x < 0)
			printf("!!! ERROR! the natural logarithm of a negative number\n");
		else
			printf(" = %f\n", log(x));
		return 1;
	}
	//---log(x)---
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "log") && str[3] != 'a')
	{
		q2 = copy_str(str, 4, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		if(x < 0)
			printf("!!! ERROR! the decimal logarithm of a negative number\n");
		else
			printf(" = %f\n", log10(x));
		return 1;
	}
	//---logab(x)(y)--- // x == base
	if(cmpstr_simple(q1 = copy_str(str, 0, 4), "logab"))
	{
		int t = cmpstr_char(str, ')');
		q2 = copy_str(str, 6, t-1);
		q3 = copy_str(str, t+2, strlen(str)-2); 
		x = str_to_float(q2);
		y = str_to_float(q3);
		free(q1);
		free(q2);
		free(q3);
		if(x < 0 || y < 0 || x == 1)
			printf("!!! ERROR! the logarithm of a negative number or the base == 1\n");
		else
			printf(" = %f\n", log(x), log(y), log(y)/log(x));
		return 1;
	}
	//---pow(x)(y)--- <=> x^y
	if(cmpstr_simple(q1 = copy_str(str, 0, 2), "pow"))
	{
		int t = cmpstr_char(str, ')');
		q2 = copy_str(str, 4, t-1);
		q3 = copy_str(str, t+2, strlen(str)-2); 
		x = str_to_float(q2);
		y = str_to_float(q3);
		free(q1);
		free(q2);
		free(q3);
		printf(" = %f\n", pow(x, y));
		return 1;
	}
	//---sqrt(x)--- <=> x^0.5
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "sqrt"))
	{
		q2 = copy_str(str, 5, strlen(str)-2);
		x = str_to_float(q2);
		free(q1);
		free(q2);
		printf(" = %f\n", sqrt(x));
		return 1;
	}
	if(cmpstr_simple(q1 = copy_str(str, 0, 4), "close"))
	{
		free(q1);
		printf("closing...\n");
		return 0;
	}
	if(cmpstr_simple(q1 = copy_str(str, 0, 3), "help"))
	{
		free(q1);
		HELP_FUNC();
		return 1;
	}
	printf("!!! unknown function\n");
	return 1;
}

int FUNCTION(){
	int flag = 1;
	printf("help -- you can see all functions\n");
	while(flag)
		flag = process3();
	return 1;
}
