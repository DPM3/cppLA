#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

namespace matrix {
using namespace vector;

template<int ROWS, int COLS>
class MatrixBase {
protected:
	class Data {
		double elems[ROWS][COLS];
	public:
		Data() = default;
		//this->elems is a copy of the elems parameter
		Data(double elems[ROWS][]) {
			for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				this->elems[i][j] = elems[i][j];
			}
			}
		}
		//get the (i'th, j'th) element
		double& operator()(int i, int j) {
			return elems[i][j];
		}
		//run func for each element. func should be able to get double(or double&) and int.
		template<class FUNC> void foreach(FUNC func) {
			for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				func(elems[i][j], i, j);
			}
			}
		}
	} data;
public:
	//Adds mat to this
	Matrix& operator+=(const Matrix& mat) {
		auto func = [&mat](double& element, int i, int j) { element += mat(i, j); };
		data.foreach(func);
		return *this;
	}
	//Subtracts mat from this
	Matrix& operator-=(const Matrix& mat) {
		auto func = [&mat](double& element, int i, int j) { element -= mat(i, j); };
		data.foreach(func);
		return *this;
	}
	//Multiplying a scalar
	Matrix& operator*=(double d) {
		auto func = [&d](double& element, int i, int j) { element *= d; };
		data.foreach(func);
		return *this;
	}
	//Multiplying a vector
	Vector<ROWS> operator*(const Vector<ROWS>& vec);
	//Multiplying a matrix
	template<int COLS2>
		Matrix<ROWS, COLS2> operator*(const Matrix<COLS, COLS2>& mat);
	double& operator() (int i, int j) {
		return data(i,j);
	}

	Matrix<ROWS-1, COLS-1> minor(int row, int col) {
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
	bool hasInv() { return false; }
};
}

#endif
