#include <iostream>
class Complex{
    private:
        double re;
        double im;
    public:
        Complex(): re(0), im(0) {}
        Complex(double re, double im = 0): re(re), im(im) {}
        Complex operator+(const Complex& other) const{
            Complex res;
            res.re = this->re + other.re;
            res.im = this->im + other.im;
            return res;
        }
        Complex& operator+=(const Complex& other){
            this->re += other.re;
            this->im += other.im;
            return *this;
        }
        double real() const{
            return this->re;
        }
        double image() const{
            return this->im;
        }
};
std::ostream& operator<<(std::ostream& out, const Complex& number){
    return out << "(" << number.real() << ";" << number.image() << ")" << std::endl;
};
int main(){
    Complex a(2,5), b(3,8), c(9,5);
    std::cout << (a + b) << std::endl;
    std::cout << (a += c) << std::endl;
    return 0;
}