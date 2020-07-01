#ifndef MATRIX_H
#define MATRIX_H

#include"Vector.h"

namespace matrix {
using namespace vector;

template<int ROWS, int COLS> class Matrix {
	Vector<ROWS> vals[COLS];
public:
	//exceptions:
	class SizeExpt{ };
	class OutOfBoundsExpt : public SizeExpt { };

	Matrix() throw (OutOfBoundsExpt);

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(double scalar);
	Vector<ROWS>& operator*=(const Vector<ROWS>& vec);
	template<int COLS2>
		Matrix<ROWS, COLS2> operator*(const Matrix<COLS, COLS2>& mat);

	Vector<ROWS>& operator[] (int i);
	typename Vector<ROWS>::ElmtDouble operator() (int i, int j);

	Matrix<ROWS-1, COLS-1> minor(int row, int col) throw (OutOfBoundsExpt);
	bool hasInv() { return false; }

	Vector<ROWS> col(int index);
	Vector<ROWS> row(int index);
};

//specialization for square matrices
template<int SIZE> class Matrix<SIZE, SIZE> {
	Vector<SIZE> vals[SIZE];
public:
	//exceptions:
	class SizeExpt{ };
	class OutOfBoundsExpt : public SizeExpt { };

	Matrix() throw (OutOfBoundsExpt);
	Matrix(double scalar) throw (OutOfBoundsExpt);

	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix& operator*=(double scalar);
	Vector<SIZE>& operator*=(const Vector<SIZE>& vec);
	template<int COLS2>
		Matrix<SIZE, COLS2>& operator*(const Matrix<SIZE, COLS2>& mat);

	Vector<SIZE>& operator[] (int i);
	typename Vector<SIZE>::ElmtDouble operator() (int i, int j);

	Matrix<SIZE-1, SIZE-1> minor(int row, int col) throw (OutOfBoundsExpt);
	bool hasInv();
	double det();
	Matrix adj();
	Matrix inv();

	Vector<ROWS> col(int index);
	Vector<ROWS> row(int index);
};

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator+(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS>& m1, const Matrix<ROWS, COLS>& m2);

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator*(const Matrix<ROWS, COLS>& mat, double scalar);

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator*(double scalar, const Matrix<ROWS, COLS>& mat);

template<int ROWS, int COLS>
Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS>& mat);

}
#include"Matrix.cpp"

#endif
