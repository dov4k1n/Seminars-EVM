#include <iostream>
#include <cstring>
class String{
    public:
        int size;
        char* data;
        String():data(nullptr), size(0){}
        String(const char* str){
            size = std::strlen(str);
            data = new char[size];
            for(int i = 0; i < size; i++){
                data[i] = str[i];
            }
        }
        ~String(){
            delete[] data;
        }
        String operator+(const String& str) const{
            String newstr;
            newstr.size = this->size + str.size + 1;
            newstr.data = new char[newstr.size];
            for (int i = 0; i < this->size; i++) newstr.data[i] = this->data[i];
            for (int i = 0; i < str.size; i++) newstr.data[i + this->size] = str.data[i];
			 newstr.data[newstr.size - 1] = '\0';
            return newstr;
        }
        String& operator+=(const String& str){
            for(int i = 0; i < str.size; i++){
                this->data[i + this->size] = str.data[i];
            }
            this->size += str.size;
            return *this;
        }
        char operator[](const int& a) const{
            return this->data[a];
        }
        char& operator[](const int& a){
            return this->data[a];
        }
};
std::ostream& operator<<(std::ostream& out, const String& str){
    for (int i = 0; i < str.size; i++){
        out << str.data[i];
    }
    return out;
}
int main(){
    char* a = new char[3];
    char* b = new char[3];
    a[0] = 'a'; a[1] = 'b'; a[2] = 'c';
    b[0] = 'A'; b[1] = 'B'; b[2] = 'C';
    String str1(a);
    String str2(b);
    std::cout << (str1 + str2) << std::endl;
    str1.data[1] = 'D';
    std::cout << (str1 += str2) << std::endl;
    return 0;
}