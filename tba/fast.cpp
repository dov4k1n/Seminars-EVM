#include <iostream>

int main() {
    std::cout << "type (x1, y1) and (x2, y2)" << std::endl;
    long double x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    std::cout << "type (x0, y0) of interested point" << std::endl;
    long double x0, y0;
    std::cin >> x0 >> y0;

    long double k = ((long double)y2 - (long double)y1) / ((long double)x2 - (long double)x1);
    long double b = (long double)y1 - k * (long double)x1;
    
    long double y = k * x0 + b;
    std::cout << "line `y = kx + b` with x = " << x0 << " is at height " << y << std::endl;
    std::cout << "k = " << k << ", b = " << b << std::endl;
    std::cout << "`y = kx + b` == `y = " << k << "x + " << b << "`" << std::endl; 

    return 0;
}