#ifndef MATRIX_H
#define MATRIX_H
#include"Vector.h"
template<int ROWS, int COLS> class Matrix {
	typedef Vector<ROWS> Vector;
	Vector vals[COLS];
public:
	//exceptions:
	class SizeExpt{ };
	class OutOfBoundsExpt : public SizeExpt { };
	class MultExpt : public SizeExpt { };

	Matrix() throw OutOfBoundsExpt;
	Matrix(int scalar);

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator*=(double scalar);
	Vector& operator*=(const Vector& vec);

	Vector operator[] (int i);
	double operator() (int i, int j);

	Matrix minor(int row, int col) throw OutOfBoundsExpt;
	bool hasInv() { return false; }
}

//specialization for square matrices
template<int SIZE> class Matrix<SIZE, SIZE> {
	typedef Vector<SIZE> Vector;
	Vector vals[SIZE];
public:
	//exceptions:
	class SizeExpt{ };
	class OutOfBoundsExpt : public SizeExpt { };
	class MultExpt : public SizeExpt { };

	Matrix() throw OutOfBoundsExpt;
	Matrix(int scalar);

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator*=(double scalar);
	Vector& operator*=(const Vector& vec);

	Vector operator[] (int i);
	double operator() (int i, int j);

	Matrix minor(int row, int col) throw OutOfBounds;
	bool hasInv();
	double det();
	Matrix adjoint();
	Matrix inv();
}

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator+(const Matrix<int ROWS, int COLS>& m1, const matrix<int ROWS, int COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator-(const matrix<int ROWS, int COLS>& m1, const matrix<int ROWS, int COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator*(const matrix<int ROWS, int COLS>& m1, const matrix<int ROWS, int COLS>& m2);

#endif
