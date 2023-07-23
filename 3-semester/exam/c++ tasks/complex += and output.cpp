#include <iostream>

class Complex {
	public:
		Complex(double re = 0, double im = 0) :
			re(re),
			im(im)
		{ }

	Complex& operator+=(const Complex& other) {
		re += other.re;
    im += other.im;
		
		return *this;
  }

  double Re() const { return re; }
  double& Re() { return re; }
  double Im() const { return im; }
  double& Im() { return im; }

	private:
		double re;
		double im;
};

std::ostream& operator<<(std::ostream& out, const Complex& number) {
	out << "(" << number.Re() << ", " << number.Im() << ")";
	return out;
}

int main() {
	Complex point_one(5, 6), point_two(3, 4);
	point_one += point_two;
  std::cout << point_one << std::endl;
	return 0;
}