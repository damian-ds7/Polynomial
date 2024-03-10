#include <iostream>
#include "polynomial.h"

int main() {
    Polynomial p1("-x^2 + 2.2x - 1.5");
    std::cout << p1 << "\n";
    return 0;
}