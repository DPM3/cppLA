#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>

namespace matrix {
template<int ROWS, int COLS> class Matrix;
}

namespace vector {
using namespace std;

template<int SIZE> class Vector {
	//used for proper interface for the individual elements of the vector
	//(for example, when [] is called).

	double vals[SIZE];

public:
	class ElmtDouble;

	Vector();

	Vector<SIZE>& operator+= (const Vector<SIZE>& other);
	Vector<SIZE>& operator-= (const Vector<SIZE>& other);
	Vector<SIZE>& operator*= (double d);
	Vector<SIZE>& operator/= (double d);

	ElmtDouble operator[] (int index);
	
	int size();

	double length();

	template<int ROWS, int COLS>
	friend ElmtDouble matrix::Matrix<ROWS, COLS>::operator() (int i, int j);
	friend double operator*(const Vector& v1, const Vector& v2);
};

template<int SIZE>
Vector<SIZE> operator+ (Vector<SIZE> v1, const Vector<SIZE>& v2);

template<int SIZE>
Vector<SIZE> operator- (Vector<SIZE> v1, const Vector<SIZE>& v2);

template<int SIZE>
Vector<SIZE> operator* (double scalar, Vector<SIZE> v);

template<int SIZE>
Vector<SIZE> operator* (const Vector<SIZE>& v, double scalar);

template<int SIZE>
double operator* (const Vector<SIZE>& v1, const Vector<SIZE>& v2);

//for convinience
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;

//because we are using templates, it's not possible to compile the Vector module alone,
//and then link it to other modules.
//so whenever someone includes the Vector.h file, they are also including the Vector.cpp file,
//so the Vector class will be compiled with it.
}
#include"Vector.cpp"
#endif
