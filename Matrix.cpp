namespace matrix {

template<int ROWS, int COLS>
Matrix<ROWS, COLS>::Matrix() throw (OutOfBoundsExpt) {
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
Matrix<ROWS - 1, COLS - 1> Matrix<ROWS, COLS>::minor(int row, int col) throw (OutOfBoundsExpt) {
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
Matrix<SIZE, SIZE>::Matrix(double scalar) throw (OutOfBoundsExpt) {
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
		return operator()(0, 0);
	}
	if (SIZE == 2) {
		return operator()(0, 0) * operator()(1, 1) - operator()(0, 1) * operator()(1, 0);
	}
	double determinant = 0;
	bool isPositive = true;
	for (int i = 0; i < SIZE; i++) {
		double val = operator()(0, i) * minor(0, i).det();
		if (isPositive) {
			determinant += val;
		}
		else {
			determinant -= val;
		}
		isPositive = !isPositive;
	}
	return determinant;
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
		double mindet = minor(col, row).det();
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
	if (!hasInv()) {
		return Matrix();
	}
	return (1 / det()) * adj();
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator+(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2) {
	Matrix<ROWS, COLS> result = m1;
	return result+=m2;
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2) {
	Matrix<ROWS, COLS> result = m1;
	return result-=m2;
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator*(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2) {
	Matrix<ROWS, COLS> result = m1;
	return result*=m2;
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator*(double scalar, const Matrix<ROWS, COLS>& m) {
	Matrix<ROWS, COLS> m2 = m;
	return m2*=scalar;
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator*(const Matrix<ROWS, COLS>& m, double scalar) {
	return scalar * m;
}

}
