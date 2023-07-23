#include <iostream>

class Matrix {
	public:
		Matrix(const double* data, int numRows, int numCols);

		Matrix(const Matrix& other);
		Matrix& operator=(const Matrix& other);

		~Matrix() {
      if (data)
        delete[] data;
    }

		void Print() const {
      
    }

	private:
		double* data;
		int numRows;
		int numCols;
};

int main() {

  return 0;
}