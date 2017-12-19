#include <stdio.h>
#include <malloc.h>
#include <math.h>
double e;
typedef struct Polynom_{
    double data[10];
    int size;
} Polynom;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

Polynom sump(Polynom a, Polynom b) {
    Polynom c;
    c.size = max(a.size, b.size);
    int i;
    for(i = 0; i <= c.size; i++) {
        c.data[i] = a.data[i] + b.data[i];
        if (c.data[i] < e) c.data[i] = (int)0;
        if ((c.data[i] + 1) < e) c.data[i] = -1;
		if ((c.data[i] - 1) < e) c.data[i] = 1;
    }
    while ((fabs(c.data[c.size]) < e) && c.size >= 0) {
		c.size--;
	}
    return c;
}

Polynom difp(Polynom a, Polynom b) {
    Polynom c;
    c.size = max(a.size, b.size);
    int i;
    for(i = 0; i <= c.size; i++) {
        c.data[i] = a.data[i] - b.data[i];
        if (c.data[i] < e) c.data[i] = (int)0;
        if ((c.data[i] + 1) < e) c.data[i] = -1;
		if ((c.data[i] - 1) < e) c.data[i] = 1;
    }
    while ((fabs(c.data[c.size]) < e) && c.size >= 0) {
		c.size--;
	}
    return c;
}

Polynom multp(Polynom a, Polynom b) {
    Polynom c;
    c.size = a.size + b.size;
    int i, j;
    for(i = 0; i <= a.size; i++) {
        for(j = 0; j <= b.size; j++){
            c.data[i + j] += a.data[i] * b.data[j];
            if (c.data[i + j] < e) c.data[i + j] = 0;
            if ((c.data[i + j] + 1) < e) c.data[i + j] = -1;
			if ((c.data[i + j] - 1) < e) c.data[i + j] = 1;
        }
    }
    return c;
}

void print_polynom(Polynom c) {
	int i;
	if (c.data[c.size]){
		if ((abs(c.data[c.size]) - 1)) printf("%.0lfx^%d", c.data[c.size], c.size);
		else
			if (c.data[c.size] > 0) printf("x^%d ", c.size);
			else printf("-x^%d ", c.size);
		for(i = c.size - 1; i >= 2; i--) {
			if (fabs(c.data[i])){
				if (c.data[i] != 1)
					if (c.data[i] > 0) printf("+ %.0lfx^%d ", c.data[i], i);
					else printf("- %.0lfx^%d ", fabs(c.data[i]), i);
				else 
					if (c.data[i] > 0) printf("+ x^%d ", i);
					else printf("- x^%d ", i);
			}
		}
	}
    if (c.data[1] != 0) {
		if (fabs(c.data[1] != 1))
			if (c.data[1] > 0) printf("+ %.0lfx b", c.data[1]);
			else printf("- %.0lfx ", fabs(c.data[1]));
		else 
			if (c.data[1] > 0) printf("+ x ");
			else printf("- x "); 
	}
    if (c.data[0]) {
		if (c.data[0] > 0) printf("+ %.0lf", c.data[0]);
		else printf("- %.0lf", fabs(c.data[0]));
	}
    printf("\n");
}

int main() {
	int i;
	e = 1;
	for(i = 0; i < 4; i++) {
		e /= 10;
	}
    Polynom a, b, c;
    a.size = 3;
    b.size = 3;
    for(i = 0; i <= 3; i++) {
        a.data[i] = 1;
        b.data[i] = 1;
    }
    b.data[0] = 0;
    c = difp(a, b);
    printf("%d\n", c.size);
    print_polynom(a);
	print_polynom(b);
	print_polynom(c);
    
    return 0;
}

