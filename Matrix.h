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
	mutable class Data {
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
		//run func for each element. func should be able to get double(or double&) and two ints.
		template<class FUNC> void foreachRow(int row, FUNC func) {
			for (int j = 0; j < COLS; j++)
				func(elems[row][j], j);
		}
		//run func for each element. func should be able to get double(or double&) and two ints.
		template<class FUNC> void foreachCol(int col, FUNC func) {
			for (int i = 0; i < ROWS; i++)
				func(elems[i][col], i);
		}
	} data;

	template<int SIZE, class GETTER>
	class IntfVec {
		GETTER getElmt;
	public:
		IntfVec(GETTER getElmt) : getElmt(getElmt) { }
		operator Vector<SIZE> () {
			Vector<SIZE> result;
			for (int i = 0; i < SIZE; i++)
				result[i] = getElmt(i);
			return result;
		}
		IntfVec& operator=(Vector<SIZE> vec) {
			for (int i = 0; i < SIZE; i++)
				getElmt(i) = vec[i];
			return *this;
		}
		IntfVec& operator+=(Vector<SIZE> vec) {
			for (int i = 0; i < SIZE; i++)
				getElmt(i) += vec[i];
			return *this;
		}
		IntfVec& operator-=(Vector<SIZE> vec) {
			return operator+=(-vec);
		}
		IntfVec& operator*=(double s) {
			for (int i = 0; i < SIZE; i++)
				getElmt(i) *= s;
			return *this;
		}
		IntfVec& operator/=(double s) {
			return operator*=(1.0/s);
		}
	};

	typedef Matrix<ROWS, COLS> Mat;
public:
	//NOTE: the following functions are meant to be an interface for Matrix.
	//This is all done for code sharing between Matrix<ROWS, COLS> and Matrix<SIZE, SIZE>(specialization).

	//Adds mat to this
	Mat& operator+=(Mat const& mat) {
		data.foreach( [&mat] (double& element, int i, int j) {
			element += mat(i, j);
		});
		return *this;
	}
	//Subtracts mat from this
	Mat& operator-=(Mat const& mat) {
		data.foreach( [&mat] (double& element, int i, int j) {
			element -= mat(i, j);
		});
		return *this;
	}
	//Multiplying a scalar
	Mat& operator*=(double d) {
		data.foreach( [&d] (double& element, int i, int j) {
			element *= d;
		});
		return *this;
	}
	Mat& operator/=(double d) {
		return *this *= 1.0/d;
	}

	//Multiplying a vector
	Vector<ROWS> operator*(Vector<COLS> const& vec) const {
		Vector<ROWS> result;
		data.foreach( [&result, &vec] (double const& element, int i, int j) {
			result[i] += element * vec[j];
		});
		return result;
	}
	//Multiplying a matrix
	template<int COLS2>
	Matrix<ROWS, COLS2> operator*(Matrix<COLS, COLS2> const& mat) const {
		Matrix<ROWS, COLS2> result;
		//multiply by the formula (AB)i,j = R_i(A) * C_j(B)
		result.data.foreach( [&mat, this] (double& element, int i, int j) {
			element = this->row(i) * mat.col(j);
		});
		return result;
	}
	double& operator() (int i, int j) {
		return data(i,j);
	}

	auto row(int row) const {
		auto func = [this, &row] (int j) {
			return *this(row, j);
		};
		return IntfVec<COLS, decltype(func)> (func);
	}

	auto col(int col) const {
		auto func = [this, &col] (int i) {
			return *this(i, col);
		};
		return IntfVec<ROWS, decltype(func)> (func);
	}


	Matrix<ROWS-1, COLS-1> minor(int row, int col) const {
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
	virtual bool hasInv() const = 0;
};

template<int ROWS, int COLS> class Matrix : public MatBase<ROWS, COLS> {
public:
	bool hasInv() const {
		return false;
	}
};

template<int SIZE> class Matrix<SIZE, SIZE> : public MatBase<SIZE, SIZE> {
	typedef MatBase<SIZE,SIZE> Base;
public:
	Matrix() = default;
	Matrix(double s) : Base() {
		Base::data.foreach( [&s] (double& element, int i, int j) {
			element = i==j? 1 : 0;
		});
	}
	double det() const {
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

	bool hasInv() const {
		return det() != 0;
	}
	
	Matrix inv() const {
		if (!hasInv())
			return Matrix(0);
		return (1 / det()) * adj();
	}

	Matrix adj() const {
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

namespace ElmntryOp{

template<int ROWS, int COLS>
void swap(Matrix<ROWS, COLS>& mat, int row1, int row2) {
	Vector<COLS> row = mat.row(row2);
	mat.row(row2) =  mat.row(row1);
	mat.row(row1) = row;
}

template<int ROWS, int COLS>
void scale(Matrix<ROWS, COLS>& mat, int row1, int s) {
	mat.row(row1) *= s;
}

template<int ROWS, int COLS>
void add(Matrix<ROWS, COLS>& mat, int row1, int row2, int mult) {
	mat.row(row2) += mat.row(row1) * mult;
}

}

}

#endif
