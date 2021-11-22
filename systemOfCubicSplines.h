#ifndef SYSTEMOFCUBICSPLINES_H
#define SYSTEMOFCUBICSPLINES_H

#include "cubicSpline.h"
#include <vector>

class systemOfCubicSplines
{
private:
	std::vector<std::pair<double, double>> x_y;
	int N;

	std::vector<cubicSpline> list;

	std::vector<double> h_list;
	std::vector<double> c_list;

	std::vector<double> calc_c_list();
	std::vector<double> calc_c_list2();
	std::vector<cubicSpline> fill_cubicSpline_list();

	double get_divided_difference(std::vector<int> indexes);

public:
	systemOfCubicSplines(std::vector<std::pair<double, double>> input);
	std::vector<cubicSpline> getCubicSplineList() { return list; }
};

#endif // SYSTEMOFCUBICSPLINES_H