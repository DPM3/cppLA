#include<cmath>
namespace vector {
using namespace std;

template<int SIZE>
class Vector<SIZE>::VectorDouble { 
	double* val;
public:
	VectorDouble(double& val) : val(&val) { }

	operator double() {
		return *val;
	}

	VectorDouble& operator= (double d) {
		*val = d;
		return *this;
	}
	VectorDouble& operator+= (double d) {
		*val += d;
		return *this;
	}
	VectorDouble& operator-= (double d) {
		*val -= d;
		return *this;
	}
	VectorDouble& operator*= (double d) {
		*val *= d;
		return *this;
	}
	VectorDouble& operator/= (double d) {
		*val /= d;
		return *this;
	}
};

template<int SIZE>
Vector<SIZE>::Vector() {
	for (int i = 0; i < SIZE; i++) {
		vals[i] = 0;
	}
}

template<int SIZE>
Vector<SIZE>& Vector<SIZE>::operator+= (const Vector<SIZE>& other) {
	for (int i = 0; i < SIZE; i++) {
		vals[i] = vals[i] + other.vals[i];
	}
	return *this;
}

template<int SIZE>
Vector<SIZE>& Vector<SIZE>::operator-= (const Vector<SIZE>& other) {
	for (int i = 0; i < SIZE; i++) {
		vals[i] = vals[i] - other.vals[i];
	}
	return *this;
}

template<int SIZE>
Vector<SIZE>& Vector<SIZE>::operator*= (double d) {
	for (int i = 0; i < SIZE; i++) {
		vals[i] *= d;
	}
	return *this;
}

template<int SIZE>
Vector<SIZE>& Vector<SIZE>::operator/= (double d) {
	for (int i = 0; i < SIZE; i++) {
		vals[i] /= d;
	}
	return *this;
}

template<int SIZE>
typename Vector<SIZE>::VectorDouble Vector<SIZE>::operator[] (int index) {
	//will work, implicit constructor of VectorDouble
	return vals[index];
}

template<int SIZE>
int Vector<SIZE>::size() {
	return SIZE;
}

template<int SIZE>
Vector<SIZE> operator+ (Vector<SIZE> v1, const Vector<SIZE>& v2) {
	v1 += v2;
	return v1;
}

template<int SIZE>
Vector<SIZE> operator- (Vector<SIZE> v1, const Vector<SIZE>& v2) {
	v1 -= v2;
	return v1;
}

template<int SIZE>
Vector<SIZE> operator* (double scalar, Vector<SIZE> v) {
	return v *= scalar;
}

template<int SIZE>
Vector<SIZE> operator* (const Vector<SIZE>& v, double scalar) {
	return scalar * v;
}

template<int SIZE>
double Vector<SIZE>::length() {
	double squareSum = 0;
	for (int i = 0; i < SIZE; i++) {
		squareSum += pow(vals[i], 2);
	}
	return sqrt(squareSum);
}

}
