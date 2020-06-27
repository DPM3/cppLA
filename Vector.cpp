#include <iostream>
using namespace std;

template<int SIZE> class Vector {
	//used for proper interface for the individual elements of the vector
	//(for example, when [] is called).
	class VectorDouble { 
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

	double vals[SIZE];

public:
	Vector() {
		for (int i = 0; i < SIZE; i++) {
			vals[i] = 0;
		}
	}

	Vector<SIZE>& operator+= (const Vector<SIZE>& other) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] = vals[i] + other.vals[i];
		}
		return *this;
	}

	Vector<SIZE>& operator-= (const Vector<SIZE>& other) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] = vals[i] - other.vals[i];
		}
		return *this;
	}

	Vector<SIZE>& operator*= (double d) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] *= d;
		}
		return *this;
	}

	Vector<SIZE>& operator/= (double d) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] /= d;
		}
		return *this;
	}

	VectorDouble operator[] (int index) {
		//will work, implicit constructor of VectorDouble
		return vals[index];
	}
	
	int size() {
		return SIZE;
	}
};

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

//for convinience
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
