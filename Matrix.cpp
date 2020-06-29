#include "Matrix.h"
using namespace std;

template<int ROWS, int COLS>
Matrix<ROWS, COLS>::Matrix() {
	for (int col = 0; col < COLS; col++) {
		for (int row = 0; row < ROWS; row++) {
			operator()(row, col) = 0;
		}
	}
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& Matrix<ROWS, COLS>::operator+=(const Matrix<ROWS, COLS>& mat) {
	for (int col = 0; col < COLS; col++) {
		for (int row = 0; row < ROWS; row++) {
			operator()(row, col) += mat(row, col);
		}
	}
	return *this;
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& Matrix<ROWS, COLS>::operator-=(const Matrix<ROWS, COLS>& mat) {
	return operator+=(-1 * mat);
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& Matrix<ROWS, COLS>::operator*=(const Matrix<ROWS, COLS>& mat) {
	
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& Matrix<ROWS, COLS>::operator*=(double scalar) {
	for (int col = 0; col < COLS; col++) {
		for (int row = 0; row < ROWS; row++) {
			operator()(row, col) *= scalar;
		}
	}
	return *this;
}

template<int ROWS, int COLS>
Matrix<ROWS - 1, COLS - 1> Matrix<ROWS, COLS>::minor(int row, int col) throw OutOfBoundsExpt {
	if (ROWS == 1 || COLS == 1) {
		throw OutOfBoundsExpt();
	}
	Matrix<ROWS - 1, COLS - 1> min = Matrix<ROWS - 1, COLS - 1>(0);
	int iMin = 0;
	for (int i = 0; i < COLS; i++) {
		if (i == col) {
			continue;
		}
		int jMin = 0;
		for (int j = 0; j < ROWS; j++) {
			if (j == row) {
				continue;
			}
			min(jMin, iMin) = operator()(i, j);
			jMin++;
		}
		iMin++;
	}
	return min;
}

template<int SIZE>
Matrix<SIZE, SIZE>::Matrix(double scalar) {
	for (int col = 0; col < SIZE; col++) {
		for (int row = 0; row < SIZE; row++) {
			if (row == col) {
				operator()(row, col) = scalar;
			}
			else {
				operator()(row, col) = 0;
			}
		}
	}
}

template<int SIZE>
double Matrix<SIZE, SIZE>::det() {
	if (SIZE == 1) {
		return operator()(i, j);
	}
	if (SIZE == 2) {
		return operator()(0, 0) * operator()(1, 1) - operator()(0, 1) * operator()(1, 0);
	}
	double det = 0;
	bool isPositive = true;
	for (int i = 0; i < SIZE; i++) {
		double val = operator()(0, i) * minor(0, i);
		if (isPositive) {
			det += val;
		}
		else {
			det -= val;
		}
		isPositive = !isPositive;
	}
	return det;
}

template<int SIZE>
bool Matrix<SIZE, SIZE>::hasInv() {
	return det() != 0;
}

template<int SIZE>
Matrix<SIZE, SIZE> Matrix<SIZE, SIZE>::adj() {
	Matrix<SIZE, SIZE> adjoint = Matrix<SIZE, SIZE>();
	for (int col = 0; col < SIZE; col++) {
		for (int row = 0; row < SIZE; row++) {
			double mindet = minor(col, row);
			if (row + col % 2 == 0) {
				adjoint(row, col) = mindet;
			}
			else {
				adjoint(row, col) = -1 * mindet;
			}
		}
	}
	return adjoint;
}

template<int SIZE>
Matrix<SIZE, SIZE> Matrix<SIZE, SIZE>::inv() {
	Matrix<SIZE, SIZE> invmat = Matrix<SIZE, SIZE>();
	if (!hasInv()) {
		return intmat;
	}
	return (1 / det) * adj();
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator+(const Matrix<int ROWS, int COLS>& m1, const matrix<int ROWS, int COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator-(const matrix<int ROWS, int COLS>& m1, const matrix<int ROWS, int COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator*(const matrix<int ROWS, int COLS>& m1, const matrix<int ROWS, int COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator*(double scalar, const matrix<int ROWS, int COLS>& m) {
	Matrix<ROWS, COLS> timesmat& = Matrix<ROWS, COLS>();
	timesmat = Matrix(m);
	timesmat *= scalar;
	return timesmat;
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator*(const matrix<int ROWS, int COLS>& m, double scalar) {
	return m * scalar;
}
