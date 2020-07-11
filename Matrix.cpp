#define TEMPL_R_C template<int ROWS, int COLS>
#define MAT_R_C   Matrix<ROWS,COLS>
#define TEMPL_S_G template<int SIZE, class GETTER>
#define RV_S_G    Matrix<ROWS, COLS>::RefVec<SIZE, GETTER>

namespace matrix {

//////////-- Matrix --//////////
TEMPL_R_C
MAT_R_C::Matrix(double scalar) {
	for (int i = 0; i < ROWS; i++)
	for (int j = 0; j < COLS; j++)
		if (i == j) (*this)(i,j) = 1;
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
RV_S_G& RV_S_G::operator+= (Vector<SIZE> vec) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) += vec[i];
}

TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator-= (Vector<SIZE> vec) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) -= vec[i];
}
TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator*= (double scalar) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) *= scalar;
}
TEMPL_R_C TEMPL_S_G
RV_S_G& RV_S_G::operator/= (double scalar) {
	for (int i = 0; i < SIZE; i++)
		getElmt(i) /= scalar;
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
	auto getter = [this, &i] (int j) {
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
	auto getter = [this, &i] (int j) {
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
	for (int i = 0; i < ROWS, i++)
	for (int j = 0; j < COLS, j++)
		(*this)(i,j) += mat(i,j);
	return *this;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator-= (MAT_R_C const& mat) {
	for (int i = 0; i < ROWS, i++)
	for (int j = 0; j < COLS, j++)
		(*this)(i,j) -= mat(i,j);
	return *this;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator*= (double scalar) {
	for (int i = 0; i < ROWS, i++)
	for (int j = 0; j < COLS, j++)
		(*this)(i,j) *= scalar;
	return *this;
}

TEMPL_R_C
MAT_R_C& MAT_R_C::operator/= (double scalar) {
	for (int i = 0; i < ROWS, i++)
	for (int j = 0; j < COLS, j++)
		(*this)(i,j) /= scalar;
	return *this;
}

//////////-- End of Matrix --//////////


}//namespace matrix//

#undef TEMPL_R_C
#undef MAT_R_C
#undef TEMPL_S_G
#undef RV_S_G
