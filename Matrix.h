#ifndef MATRIX_H
#define MATRIX_H

#include"Vector.h"

//useful defs:
#define TEMPL_R_C template<int ROWS, int COLS>
#define TEMPL_S   template<int SIZE>
#define MAT_R_C   Matrix<ROWS, COLS>
#define MAT_S     Matrix<SIZE, SIZE>

namespace matrix {
using namespace vector;

template<int ROWS, int COLS> class Matrix {

	double data[ROWS][COLS];

public:
	Matrix() = default;

//puts scalar on the main diagonal, and 0 elsewhere
	Matrix(double scalar);

//initialize matrix with syntax {{1,2,3}, {4,5,6}, {7,8,9}}
	Matrix(initializer_list<initializer_list<double>> mat);

//a 'reference vector' representing a part of the matrix's data(for example, a row)
//GETTER is a function that gets the i'th element in this so called 'Vector' that is being referenced
	template<int SIZE, class GETTER>
	class RefVec {
		GETTER getElmt;
	public:
		RefVec(GETTER getElmt);

	//WARNING: this conversion is not always called implicitly
	//(even when it makes sense for it to be called)
	//it's best ignored, but it does exist to support the idea of a reference
		operator Vector<SIZE> ();

	//setter operations:
		RefVec& operator=  (Vector<SIZE> vec);
		RefVec& operator+= (Vector<SIZE> vec);
		RefVec& operator-= (Vector<SIZE> vec);
		RefVec& operator*= (double scalar);
		RefVec& operator/= (double scalar);
	};

//subscript operator:
	double& operator() (int i, int j);
	double const& operator() (int i, int j) const;

//get a row refrence:
	auto rowRef(int i);
//get a copy of row as Vector:
	Vector<COLS> row(int i) const;

//get a col refrence:
	auto colRef(int j);
//get a copy of col as Vector;
	Vector<ROWS> col(int j) const;

//basic addition:
	Matrix& operator+= (Matrix const& mat);
	Matrix& operator-= (Matrix const& mat);

//basic scaling:
	Matrix& operator*= (double scalar);
	Matrix& operator/= (double scalar);

//elemtary operations on a matrix:
	void elmtrySwap(int row1, int row2);
	void elmtryAdd (int row1, int row2, double scalar);
	void elmtryMult(int row, double scalar);
};

//basic comparison:
TEMPL_R_C bool operator== (MAT_R_C const& mat1, MAT_R_C const& mat2);

//basic addition:
TEMPL_R_C MAT_R_C operator+ (MAT_R_C mat1, MAT_R_C const& mat2);
TEMPL_R_C MAT_R_C operator- (MAT_R_C mat1, MAT_R_C const& mat2);

//basic scaling:
TEMPL_R_C MAT_R_C operator* (MAT_R_C mat, double scalar);
TEMPL_R_C MAT_R_C operator/ (MAT_R_C mat, double scalar);

//mat x mat multiplication:
template<int ROWS, int COLS, int COLS2>
Matrix<ROWS, COLS2> operator* (MAT_R_C const& mat1, Matrix<COLS, COLS2> const& mat2);

//mat x vector multiplication:
TEMPL_R_C Vector<ROWS> operator* (MAT_R_C const& mat, Vector<COLS> const& vec);

//minor:
TEMPL_R_C Matrix<ROWS-1, COLS-1> minor(MAT_R_C const& mat, int row, int col);

//transpose:
TEMPL_R_C MAT_R_C trans(MAT_R_C const& mat);

//determinant (only for square matrices):
TEMPL_S double det(MAT_S const& mat);

//adjoint (only for square matrices):
TEMPL_S MAT_S adj(MAT_S const& mat);

//check inversibility:
TEMPL_R_C bool hasInv(MAT_R_C const& mat);

//inverse (only for square matrices):
TEMPL_S MAT_S inv(MAT_S mat);

//cannonical form of mat:
TEMPL_R_C MAT_R_C cf(MAT_R_C mat);

//print matrix:
TEMPL_R_C ostream& operator<<(ostream& os, MAT_R_C const& mat);

}//namespace matrix//

//undef the useful defs:
#undef TEMPL_R_C
#undef TEMPL_S
#undef MAT_R_C
#undef MAT_S

#include"Matrix.cpp"

#endif
