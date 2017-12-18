#include <stdlib.h>
#include <stdio.h>
int prst(int p);
int CANONIC_2() {
    int n, last, i, a, j = 0, *A, *B;
    printf("write the number:  ");
    scanf("%d", &n);
    last = n;
    A = malloc(sizeof(int)*n);
    B = malloc(sizeof(int)*n);
    for(i = 2; i<= n; i++)
    { 
        if( prst(i) == 1)
        {
            a = 0;
            while (n%i == 0)
            {
                n /= i;
                a++;
            }
            if(a != 0)
            {
                A[j] = i; /* factor */
                B[j] = a; /* degree */
                j++;
            }
        }
    }
    printf("%d = ", last);
    for(i = 0; i<j; i++)
    {
        if (i != (j-1)) printf("%d^%d * ", A[i], B[i]);
        else  printf("%d^%d\n", A[i], B[i]);
    }
    free(A);
    free(B);
    return 1;
}

int prst(int p) /*check for simple number*/
{
    int i, flag = 1;
    for (i = 2; i<p; i++)
        if (p%i == 0) return (flag = 0);
    return(flag);
}
