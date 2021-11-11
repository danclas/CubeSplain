#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

class cubicSpline
{
private:
	double a;
	double b;
	double c;
	double d;
	double x1;
	double x2;
public:
	cubicSpline(double _a, double _b, double _c, double _d, double _x1, double _x2) : a(_a), b(_b), c(_c), d(_d), x1(_x1), x2(_x2) {}
	double F(double x)
	{
		return a + b * (x - x2) + c / 2 * (x - x2) * (x - x2) + d / 6 * (x - x2) * (x - x2) * (x - x2);
	}
	double get_x1() { return x1; }
	double get_x2() { return x2; }
};

#endif // CUBICSPLINE_H