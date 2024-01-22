#include <iostream>

// C++11 quirk only allows constexpr f(x)s to have a return statement in the body
constexpr int pow(int base, int exp) {
    return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

int main() {
    constexpr int num = pow(10, 8); // compile-time calculation of 10^8 (been wanting to try it out)

    return 0;
}