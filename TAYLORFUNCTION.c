#include <stdio.h>
#include <math.h>
double sinx(double x, int n) {
	int i;
	double e;
	e = 1.0;
	for(i = 0; i < n; i++) {
		e /= 10;
	}
	double d = x;
	double u = x;
	double c = 0;
	int k = 1;
	while ( fabs(d - c) > e){
		c = d;
		u = (u * x * x) / ((2 * k + 1) * 2 * k) * (-1);
		d += u;
		k++;
	}
	return d;
}

double sinhx(double x, int n) {
	int i;
	double e;
	e = 1.0;
	for(i = 0; i < n; i++) {
		e /= 10;
	}
	double d = x;
	double u = x;
	double c = 0;
	int k = 1;
	while ( fabs(d - c) > e){
		c = d;
		u = (u * x * x) / ((2 * k + 1) * 2 * k);
		d += u;
		k++;
	}
	return d;
}

double expx(double x, int n) {
	int i;
	double e;
	e = 1.0;
	for(i = 0; i < n; i++) {
		e /= 10;
	}
	double d = 1;
	double u = x;
	double c = 0;
	int k = 0;
	while ( fabs(d - c) > e){
		c = d;
		u = (u * x) / ((k + 1));
		d += u;
		k++;
	}
	return d;
}

double cosx(double x, int n) {
	int i;
	double e;
	e = 1.0;
	for(i = 0; i < n; i++) {
		e /= 10;
	}
	double d = 1;
	double u = 1;
	double c = 0;
	int k = 1;
	while ( fabs(d - c) > e){
		c = d;
		u = (u * x * x) / ((2 * k - 1) * 2 * k) * (-1);
		d += u;
		k++;
	}
	return d;
}

double coshx(double x, int n) {
	int i;
	double e;
	e = 1.0;
	for(i = 0; i < n; i++) {
		e /= 10;
	}
	double d = 1;
	double u = 1;
	double c = 0;
	int k = 1;
	while ( fabs(d - c) > e){
		c = d;
		u = (u * x * x) / ((2 * k - 1) * 2 * k);
		d += u;
		k++;
	}
	return d;
}

double tgx(double x, int n) {
	return(sinx(x, n + 2) / cosx(x, n + 2));
}

double thx(double x, int n) {
	return(sinhx(x, n + 2) / coshx(x, n + 2));
}

double ctgx(double x, int n) {
	return(cosx(x, n + 2) / sinx(x, n + 2));
}

double cthx(double x, int n) {
	return(coshx(x, n + 2) / sinhx(x, n + 2));
}

int TEYLORFUNCTION() {
	double x;
	int n;
	scanf("%lf %d", &x, &n);
	printf("%.11lf", expx(x, n));
	printf("%.11lf", cosx(x, n));
	printf("%.11lf", sinx(x, n));
	printf("%.11lf", coshx(x, n));
	printf("%.11lf", sinhx(x, n));
	printf("%.11lf", tgx(x, n));
	printf("%.11lf", ctgx(x, n));
	printf("%.11lf", tanhx(x, n));
	printf("%.11lf", cthx(x, n));
	return 1;
}
