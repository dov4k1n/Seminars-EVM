typedef struct point{
	double x, y;
} point;

double f1(double x);

double f2(double x);

double f3(double x);

double f4(double x);

double f5(double x);

double f6(double x);

void choose(double (**f)(double x), int m);

void getpoints(int m, double(*f)(double x), FILE *out, int n);

void load(point *p, FILE *in, int n);

double piecewiselinear(point *p, int n, double x);
