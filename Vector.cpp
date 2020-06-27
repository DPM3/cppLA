#include <iostream>
#include <string>
using namespace std;

template<int SIZE>
class Vector {
private:
	class VectorDouble {
	private:
		double val;
	public:
		operator double() {
			return val;
		}

		void operator= (double d) {
			val = d;
		}
	};

	VectorDouble vals[SIZE];

public:
	Vector() {
		vals = { };
	}

	Vector<SIZE>& operator+= (Vector<SIZE> other) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] = vals[i] + other.vals[i];
		}
		return *this;
	}

	Vector<SIZE>& operator-= (Vector<SIZE> other) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] = vals[i] - other.vals[i];
		}
		return *this;
	}

	VectorDouble& operator[] (int index) {
		return vals[index];
	}

	int size() {
		return SIZE;
	}
};

template<int SIZE> ostream& operator<< (ostream &strm, const Vector<SIZE> *v) {
	string s = "[" + (v*)[0];
	for (int i = 1; i < SIZE; i++) {
		s += ", " + (v*)[i];
	}
	s += "]";
	return strm << s;
}

template<int SIZE> Vector<SIZE> operator+ (Vector<SIZE> v1, Vector<SIZE> v2) {
	Vector<SIZE> result = v1;
	result += v2;
	return result;
}

template<int SIZE> Vector<SIZE> operator- (Vector<SIZE> v1, Vector<SIZE> v2) {
	Vector<SIZE> result = v1;
	result -= v2;
	return result;
}

template<int SIZE> Vector<SIZE> operator* (double scalar, Vector<SIZE> v) {
	Vector<SIZE> result = v;
	for (int i = 0; i < SIZE; i++) {
		result[i] = result[i] * scalar;
	}
	return result;
}

template<int SIZE> Vector<SIZE> operator* (Vector<SIZE> v, double scalar) {
	return scalar * v;
}

//for convinience
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;