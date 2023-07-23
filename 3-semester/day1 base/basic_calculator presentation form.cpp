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

        double Re() const { return re; } // reading // napisat code, chtobi ponyat raznicy mejdy Re
        double& Re() { return re; } // writing
        double Im() const { return im; }
        double& Im() { return im; }

        friend double complexmagn(Complex&);

        Complex operator+(const Complex& other) const {
            return Complex(re + other.re, im + other.im);
        }

        Complex operator-(const Complex& other) const {
            return Complex(re - other.re, im - other.im);
        }
};

double complexmagn(Complex& a) {
    return std::sqrt(a.Re() * a.Re() + a.Im() * a.Im());
}

int main() {
    std::cout << "i'm calculating distance between points. enter 2 points' coordinates" << std::endl;
    double re1, im1, re2, im2;
    std::cin >> re1 >> im1 >> re2 >> im2;

    Complex point_one(re1, im1), point_two(re2, im2), point_temp;
    point_temp = point_one - point_two;
    std::cout << complexmagn(point_temp) << std::endl;

    return 0;
}