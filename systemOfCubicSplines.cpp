#include "systemOfCubicSplines.h"

systemOfCubicSplines::systemOfCubicSplines(std::vector<std::pair<double, double>> input)
{
    x_y = input;
    N = x_y.size() - 1;

    c_list = calc_c_list();
    
    list = fill_cubicSpline_list();
}

std::vector<double> systemOfCubicSplines::calc_c_list()

{
    std::vector<double> u; // for CalcUnknown
    std::vector<double> a; // for CalcUnknown
    std::vector<double> c; // for CalcUnknown
    std::vector<double> b; // for CalcUnknown

    this->h_list.push_back(0); // for h[0]

    u.push_back(0); // for u[0]
    u.push_back(get_divided_difference(std::vector<int>{ 0, 1, 2 }) * 6); // for u[1]

    a.push_back(0); // for a[0]
    a.push_back(0); // for a[1]

    c.push_back(0); // for c[0]

    b.push_back(0); // for b[0]

    // compiling var for calculate c_list
    for (int i = 1; i <= N - 2; i++)
    {
        this->h_list.push_back(abs(x_y[i].first - x_y[i - 1].first));
        double x2_x1 = x_y[i + 1].first - x_y[i].first;

        u.push_back(get_divided_difference(std::vector<int> { i, i + 1, i + 2 }) * 6);

        c.push_back(x2_x1 / (this->h_list[i] + x2_x1));

        b.push_back(2);
        if (i > 1)
        {
            a.push_back(this->h_list[i] / (this->h_list[i] + x2_x1));
        }

    }


    this->h_list.push_back(x_y[N - 1].first - x_y[N - 2].first); // for h[N-1]
    this->h_list.push_back(x_y[N].first - x_y[N - 1].first); // for h[N]

    if (N != 2)
    {
        a.push_back(this->h_list[N - 1] / (this->h_list[N - 1] + this->h_list[N])); // for a[N]
    }

    c.push_back(this->h_list[N] / (this->h_list[N - 1] + this->h_list[N])); // for c[N-1]

    b.push_back(2); // for b[N-1]
    b.push_back(2); // for b[N]

    return CalcUnknown(a, b, c, u);
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


std::vector<double> systemOfCubicSplines::CalcUnknown(std::vector<double>& a, std::vector<double>& b, std::vector<double>& c, std::vector<double>& d)
{
    std::vector<double> y;
    std::vector<double> alph;
    std::vector<double> beta;

    int N = d.size() - 1;

    //Задаём стартовые значения (i = 0)
    y.push_back(0);   
    alph.push_back(0);
    beta.push_back(0);

    //Задаём стартовые значения (i = 1)
    y.push_back(b[1]);
    alph.push_back(-c[1] / y[1]);
    beta.push_back(d[1] / y[1]);

    for (int i = 2; i <= N - 1; i++)
    {
        y.push_back(b[i] + a[i] * alph[i - 1]);
        alph.push_back(-c[i] / y[i]);
        beta.push_back((d[i] - a[i] * beta[i - 1]) / y[i]);
    }

    //Задаём конечные значения
    if (N > 0)
    {
        y.push_back(b[N] + a[N] * alph[N - 1]);
        beta.push_back((d[N] - a[N] * beta[N - 1]) / y[N]);
    }

    //N = beta.size() - 1;

    std::vector<double> x(N + 1);

    x[N] = beta[N];

    for (int i = N - 1; i > 0; i--)
    {
        x[i] = alph[i] * x[i + 1] + beta[i];
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