#include <iostream>
using namespace std;

class Value{
public:
	virtual Value* CreateZeroValue() = 0;
	virtual Value* Duplicate() = 0;
	virtual Value& operator+=(const Value& other) = 0;
	virtual Value& operator-=(const Value& other) = 0;
	virtual Value& operator*=(const Value& other) = 0;
	virtual Value& operator/=(const Value& other) = 0;
	virtual bool operator==(const Value& other) = 0;
};

class RealValue : public Value {
private:
	double x;
public:
	double GetR() const{
		return x;
	}
	void SetR(const double& xArg){
		x = xArg;
	}
	Value* CreateZeroValue() override{
		RealValue* our = new RealValue;
		our->x = 0;
		return our;
	}
	Value* Duplicate() override{
		RealValue* our = new RealValue;
		our->x = (*this).x;
		return our;
	}
	Value& operator+=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 1;
		const Value* pm = &other;
		const RealValue* pf = dynamic_cast<const RealValue*>(pm);
		x = x + (*pf).x;
		return *this;
	}
	Value& operator-=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 1;
		const Value* pm = &other;
		const RealValue* pf = dynamic_cast<const RealValue*>(pm);
		x = x - (*pf).x;
		return *this;
	}
	Value& operator*=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 1;
		const Value* pm = &other;
		const RealValue* pf = dynamic_cast<const RealValue*>(pm);
		x = x * (*pf).x;
		return *this;
	}
	Value& operator/=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 1;
		const Value* pm = &other;
		const RealValue* pf = dynamic_cast<const RealValue*>(pm);
		if ((*pf).x == 0)
			throw 0;
		x = x / (*pf).x;
		return *this;
	}
	bool operator==(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 1;
		const Value* pm = &other;
		const RealValue* pf = dynamic_cast<const RealValue*>(pm);
		if (x == (*pf).x)
			return true;
		else
			return false;
	}
};

class ComplexValue : public Value {
private:
	double x;
	double y;
public:
	double GetCR() const{
		return x;
	}
	double GetCM() const{
		return y;
	}
	void SetC(const double& xArg, const double& yArg){
		x = xArg;
		y = yArg;
	}
	Value* CreateZeroValue() override{
		ComplexValue* our = new ComplexValue;
		our->x = 0;
		our->y = 0;
		return our;
	}
	Value* Duplicate() override{
		ComplexValue* our = new ComplexValue;
		our->x = (*this).x;
		our->y = (*this).y;
		return our;
	}
	Value& operator+=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 2;
		const Value* pm = &other;
		const ComplexValue* pf = dynamic_cast<const ComplexValue*>(pm);
		x = x + (*pf).x;
		y = y + (*pf).y;
		return *this;
	}
	Value& operator-=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 2;
		const Value* pm = &other;
		const ComplexValue* pf = dynamic_cast<const ComplexValue*>(pm);
		x = x - (*pf).x;
		y = y - (*pf).y;
		return *this;
	}
	Value& operator*=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 2;
		const Value* pm = &other;
		const ComplexValue* pf = dynamic_cast<const ComplexValue*>(pm);
		double x0 = x;
		double y0 = y;
		x = x0 * (*pf).x - y0 * (*pf).y;
		y = x0 * (*pf).y + (*pf).x * y0;
		return *this;
	}
	Value& operator/=(const Value& other) override{
		if (typeid(other).name() != typeid(*this).name())
			throw 2;
		const Value* pm = &other;
		const ComplexValue* pf = dynamic_cast<const ComplexValue*>(pm);
		double x1 = x;
		double y1 = y;
		double x2 = (*pf).x;
		double y2 = (*pf).y;
		if (x2 == 0 and y2 == 0)
			throw 0;
		x = (x1*x2 + y1*y2) / (x2*x2 + y2*y2);
		y = (x2*y1 - x1*y2) / (x2*x2 + y2*y2);
		return *this;
	}
	bool operator==(const Value& other) override{
	if (typeid(other).name() != typeid(*this).name())
		throw 2;
	const Value* pm = &other;
	const ComplexValue* pf = dynamic_cast<const ComplexValue*>(pm);
	if (x == (*pf).x and y == (*pf).y)
		return true;
	else
		return false;
	}
};

void Solve(Value& a, Value& b, Value& result){
	Value* our = a.CreateZeroValue();
	if (a == *our){
		delete our;
		cout << "delenie na 0" << endl;
		throw 0;
	}
	delete our;
	Value* result_help = result.CreateZeroValue();
	result = *result_help;
	b /= a;
	result -= b;
	delete result_help;
}

int main(){
	try{
		RealValue a, b, result;
		a.SetR(3);
		b.SetR(6);
		Solve(a, b, result);
		cout << result.GetR() << endl;
	}
	catch(const int& q){
		cerr << "Error" << " " << q << endl;
	}
	return 0;
}


