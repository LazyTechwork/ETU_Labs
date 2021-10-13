#include "labs.h"

int lab2() {
    unsigned int n;
    std::cout << "Введите макс. кол-во элементов: ";
    std::cin >> n;
    int elements[n];
    std::getchar();
    for (int ch, i = 0; (ch = std::getchar()) != EOF && (ch != '{') && i < n; ++i) {
        if (ch >= 0x61 && ch <= 0x7a)
            --i;
        else
            *(elements + i) = ch;
    }

    std::cout << std::string(10, '=') + " РЕЗУЛЬТАТ " + std::string(10, '=') << std::endl;
    for (int *it = elements; it <= *(&elements + 1) - 1; ++it) {
        if (*it >= 0x41 && *it <= 0x5a) {
            *it += 0x20;
        }
        std::cout << (char) *it;
    }
    return 0;
}