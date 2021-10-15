#include "labs.h"

int lab2() {
    unsigned int n;
    std::cout << "Введите макс. кол-во элементов: ";
    std::cin >> n;
    int elements[n];
    std::getchar();
    int entered = 0;
    for (int ch; (ch = std::getchar()) != EOF && (ch != '{') && entered < n; ++entered) {
        if (ch >= 0x61 && ch <= 0x7a)
            --entered;
        else
            *(elements + entered) = ch;
    }

    std::cout << std::string(10, '=') + " РЕЗУЛЬТАТ " + std::string(10, '=') << std::endl;
    if (entered <= 0)
        return 0;
    for (int *it = elements, i = 0; i <= entered; ++i) {
        if (*it >= 0x41 && *it <= 0x5a) {
            *it += 0x20;
        }
        std::cout << (char) *it;
        ++it;
    }
    return 0;
}