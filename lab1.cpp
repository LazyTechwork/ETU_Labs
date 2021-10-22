#include "labs.h"

std::vector<unsigned long long> factorials = {1};

const double PI = 3.1415926;

unsigned int resolve_quarter(double angle) {
    unsigned int quarter = std::ceil((angle) / (PI / 2));
    if (std::fmod(angle, PI / 2) == 0)
        quarter++;
    if (quarter > 4)
        quarter = quarter % 4 == 0 ? 4 : quarter % 3 == 0 ? 3 : quarter % 2 == 0 ? 2 : 1;
    return quarter;
}

unsigned long long fact(unsigned long long x) {
    if (factorials.size() - 1 >= x)
        return factorials[x];

    unsigned long long result = factorials[factorials.size() - 1];
    for (unsigned int i = factorials.size(); i <= x; ++i) {
        result *= i;
        factorials.push_back(result);
    }
    return result;
}

double pow(double x, int n) {
    double result = 1.0;
    for (int i = 1; i <= n; ++i)
        result *= x;

    return result;
}

double e_x(double x) {
    double result = 1.0f;
    for (int i = 1; i <= 20; ++i) {
        result += pow(x, i) / fact(i);
    }
    return result;
}

double sqrt(double x) {
    double result[20] = {1};
    for (int i = 1; i < 20; ++i)
        result[i] = 0.5 * (result[i - 1] + x / result[i - 1]);

    return result[19];
}

double convert_angle(double x) {
    x -= x > PI * 2 ? std::floor(x / (PI * 2)) * (PI * 2) : 0;
    const unsigned int quarter = resolve_quarter(x);
    if (quarter == 1)
        return x;
    if (quarter == 2)
        return PI - x;
    if (quarter == 3)
        return x - PI;
    if (quarter == 4)
        return 2.0 * PI - x;
    return 0;
}

double sin(double x) {
    const unsigned int quarter = resolve_quarter(x);
    x = convert_angle(x);
    double result = x;
    for (int i = 1; i <= 20; ++i)
        result += (pow(-1, i) * pow(x, 2 * i + 1)) / fact(2 * i + 1);

    return result * (quarter == 3 || quarter == 4 ? -1 : 1);
}

double cos(double x) {
    const unsigned int quarter = resolve_quarter(x);
    x = convert_angle(x);
    double result = 1;
    for (int i = 1; i <= 20; ++i)
        result += (pow(-1, i) * pow(x, 2 * i)) / fact(2 * i);

    return result * (quarter == 2 || quarter == 3 ? -1 : 1);
}

double atg(double x) {
    double result = x;
    for (int i = 1; i <= 20; ++i)
        result += (pow(-1, i - 1) * pow(x, 2 * i - 1)) / (2 * i - 1);

    return result - 1;
}

int lab1() {
    double a, b;
    std::cin >> a >> b;
    std::cout << "Вычисленное значение:" << std::endl;
    std::cout << pow(sin(a + pow(b, 3)), 2) * sqrt(e_x(pow(a, 2) - 9.4) / pow(a + b, 3)) << std::endl;

    std::cout << "Контрольное  значение:" << std::endl;
    std::cout << std::pow(std::sin(a + std::pow(b, 3)), 2) *
                 std::sqrt(std::exp(std::pow(a, 2) - 9.4) / std::pow(a + b, 3)) << std::endl;

//    std::cout << sin(11 * PI / 6) << " " << std::sin(11 * PI / 6) << std::endl;
//    std::cout << cos(11 * PI / 6) << " " << std::cos(11 * PI / 6) << std::endl;
    return 0;
}
