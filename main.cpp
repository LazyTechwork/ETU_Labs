#include <iostream>
#include "BaseConvert.h"

using namespace std;

int main() {
    cout << BaseConvert::dec("FF", 16) << endl << BaseConvert::convert(255, 16);
    return 0;
}