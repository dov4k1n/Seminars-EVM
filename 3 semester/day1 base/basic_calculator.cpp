#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

/*typedef struct city {
    std::string name;
    double distance;
};*/

class Complex {
    private:
        double re;
        double im;
    public:
        Complex(double re = 0, double im = 0) :
            re(re),
            im(im)
        { }

        double Re() const { return re; }
        double Re() { return re; }
        double Im() const { return im; }
        double Im() { return im; }

        friend double complexmagn(Complex&);

        Complex operator+(const Complex& other) const {
            return Complex(re + other.re, im + other.im);
        }

        Complex operator-(const Complex& other) const {
            return Complex(re - other.re, im - other.im);
        }
        // (a + bi) * (c + di) = (ac - bd) + (ad + bc)*i
        Complex operator*(const Complex& other) const {
            return Complex(re*other.re - im*other.im, re*other.im + im*other.re);
        }
        // (a + bi) / (c + di) = (c^2 + d^2)^(-1) * ( (ac + bd) + (bc - ad)*i )
        Complex operator/(const Complex& other) const {
            double tmp = complexmagn(other);
            return Complex( (re*other.re + im*other.im) / tmp, (im*other.re - re*other.im) / tmp );
        }

        Complex& operator+=(const Complex& other) {
            re += other.re;
            im += other.im;

            return *this;
        }

        Complex& operator-=(const Complex& other) {
            re -= other.re;
            im -= other.re;

            return *this;
        }

        /*Complex& operator*=(const Complex& other) {

        }*/

        Complex operator-() const {
            return Complex(-re, -im);
        }

        Complex operator+(double other) const {
            return Complex(re + other, im);
        }

        Complex operator-(double other) const {
            return Complex(re - other, im);
        }

        Complex operator*(double other) const {
            return Complex(re*other, im*other);
        }

        Complex operator/(double other) const {
            return Complex(re/other, im/other);
        }
};

double complexmagn(Complex& a) {
    return std::sqrt(a.Re() * a.Re() + a.Im() * a.Im());
}

Complex operator+(const double& left, const Complex& right) {
    return Complex(left + right.Re(), right.Im());
}

Complex operator-(const double& left, const Complex& right) {
    return Complex(left - right.Re(), -right.Im());
}

Complex operator*(const double& left, const Complex& right) {
    return Complex(left*right.Re(), left*right.Im());
}

Complex operator/(const double& left, const Complex& right) {
    Complex tmp(left, 0);
    return tmp/right;
}
/*
std::vector<city> gen_city(const int& amountof_cities) {
	std::vector<city> myret;
	city tmp;
    std::vector<std::string> names = {"Moscow","Kiev","Donbass","Makhachkala","Washington","Berlin","Lvyov"};

	for (int i = 0; i < amountof_cities; i++) {
		tmp.name = names[rand() % 7];
		tmp.distance = 15 + (rand() % 26);
		myret.push_back(tmp);
	}
	return myret;
}*/

/*//ax^2 + bx + c = 0
std::vector<double> solve2eq(double& a, double& b, double& c) {
    std::vector<Complex> solutions;
    solutions.push_back();
}*/

int main() {
    std::cout << "i'm calculating distance between points. enter 2 points' coordinates" << std::endl;
    double re1, im1, re2, im2;
    std::cin >> re1 >> im1 >> re2 >> im2;

    Complex point_one(re1, im1), point_two(re2, im2), point_temp;
    point_temp = point_one - point_two;
    std::cout << complexmagn(point_temp) << std::endl;

    return 0;
}