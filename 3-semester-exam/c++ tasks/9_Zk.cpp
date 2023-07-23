#include <iostream>
class Zk{
    public:
        int value;
        int modulus;
        Zk():value(0), modulus(1){}
        Zk(int value, int modulus): value(value), modulus(modulus){
            value %= modulus;
            if (value < 0) value += modulus;
        }
        Zk operator+(int a) {
            Zk summ;
            summ.modulus = this->modulus;
            summ.value = (this->value + a) % summ.modulus;
            if (summ.value < 0) summ.value += summ.modulus;
            return summ;
        }
        Zk operator*(const int& a) const{
            Zk product;
            product.modulus = this->modulus;
            product.value = (this->value * a) % product.modulus;
            if (product.value < 0) product.value += product.modulus;
            return product;
        }
};
int main(){
    Zk a(5, 2);
    std::cout << (a * 5).value << std::endl;
    std::cout << (a + 5).value << std::endl;
    return 0;
}