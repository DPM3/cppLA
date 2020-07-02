#ifndef VECTOR_H
#define VECTOR_H

#include<cmath>

namespace vector {
using namespace std;

//A vector class with a full interface
template<int SIZE> class Vector : private VectorImpl<SIZE> {
	class Data {
		double elements[SIZE];
	public:
		//empty constructor
		Data() { };
		//copy from array
		Data(double const* elements) {
			for (int i = 0; i < SIZE; i++)
				this->elements[i] = elements[i];
		}
		//get i'th element
		double& operator[] (int i) {
			return elements[i];
		}
		//namespace for arithmetic functions
		struct Arit {
			// add two vectors
			static Data add(Data const& a, Data const& b) {
				Data result;
				for (int i = 0; i < SIZE; i++)
					result[i] = a[i] + b[i];
				return result;
			}
			//subtract two vectors
			static Data subtract(Data const& a, Data const& b) {
				Data result;
				for (int i = 0; i < SIZE; i++)
					result[i] = a[i] - b[i];
				return result;
			}
			//multiply vector by scalar. Also used for negation
			static Data scale(Data const& a, double s) {
				Data result;
				for (int i = 0; i < SIZE; i++)
					result[i] = a[i] * s;
				return result;
			}
			//dot product of two vectors
			static double dotProd(Data const& a, Data const& b) {
				double result=0;
				for (int i = 0; i < SIZE; i++)
					result += a[i] * b[i];
				return result;
			}
			//standard norm
			static double norm(Data const& a) {
				return sqrt(dotProd(a, a));
			}
		};
	} data;
public:
	Vector() : VectorImpl<SIZE>() { }
	//Copy the first SIZE elements of the array into this vector
	Vector(double const& data) : VectorImpl<SIZE>(data) { }

	//Adds other to this
	Vector<SIZE>& operator+= (Vector const& other) {
		data = Data::Arit::add(this->data, other.data);
		return *this;
	}
	//Subtracts other from this
	Vector<SIZE>& operator-= (Vector const& other) {
		data = Data::Arit::subtract(this->data, other.data);
		return *this;
	}
	//Multiplies by scalar
	Vector<SIZE>& operator*= (double d) {
		data = Data::Arit::scale(this->data, d);
		return *this;
	}
	//Divides by scaler
	Vector<SIZE>& operator/= (double d) {
		data = Data::Arit::scale(this->data, 1/d);
		return *this;
	}
	//Returns the dot product of this and v
	double operator* (Vector const& v) {
		return Data::Arit::dotProd(this->.data, v.data);
	}

	//Returns the element of data of this index
	double& operator[] (int index) {
		return data[index];
	}
	//Returns the standard norm
	double len() {
		return Data::Arit::norm(this->data, this->data);
	}
	//Returns SIZE
	int size() {
		return SIZE;
	}
};

//Returns the sum of 2 vectors
template<int SIZE>
Vector<SIZE> operator+ (Vector<SIZE> v1, const Vector<SIZE>& v2) {
	v1 += v2;
	return v1;
}
//Returns the difference of 2 vectors
template<int SIZE>
Vector<SIZE> operator- (Vector<SIZE> v1, const Vector<SIZE>& v2) {
	v1 -= v2;
	return v1;
}
//Returns the product of the vector and scalar
template<int SIZE>
Vector<SIZE> operator* (double scalar, Vector<SIZE> v) {
	return v *= scalar;
}
//Returns the product of the vector and scalar
template<int SIZE>
Vector<SIZE> operator* (const Vector<SIZE>& v, double scalar) {
	return v *= scalar;
}
//Returns the division of the vector and scalar
template<int SIZE>
Vector<SIZE> operator/ (double scalar, Vector<SIZE> v) {
	return v /= scalar;
}
//Returns the division of the vector and scalar
template<int SIZE>
Vector<SIZE> operator/ (const Vector<SIZE>& v, double scalar) {
	return v /= scalar;
}

//operator<< for printing with cout
template<int SIZE>
ostream& operator<< (ostream& os, Vector<SIZE> const& v) {
	os << v[0];
	for (int i = 1; i < SIZE; i++) {
		os << ", " << v[i];
	}
	return os;
}

//for convinience
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
}
#endif
