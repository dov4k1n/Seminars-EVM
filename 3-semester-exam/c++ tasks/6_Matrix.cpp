#include <iostream>
class Matrix {
    private:
        double* data;
        int numRows;
        int numCols;
    public:
        Matrix(const double* data_, int numRows_, int numCols_){
            numRows = numRows_;
            numCols = numCols_;
            data = new double[numCols * numRows];
            for (int i = 0; i < numRows; i++){
                for (int j = 0; j < numCols; j++){
                    data[j + i*numCols] = data_[j + i*numCols];
                }
            }
        }
        Matrix(const Matrix& other){
            data = other.data;
            numCols = other.numCols;
            numRows = other.numRows;
        }
        Matrix(): data(nullptr), numRows(0), numCols(0){}
        ~Matrix(){
            if (data != nullptr) delete[] data;
        }
        void Print() const{
            for (int i = 0; i < numRows; i++){
                for (int j = 0; j < numCols; j++){
                    std::cout << data[j + i*numCols] << ' ';
                    if (j == numCols - 1) std::cout << std::endl;
                }
            }
        }
        Matrix& operator=(const Matrix& other){
            if (this->data) delete[] this->data;
            this->data = nullptr;
            this->numCols = other.numCols;
            this->numRows = other.numRows;
            if (other.data){
                this->data = new double[this->numCols * this->numRows];
                for (int i = 0; i < this->numRows; i++){
                    for (int j = 0; j < this->numCols; j++){
                        this->data[j + i*this->numCols] = other.data[j + i*this->numCols];
                        
                    }   
                }
            } 
            return *this;
        }
};
int main(){
    double* data1 = new double[4];
    data1[0] = 1; data1[1] = 2; data1[2] = 3; data1[3] = 4;
    Matrix A(data1, 2, 2), B;
    B = A;
    A.Print();
    std::cout << std::endl;
    B.Print();
    return 0;
}