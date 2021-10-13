#include "lab1.h"

std::vector<unsigned long long> factorials = {1};

const float PI = 3.141592;

unsigned int resolve_quarter(double angle) {
    unsigned int quarter = std::ceil((angle) / (PI / 2));
    if (std::fmod(angle, PI / 2) == 0)
        quarter++;
    if (quarter > 4)
        quarter = quarter % 4 == 0 ? 4 : quarter % 3 == 0 ? 3 : quarter % 2 == 0 ? 2 : 1;
    return quarter;
}

unsigned long long fact(unsigned long long int x) {
    if (factorials.size() - 1 >= x) {
        return factorials[x];
    }
    unsigned long long result = factorials[factorials.size() - 1];
    for (unsigned int i = factorials.size(); i <= x; ++i) {
        result *= i;
        factorials.push_back(result);
    }
    return result;
}

double pow(double x, int n) {
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= x;
    }
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
    for (int i = 1; i < 20; ++i) {
        result[i] = 0.5 * (result[i - 1] + x / result[i - 1]);
    }
    return result[19];
}

double sin(double x) {
    const unsigned int quarter = resolve_quarter(x);
    x /= x > PI * 2 ? quarter * (PI / 2) : 1;
    const bool invert = quarter == 3 || quarter == 4;
    if (quarter == 2) {
        x = PI - x;
    } else if (quarter == 3) {

    }
    double result = x;
    for (int i = 1; i <= 20; ++i) {
        result += (pow(-1, i) * pow(x, 2 * i + 1)) / fact(2 * i + 1);
    }
    return result;
}

double cos(double x) {
    x /= x > PI * 2 ? resolve_quarter(x) * (PI / 2) : 1;
    double result = 1;
    for (int i = 1; i <= 20; ++i) {
        result += (pow(-1, i) * pow(x, 2 * i)) / fact(2 * i);
    }
    return result;
}

double atg(double x) {
    double result = x;
    for (int i = 1; i <= 20; ++i) {
        result += (pow(-1, i - 1) * pow(x, 2 * i - 1)) / (2 * i - 1);
    }
    return result - 1;
}

int lab1() {
//    int a, b;
//    cin >> a >> b;
//    cout << pow(sin(a + pow(b, 2)), 2) * sqrt(e_x(pow(a, 2) - 9.4) / pow(a - b, 3)) << endl;
    std::cout << resolve_quarter((3 * PI) / 2);
    return 0;
}
