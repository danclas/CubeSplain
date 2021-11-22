#include "systemOfCubicSplines.h"

systemOfCubicSplines::systemOfCubicSplines(std::vector<std::pair<double, double>> input)
{
    x_y = input;
    N = x_y.size() - 1;

    c_list = calc_c_list();

    if (c_list==calc_c_list2())
    {
        int g = 0;
    }
    
    list = fill_cubicSpline_list();
}

double systemOfCubicSplines::get_divided_difference(std::vector<int> indexes)
{
    std::vector<int> left_indexes = indexes;
    left_indexes.erase(left_indexes.begin());
    std::vector<int> right_indexes = indexes;
    right_indexes.pop_back();

    if (indexes.size() > 1)
    {
        int left_index = *(indexes.rbegin());
        int right_index = *(indexes.begin());

        double temp = (get_divided_difference(left_indexes) - get_divided_difference(right_indexes)) / 
                      (x_y[left_index].first - x_y[right_index].first);
        return temp;
    }
    else
    {
        if (indexes.size() == 1)
        {
            return x_y[indexes[0]].second;
        }
    }
    
    
    
}


std::vector<double> systemOfCubicSplines::calc_c_list()
{
    std::vector<double> y;
    std::vector<double> alph;
    std::vector<double> beta;


    //Задаём стартовые значения (i = 0)
    y.push_back(0);
    alph.push_back(0);
    beta.push_back(0);
    this->h_list.push_back(0);

    //Задаём стартовые значения (i = 1)
    this->h_list.push_back(x_y[1].first - x_y[0].first);
    this->h_list.push_back(x_y[2].first - x_y[1].first); // for i = 2
    y.push_back(2);
    alph.push_back(3 * get_divided_difference(std::vector<int>{0, 1, 2}));
    beta.push_back((-this->h_list[2] / (this->h_list[2] + this->h_list[1])) / 2); // (-h[2]/(h[2]+h[1]))/2

    for (int i = 2; i <= N - 1; i++)
    {
        this->h_list.push_back(x_y[i + 1].first - x_y[i].first);
        y.push_back(this->h_list[i] / (this->h_list[i] + this->h_list[i + 1]));
        alph.push_back((6 * get_divided_difference(std::vector<int>{i - 1, i, i + 1}) - y[i] * alph[i - 1]) / (2 + y[i] * beta[i - 1]));
        if (i == N - 1)
        {
            beta.push_back(0);
        }
        else
        {
            beta.push_back(-this->h_list[i + 1] / (2 * this->h_list[i + 1] + 2 * this->h_list[i] + this->h_list[i] * beta[i - 1]));
        }
    }

    std::vector<double> x(N);

    x[N-1] = alph[N-1];

    for (int i = N - 2; i > 0; i--)
    {
        x[i] = beta[i] * x[i + 1] + alph[i];
    }

    //std::reverse(x.begin(), x.end());
    x.push_back(0);

    return x;
}

std::vector<cubicSpline> systemOfCubicSplines::fill_cubicSpline_list()
{

    std::vector<double> a_list(N + 1);
    std::vector<double> b_list(N + 1);
    std::vector<double> d_list(N + 1);
    std::vector<cubicSpline> res;

    a_list[0] = get_divided_difference(std::vector<int> {0}); // for a[0]
    a_list[1] = get_divided_difference(std::vector<int> {1}); // for a[1]

    b_list[0] = 0;                                                                                       // for b[0]
    b_list[1] = this->c_list[1] * this->h_list[1] / 3 + get_divided_difference(std::vector<int>{0, 1});  // for b[1]

    d_list[0] = 0;                                  // for d[0]
    d_list[1] = this->c_list[1] / this->h_list[1];  // for d[0]

    //this->list.push_back(cubicSpline(0, 0, 0, 0, 0, 0));

    res.push_back(cubicSpline(a_list[1], b_list[1], this->c_list[1], d_list[1], this->x_y[0].first, this->x_y[1].first)); // for list[1]

    for (int i = 2; i <= N; i++)
    {
        a_list[i] = get_divided_difference(std::vector<int> {i});

        b_list[i] = this->c_list[i] * this->h_list[i] / 3 +
            this->c_list[i - 1] * this->h_list[i] / 6 +
            get_divided_difference(std::vector<int>{i - 1, i});

        d_list[i] = (this->c_list[i] - this->c_list[i - 1]) / this->h_list[i];

        res.push_back(cubicSpline(a_list[i], b_list[i], this->c_list[i], d_list[i], this->x_y[i - 1].first, this->x_y[i].first));
    }

    return res;
}

std::vector<double> systemOfCubicSplines::calc_c_list2()
{
    std::vector<double> y;
    std::vector<double> alph;
    std::vector<double> beta;


    //Задаём стартовые значения (i = 0)
    y.push_back(0);
    alph.push_back(0);
    beta.push_back(0);
    this->h_list.push_back(0);

    //Задаём стартовые значения (i = 1)
    this->h_list.push_back(x_y[1].first - x_y[0].first);
    this->h_list.push_back(x_y[2].first - x_y[1].first); // for i = 2
    y.push_back(2);
    alph.push_back(3 * get_divided_difference(std::vector<int>{0, 1, 2}));
    beta.push_back(-this->h_list[2] / ((this->h_list[2] + this->h_list[1]) * 2)); // (-h[2]/(h[2]+h[1]))/2

    for (int i = 2; i <= N - 1; i++)
    {
        this->h_list.push_back(x_y[i + 1].first - x_y[i].first);
        y.push_back(2*(this->h_list[i+1] + this->h_list[i])+ this->h_list[i]*beta[i-1]);
        alph.push_back(((6 * get_divided_difference(std::vector<int>{i - 1, i, i + 1}))* (this->h_list[i + 1] + this->h_list[i]) - this->h_list[i] * alph[i - 1]) / y[i]);
        if (i == N - 1)
        {
            beta.push_back(0);
        }
        else
        {
            beta.push_back(-this->h_list[i + 1] / y[i]);
        }
    }

    std::vector<double> x(N);

    x[N - 1] = alph[N - 1];

    for (int i = N - 2; i > 0; i--)
    {
        x[i] = beta[i] * x[i + 1] + alph[i];
    }

    //std::reverse(x.begin(), x.end());
    x.push_back(0);

    return x;
}