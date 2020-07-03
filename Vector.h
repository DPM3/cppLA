#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<cmath>

namespace vector {
using namespace std;

//A vector class with a full interface
template<int SIZE> class Vector {
private:
	mutable class Data {
		double arr[SIZE];
		double* elements = arr;
	public:
		Data() = default;
		//copy from array
		Data(double*const elements, bool isByRef) {
			if (isByRef) {
				this->elements = elements;
			}
			for (int i = 0; i < SIZE; i++)
				this->elements[i] = elements[i];
		}
		//get i'th element
		double& operator[] (int i) {
			return elements[i];
		}
		//get i'th element - for consts
		double operator[] (int i) const {
			return elements[i];
		}
		//run func for each element. func should be able to get double(or double&) and int.
		template<class FUNC> void foreach(FUNC func) {
			for (int i = 0; i < SIZE; i++)
				func(elements[i], i);
		}
	} data;

public:
	//Copy the first SIZE elements of the array into this vector
	Vector() = default;
	Vector(double*const data, bool isByRef = false) : data(data, isByRef) { }

	//Adds other to this
	Vector<SIZE>& operator+= (Vector const& other) {
		auto func = [&other](double& element, int idx) { element += other[idx]; };
		data.foreach(func);
		return *this;
	}
	//Subtracts other from this
	Vector<SIZE>& operator-= (Vector const& other) {
		auto func = [&other](double& element, int idx) { element -= other[idx]; };
		data.foreach(func);
		return *this;
	}
	//Multiplies by scalar
	Vector<SIZE>& operator*= (double d) {
		auto func = [&d](double& element, int idx) { element *= d; };
		data.foreach(func);
		return *this;
	}
	//Divides by scaler
	Vector<SIZE>& operator/= (double d) {
		return operator*=(1.0/d);
	}
	//Returns the dot product of this and v
	double operator* (Vector const& v) const {
		double result = 0;
		auto func = [&v, &result](double element, int idx) { result += element * v[idx]; };
		data.foreach(func);
		return result;
	}

	//Returns the element of data of this index
	double& operator[] (int index) {
		return data[index];
	}
	//Returns the element of data of this index
	double operator[] (int index) const {
		return data[index];
	}
	//Returns the standard norm
	double len() {
		return sqrt(*this * *this);
	}
	//Returns SIZE
	int size() { return SIZE; }
};

//Returns the sum of 2 vectors
template<int SIZE>
Vector<SIZE> operator+ (Vector<SIZE> v1, Vector<SIZE> const& v2) {
	return v1+=v2;
}
//Returns the difference of 2 vectors
template<int SIZE>
Vector<SIZE> operator- (Vector<SIZE> v1, Vector<SIZE> const& v2) {
	return v1-=v2;
}
//Returns the product of the vector and scalar
template<int SIZE>
Vector<SIZE> operator* (double scalar, Vector<SIZE> v) {
	return v *= scalar;
}
//Returns the product of the vector and scalar
template<int SIZE>
Vector<SIZE> operator* (Vector<SIZE> v, double scalar) {
	return v *= scalar;
}
//Returns the division of the vector and scalar
template<int SIZE>
Vector<SIZE> operator/ (double scalar, Vector<SIZE> v) {
	return v /= scalar;
}
//Returns the division of the vector and scalar
template<int SIZE>
Vector<SIZE> operator/ (Vector<SIZE> v, double scalar) {
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
