#include<iostream>

#define TEMPL_R_C template<int ROWS, int COLS>
#define MAT_R_C   Matrix<ROWS,COLS>
#define TEMPL_S   template<int SIZE>
#define MAT_S     Matrix<SIZE, SIZE>
#define TEMPL_S_G template<int SIZE, class GETTER>
#define RV_S_G    Matrix<ROWS, COLS>::RefVec<SIZE, GETTER>

namespace matrix {

//////////-- Matrix --//////////
TEMPL_R_C
MAT_R_C::Matrix(double scalar) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		if (i == j) (*this)(i,j) = scalar;
		else (*this)(i,j) = 0;
}

TEMPL_R_C
MAT_R_C::Matrix(initializer_list<initializer_list<double>> mat) {
	for (initializer_list<initializer_list<double>>::const_iterator it = mat.begin(); it != mat.end(); it++)
	for (initializer_list<double>::const_iterator ptr = it->begin(); ptr != it->end(); ptr++)
		(*this)(mat.begin() - it, it->begin() - ptr) = *ptr;
}


//////////-- RefVec --//////////
TEMPL_R_C TEMPL_S_G
RV_S_G::RefVec(GETTER getElmt) : getElmt(getElmt) { }

TEMPL_R_C TEMPL_S_G
RV_S_G::operator Vector<SIZE> () {
	Vector<SIZE> result;
	for (int i = 0; i < SIZE; i++)
		result[i] = getElmt(i);
	return result;
}

TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator=  (Vector<SIZE> vec) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) = vec[i];
	return *this;
}

TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator+= (Vector<SIZE> vec) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) += vec[i];
	return *this;
}

TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator-= (Vector<SIZE> vec) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) -= vec[i];
	return *this;
}
TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator*= (double scalar) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) *= scalar;
	return *this;
}
TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator/= (double scalar) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) /= scalar;
	return *this;
}

//////////-- End of RefVec --//////////

TEMPL_R_C
double& MAT_R_C::operator() (int i, int j) {
	return data[i][j];
}

TEMPL_R_C
double const& MAT_R_C::operator() (int i, int j) const {
	return data[i][j];
}

TEMPL_R_C
auto MAT_R_C::rowRef (int i) {
	auto getter = [this, &i] (int j) -> double& {
		return (*this)(i,j);
	};
	return RefVec<COLS, decltype(getter)>(getter);
}

TEMPL_R_C
Vector<COLS> MAT_R_C::row(int i) const {
	Vector<COLS> result;
	for (int j = 0; j < COLS; j++)
		result[j] = (*this)(i,j);
	return result;
}

TEMPL_R_C
auto MAT_R_C::colRef (int i) {
	auto getter = [this, &i] (int j) -> double& {
		return (*this)(i,j);
	};
	return RefVec<ROWS, decltype(getter)>(getter);
}

TEMPL_R_C
Vector<ROWS> MAT_R_C::col(int i) const {
	Vector<ROWS> result;
	for (int j = 0; j < ROWS; j++)
		result[j] = (*this)(i,j);
	return result;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator+= (MAT_R_C const& mat) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		(*this)(i,j) += mat(i,j);
	return *this;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator-= (MAT_R_C const& mat) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		(*this)(i,j) -= mat(i,j);
	return *this;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator*= (double scalar) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		(*this)(i,j) *= scalar;
	return *this;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator/= (double scalar) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		(*this)(i,j) /= scalar;
	return *this;
}

TEMPL_R_C
void MAT_R_C::elmtrySwap(int row1, int row2) {
	Vector<COLS> temp = row(row1);
	rowRef(row1) = row(row2);
	rowRef(row2) = temp;
}

TEMPL_R_C
void MAT_R_C::elmtryAdd(int row1, int row2, double scalar) {
	rowRef(row1) += row(row2) * scalar;
}

TEMPL_R_C
void MAT_R_C::elmtryMult(int row, double scalar) {
	rowRef(row) *= scalar;
}

//////////-- End of Matrix --//////////

TEMPL_R_C
bool operator== (MAT_R_C const& mat1, MAT_R_C const& mat2) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		if (mat1(i,j) != mat2(i,j)) return false;
	return true;
}

TEMPL_R_C
MAT_R_C operator+ (MAT_R_C mat1, MAT_R_C const& mat2) {
	return mat1 += mat2;
}

TEMPL_R_C
MAT_R_C operator- (MAT_R_C mat1, MAT_R_C const& mat2) {
	return mat1 -= mat2;
}

TEMPL_R_C
MAT_R_C operator* (MAT_R_C mat, double scalar) {
	return mat *= scalar;
}

TEMPL_R_C
MAT_R_C operator/ (MAT_R_C mat, double scalar) {
	return mat /= scalar;
}

template<int ROWS, int COLS, int COLS2>
Matrix<ROWS, COLS2> operator* (MAT_R_C const& mat1, Matrix<COLS, COLS2> const& mat2) {
	Matrix<ROWS, COLS2> result;
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS2; j++)
		result(i,j) = mat1.row(i) * mat2.col(j);
	return result;
}

TEMPL_R_C
Vector<ROWS> operator* (MAT_R_C const& mat, Vector<COLS> const& vec) {
	Vector<ROWS> result;
	for (int i = 0; i < ROWS; i++)
		result[i] = mat.row(i) * vec;
	return result;
}

TEMPL_R_C
Matrix<ROWS-1, COLS-1> minor(MAT_R_C const& mat, int row, int col) {
	Matrix<ROWS-1, COLS-1> result;
	for (int i = 0; i < ROWS-1; i++)
	for (int j = 0; j < COLS-1; j++)
		result(i,j) = mat(i<row ? i : i+1, j<col ? j : j+1);
	return result;
}

TEMPL_R_C
MAT_R_C trans(MAT_R_C const& mat) {
	MAT_R_C result;
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		result(i,j) = mat(j,i);
	return result;
}

TEMPL_S
double det(MAT_S const& mat) {
	double result = 0;
	for (int i = 0; i < SIZE; i++)
		result += (i%2 ? 1 : -1) * det(minor(mat, 0, i));
	return result;
}
template<>
double det<1>(Matrix<1,1> const& mat) {
	return mat(0,0);
}

TEMPL_S
MAT_S adj(MAT_S const& mat) {
	MAT_S result;
	for (int i = 0; i < SIZE; i++)
	for (int j = 0; j < SIZE; j++)
		result(i,j) = ((i+j)%2 ? -1 : 1) * det(minor(mat, j, i));
	return result;
}

TEMPL_R_C
bool hasInv(MAT_R_C const& mat) {
	return cf(mat) == MAT_R_C(0);
}

TEMPL_S
MAT_S inv(MAT_S mat) {
	if (!hasInv(mat)) return MAT_S(0);

	//NOTE: This is exactly the same algorithm of the cf(mat) function,
	//only it is doing every elentary operation to I as well.
	//This gives us the inverse
	//
	//also notice that since this is only for square matrices, we use SIZE instead of ROWS or COLS
	//(like in the original algorithm for canonnical form)

	MAT_S result(1); // = I

	int amountScanned = -1;
	for (int mostSegCol = 0; mostSegCol < SIZE; mostSegCol++) {
		int row = amountScanned + 1;
		while (mat(row,mostSegCol) == 0) row++;
		if (row == SIZE) continue;

		mat.elmtryMult(row, 1.0/mat(row,mostSegCol));
		result.elmtryMult(row, 1.0/mat(row,mostSegCol)); //changes here
		for (int i = 0; i < SIZE; i++) {
			if (i == row)
				i++;
			mat.elmtryAdd(i, row, -mat(row,mostSegCol));
			result.elmtryAdd(i, row, -mat(row,mostSegCol)); //here
		}
		mat.elmtrySwap(row, ++amountScanned);
		result.elmtrySwap(row, ++amountScanned); //and here
	}
	return result;
}

TEMPL_R_C
MAT_R_C cf(MAT_R_C mat) { //notice we get a copy, not the original
	//indicate how many rows have been scanned(minus one for implementation purposes)
	int amountScanned = -1;
	//mostSegCol = column of the next scanned row's most segnificant element(most left that isn't 0)
	for (int mostSegCol = 0; mostSegCol < COLS; mostSegCol++) {
		int row = amountScanned + 1;
		while (mat(row,mostSegCol) == 0) row++;
		//if couldn't find row with a proper most segnificant element, then move on to the next iteration
		if (row == ROWS) continue;

		mat.elmtryMult(row, 1.0/mat(row,mostSegCol));
		//subtract all other rows
		for (int i = 0; i < ROWS; i++) {
			if (i == row)
				i++;
			mat.elmtryAdd(i, row, -mat(row,mostSegCol));
		}
		//organize rows to match wanted shape
		mat.elmtrySwap(row, ++amountScanned);
	}
	return mat;
}

TEMPL_R_C
ostream& operator<<(ostream& os, MAT_R_C const& mat) {
	cout << endl;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			cout << mat(i,j) << '\t';
		cout << endl;
	}
	return os;
}

}//namespace matrix//

#undef TEMPL_R_C
#undef MAT_R_C
#undef TEMPL_S_G
#undef RV_S_G
