#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

class Complex {
    private:
        double re;
        double im;
    public:
        Complex(double re = 0, double im = 0) :
            re(re),
            im(im)
        { }

        double Re() const { return re; } // reading
        double& Re() { return re; } // writing
        double Im() const { return im; }
        double& Im() { return im; }

        friend double complexmagn(Complex&);

        Complex operator+(const Complex& other) const { return Complex(re + other.re, im + other.im); }
        Complex operator-(const Complex& other) const { return Complex(re - other.re, im - other.im); }
};

double complexmagn(const Complex& a) { return std::sqrt(a.Re() * a.Re() + a.Im() * a.Im()); }

int main() {
    std::cout << "i'm calculating distance between points. enter 2 points' coordinates" << std::endl;
    Complex point_one, point_two, point_temp;
    std::cin >> point_one.Re() >> point_one.Im() >> point_two.Re() >> point_two.Im();
    
    //point_temp = point_one - point_two;
    std::cout << complexmagn(point_one - point_two) << std::endl;
    // std::cout << complexmagn(point_temp) << std::endl;
    return 0;
}