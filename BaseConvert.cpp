#include "BaseConvert.h"

const string BaseConvert::ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

long long BaseConvert::dec(string n, unsigned short base) {
    const unsigned long long index = n.size() - 1;
    long long result = 0;
    for (int i = 0; i < n.size(); ++i) {
        result += ALPHABET.find(n[i]) * pow(base, index - i);
    }
    return result;
}

string BaseConvert::convert(unsigned long long int n, unsigned short base) {
    if (n < base)
        return string(1, ALPHABET[n]);
    else
        return convert(n / base, base) + ALPHABET[n % base];
}
