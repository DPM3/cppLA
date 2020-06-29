#ifndef MATRIX_H
#define MATRIX_H
#include"Vector.h"
template<int ROWS, int COLS> class Matrix {
	Vector<ROWS> vals[COLS];
public:
	//exceptions:
	class SizeExpt{ };
	class OutOfBoundsExpt : public SizeExpt { };
	class MultExpt : public SizeExpt { };

	Matrix() /*throw (OutOfBoundsExpt)*/;

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator*=(double scalar);
	Vector<ROWS>& operator*=(const Vector<ROWS>& vec);

	Vector<ROWS> operator[] (int i);
	double operator() (int i, int j);

	Matrix minor(int row, int col) /*throw (OutOfBoundsExpt)*/;
	bool hasInv() { return false; }
};

//specialization for square matrices
template<int SIZE> class Matrix<SIZE, SIZE> {
	Vector<SIZE> vals[SIZE];
public:
	//exceptions:
	class SizeExpt{ };
	class OutOfBoundsExpt : public SizeExpt { };
	class MultExpt : public SizeExpt { };

	Matrix() /*throw (OutOfBoundsExpt)*/;
	Matrix(double scalar);

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator*=(double scalar);
	Vector<SIZE>& operator*=(const Vector<SIZE>& vec);

	Vector<SIZE> operator[] (int i);
	double operator() (int i, int j);

	Matrix minor(int row, int col) /*throw (OutOfBoundsExpt)*/;
	bool hasInv();
	double det();
	Matrix adj();
	Matrix inv();
};

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator+(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator-(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS>& operator*(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2);

#endif
