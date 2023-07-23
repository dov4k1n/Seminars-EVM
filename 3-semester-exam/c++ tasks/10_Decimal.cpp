#include<iostream>
int Compare (int a, int b);
class Decimal{
    public:
        int* digits;
        int count;
        Decimal(int* digits_, int count_){
            count = count_;
            digits = new int[count];
            for (int i = 0; i < count; i++) digits[i] = digits_[i];
        }
        Decimal(): count(0), digits(nullptr){}
        ~Decimal(){
            delete[] digits;
        }
        Decimal(const Decimal& other){
            digits = other.digits;
            count = other.count;
        }
        Decimal& operator=(const Decimal& other){
            if (this->digits) delete[] this->digits;
            this->digits = nullptr;
            if (other.digits){
                this->digits = new int[other.count];
                for(int i = 0; i < other.count; i++) this->digits[i] = other.digits[i];
            }
            this->count = other.count;
            return *this;
        }
        Decimal operator+(const Decimal& dec){
            Decimal newdec;
            Decimal result;
            int size = Compare(this->count, dec.count);
            newdec.count = size;
            newdec.digits = new int [size + 1];
            for (int i = 0; i < this->count; ++i){
                newdec.digits[i] = this->digits[i];
            }
            int carry = 0;
            for(int j = 0; j < dec.count; ++j){
                newdec.digits[j] += dec.digits[j] + carry;
                if (newdec.digits[j] > 9){
                    newdec.digits[j] %= 10;
                    carry = 1;  
                }
                else carry = 0;
            }
            if (carry == 1){
                newdec.digits[size] = 1;
                newdec.count = size + 1;
                result = newdec;
            }
            else{
                Decimal newdecfixed;
                newdecfixed.digits = new int[size];
                for (int i = 0; i < size; ++i) newdecfixed.digits[i] = newdec.digits[i];
                newdecfixed.count = size;
                result = newdecfixed;
            }
            return result;
        }
        void Print(){
            for (int i = count - 1; i >= 0; --i) std::cout << digits[i] << ' ';
        }
};
int Compare (int a, int b){
    if (a > b) return a;
    else return b;
};
int main(){
    int* a = new int[3];
    a[0] = 2; a[1] = 5; a[2] = 9;
    int* b = new int[3];
    b[0] = 7; b[1] = 8; b[2] = 1;
    Decimal A(a, 3), B(b, 3);
    A.Print();
    std::cout << std::endl;
    B.Print();
    std::cout << std::endl;
    (A + B).Print();
    return 0;
}