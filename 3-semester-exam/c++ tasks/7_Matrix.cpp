#include <iostream>
class Matrix{
    private:
        double* data;
        int numCols;
        int numRows;
    public:
        Matrix(int numRows, int numCols): data(new double[numRows * numCols]), numRows(numRows), numCols(numCols){};
        Matrix(const Matrix& other) = delete;
        Matrix& operator=(const Matrix& other) = delete;
        ~Matrix(){
            if (data) delete[] data;
        }
        void Print() const{
            for (int i = 0; i < numRows; i++){
                for (int j = 0; j < numCols; j++){
                    std::cout << data[j + i * numCols] << ' ';
                    if (j == numCols - 1) std::cout << std::endl;
                }
            }
        }
        double operator()(int row, int col) const{
            return data[col - 1 + (row - 1) * numCols];
        }
        double& operator()(int row, int col){
            return data[col - 1 + (row - 1) * numCols];
        }
};
int main(){
    Matrix A(2, 3);
    A(1, 1) = 1; A(1, 2) = 2; A(1, 3) = 3; A(2, 1) = 4; A(2, 2) = 5; A(2, 3) = 6;
    double result = A(2,2);
    std::cout << result << std::endl;
    A.Print();
    return 0;
}