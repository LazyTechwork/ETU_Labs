#include "labs.h"

int lab2() {
    unsigned int n;
    std::cout << "Введите макс. кол-во элементов: ";
    std::cin >> n;
    unsigned char elements[n];
    std::getchar();
    for (int ch, i = 0; (ch = std::getchar()) != EOF && (ch != '{') && i < n; ++i) {
        if (ch >= 0x61 && ch <= 0x7a)
            --i;
        else
            *(elements + i) = ch;
    }
//    aHbBcCdDfFeEtTyY!!!!
    for (int i = 0; i < sizeof(elements); ++i) {
        int element = *(elements + i);
        if (element >= 0x41 && element <= 0x5a) {
            element += 0x20;
        }
        std::cout << "[" << i << "] " << (char) element << std::endl;
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}