#ifndef ETU_BASECONVERT_H
#define ETU_BASECONVERT_H

#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class BaseConvert {

public:
    static const string ALPHABET;

    static long long dec(string n, unsigned short base);

    static string convert(unsigned long long n, unsigned short base);
};


#endif
