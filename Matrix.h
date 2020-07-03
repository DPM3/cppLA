#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

namespace matrix {
using namespace vector;

//declaration
template<int ROWS, int COLS> class Matrix;

//base class for Matrix
template<int ROWS, int COLS>
class MatBase {
protected:
	class Data {
		double elems[ROWS][COLS];
	public:
		Data() = default;
		//this->elems is a copy of the elems parameter
		Data(double elems[][COLS]) {
			for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				this->elems[i][j] = elems[i][j];
		}
		//get the (i'th, j'th) element
		double& operator()(int i, int j) {
			return elems[i][j];
		}
		//run func for each element. func should be able to get double(or double&) and two ints.
		template<class FUNC> void foreach(FUNC func) {
			for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				func(elems[i][j], i, j);
		}
		class RowIter {
			int row, j;
		public:
			RowIter(int row) : row(row), j(0) { }

			double& operator*() {
				return elems[row][j];
			}
			RowIter& operator++(int) {
				j++;
				return *this;
			}
			RowIter& operator++() {
				return *this++;
			}
		};
	} data;
public:
	//NOTE: the following functions are meant to be an interface for Matrix,
	//so we have this implicit conversion function to make this process seamless.
	//This is all done for code sharing between Matrix<ROWS, COLS> and Matrix<SIZE, SIZE>(specialization).
	operator Matrix<ROWS, COLS>() {
		return dynamic_cast<Matrix<ROWS, COLS>> (*this);
	}
	//Adds mat to this
	MatBase& operator+=(MatBase const& mat) {
		auto func = [&mat](double& element, int i, int j) { element += mat(i, j); };
		data.foreach(func);
		return *this;
	}
	//Subtracts mat from this
	MatBase& operator-=(MatBase const& mat) {
		auto func = [&mat](double& element, int i, int j) { element -= mat(i, j); };
		data.foreach(func);
		return *this;
	}
	//Multiplying a scalar
	MatBase& operator*=(double d) {
		auto func = [&d](double& element, int i, int j) { element *= d; };
		data.foreach(func);
		return *this;
	}
	//Multiplying a vector
	Vector<ROWS> operator*(Vector<ROWS> const& vec);
	//Multiplying a matrix
	template<int COLS2>
	Matrix<ROWS, COLS2> operator*(const Matrix<COLS, COLS2>& mat) {
		
	}
	double& operator() (int i, int j) {
		return data(i,j);
	}

	Matrix<ROWS-1, COLS-1> minor(int row, int col) {
		Matrix<ROWS - 1, COLS - 1> min = Matrix<ROWS - 1, COLS - 1>(0);
		int iMin = 0;
		for (int i = 0; i < COLS; i++) {
			if (i == col)
				continue;
			int jMin = 0;
			for (int j = 0; j < ROWS; j++) {
				if (j == row)
					continue;
				min(jMin, iMin) = *this(i, j);
				jMin++;
			}
			iMin++;
		}
		return min;
	}
	virtual bool hasInv() = 0;
};

template<int ROWS, int COLS> class Matrix : public MatBase<ROWS, COLS> {
public:
	bool hasInv() {
		return false;
	}
};

template<int SIZE> class Matrix<SIZE, SIZE> : public MatBase<SIZE, SIZE> {
	typedef MatBase<SIZE,SIZE> Base;
public:
	double det() {
		if (SIZE == 1)
			return *this(0, 0);
		if (SIZE == 2)
			return *this(0, 0) * *this(1, 1) - *this(0, 1) * *this(1, 0);

		double determinant = 0;
		bool isPositive = true;
		for (int i = 0; i < SIZE; i++) {
			double val = *this(0, i) * Base::minor(0, i).det();
			if (isPositive)
				determinant += val;
			else
				determinant -= val;
			isPositive = !isPositive;
		}
		return determinant;
	}

	bool hasInv() {
		return det() != 0;
	}
	
	Matrix inv() {
		if (!hasInv())
			return Matrix(0);
		return (1 / det()) * adj();
	}

	Matrix adj() {
		Matrix adjoint = Matrix();
		for (int col = 0; col < SIZE; col++)
		for (int row = 0; row < SIZE; row++) {
			double mindet = Base::minor(col, row).det();
			if (row + col % 2 == 0)
				adjoint(row, col) = mindet;
			else
				adjoint(row, col) = -1 * mindet;
		}
		return adjoint;
	}
};

}

#endif
