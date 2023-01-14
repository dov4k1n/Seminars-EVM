#include <iostream>
#include <algorithm>
using namespace std;

class Rational{
private:
	int x;
	int y;
public:
	static void help(int& xArg, int& yArg){
		int a = xArg;
		int b = yArg;
		if (xArg == 0)
			yArg = 1;
		else if (yArg < 0){
			xArg = -abs(a / __gcd(a, b));
			yArg = abs(b / __gcd(a, b));
		}
		else{
			if (xArg > 0){
				xArg = a / __gcd(a, b);
				yArg = b / __gcd(a, b);
			}
			else{
				xArg = -abs(a / __gcd(a, b));
				yArg = abs(b / __gcd(a, b));
			}
			}
	}
	Rational(const Rational& other){
		x = other.x;
		y = other.y;
	}
	Rational(int xArg = 0, int yArg = 1){
		help(xArg, yArg);
		x = xArg;
		y = yArg;
	}
	Rational operator - () const{
		return Rational(-x, y);	
	} 
	Rational operator + (const Rational& other) const{
		Rational my = *this;
		my += other;
		return my;
	}
	Rational operator - (const Rational& other) const{
		Rational my = *this;
		my -= other;
		return my;
	}
	Rational operator * (const Rational& other) const{
		Rational my = *this;
		my *= other;
		return my;
	}
	Rational operator / (const Rational& other) const{
		Rational my = *this;
		my /= other;
		return my;
	}
	Rational& operator += (const Rational& other){
		int xArg = x * other.y + other.x * y;
		int yArg = y * other.y;
		help(xArg, yArg);
		x = xArg;
		y = yArg;
		return *this;
	}
	Rational& operator -= (const Rational& other){
		int xArg = x * other.y - other.x * y;
		int yArg = y * other.y;
		help(xArg, yArg);
		x = xArg;
		y = yArg;
		return *this;
	}
	Rational& operator *= (const Rational& other){
		int xArg = x * other.x;
		int yArg = y * other.y;
		help(xArg, yArg);
		x = xArg;
		y = yArg;
		return *this;
	}
	Rational& operator /= (const Rational& other){
		int xArg = x * other.y;
		int yArg = y * other.x;
		help(xArg, yArg);
		x = xArg;
		y = yArg;
		return *this;
	}
	bool operator == (const Rational& other) const {
		if (x == other.x and y == other.y)
			return true;
		else
			return false;
	}
	bool operator < (const Rational& other) const {
		int x_d = x * other.y;
		int x_other = other.x * y;
		if (x_d < x_other)
			return true;
		else
			return false;
	}
	bool operator > (const Rational& other) const {
    	int x_d = x * other.y;
		int x_other = other.x * y;
		if (x_d > x_other)
			return true;
		else
			return false;
	}
	bool operator >= (const Rational& other) const {
		if (*this > other or *this == other)
			return true;
		else
			return false;
	}
	bool operator <= (const Rational& other) const {
		if (*this < other or *this == other)
			return true;
		else
			return false;
	}
	bool operator != (const Rational& other) const {
		if (*this == other)
			return false;
		else
			return true;
	}
	friend ostream& operator << (ostream& out, const Rational& other){
		out << other.x << '/' << other.y;
		return out;
	}
	friend istream& operator >> (istream& in, Rational& other){
		in >> other.x >> other.y;
		help(other.x, other.y);
		return in;
	}
	operator int () const{
		return x/y;
	}
	operator double () const{
		return double(x)/double(y);
	}

};

int main(){
	Rational my1(1, 2);
	Rational my2(1, 4);
	cout << (my1 - my2) << endl;
	return 0;
}

