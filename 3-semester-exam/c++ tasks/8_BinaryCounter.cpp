#include <iostream>
class BinaryCounter {
    private:
        int* data;
        int count;
    public:
        BinaryCounter(){
            data = new int[1];
            data[0] = 0;
            count = 1;
        };
        BinaryCounter(const BinaryCounter& other) = delete;
        BinaryCounter& operator=(const BinaryCounter& other) = delete;
        ~BinaryCounter(){
            delete[] data;
        };
        void Print() const{
            for (int i = 0; i < count; ++i) std::cout << data[i] << ' ';
        };
        BinaryCounter& operator++(){
            for(int i = 0; i < this->count; ++i){
                if(this->data[i] == 0){
                    ++(this->data[i]);
                    break;
                }else this->data[i] = 0;
            }
            if (this->data[this->count - 1] == 0){
                int* newdata = new int[count+1];
                for (int i = 0; i < count; ++i){
                    newdata[i] = this->data[i];
                }
                newdata[count] = 1;
                delete[] this->data;
                this->data = nullptr;
                this->data = new int[count + 1];
                for (int i = 0; i < count + 1; ++i){
                    this->data[i] = newdata[i];
                }
                delete[] newdata;
                this->count += 1;
            }
            return *this;
        }
};
int main(){
    BinaryCounter C;
    ++C; ++C; ++C; ++C;
    C.Print();
    return 0;
}