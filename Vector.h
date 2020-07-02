#ifndef VECTOR_H
#define VECTOR_H

#include<cmath>

namespace vector {
//the inner implemetation details of the vector class
template<int SIZE> class VectorImpl {
public:
	VectorImpl() : data() { }
	VectorImpl(double const* data) : data(data) { }
protected:
	//the data of the vector
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
		struct Arith {
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
		};
	} data;
};

//A vector class with a full interface
template<int SIZE> class Vector : private VectorImpl<SIZE> {
public:
	Vector() : VectorImpl() { }
	//Copy the first SIZE elements of the array into this vector
	Vector(double const& data) : VectorImpl(data) { }

	//Adds other to this
	Vector<SIZE>& operator+= (const Vector<SIZE>& other) {
		data = Data::Arith::add(this->data, other.data);
		return *this;
	}
	//Subtracts other from this
#ifndef VECTOR_H
#define VECTOR_H
namespace vector {
//the inner implemetation details of the vector class
template<int SIZE> class VectorImpl {
public:
	VectorImpl() : data() { }
	VectorImpl(double const* data) : data(data) { }
protected:
	//the data of the vector
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
		struct Arith {
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
		};
	} data;
};

template<int SIZE> class Vector : private VectorImpl<SIZE> {
public:
	Vector() : VectorImpl() { }
	Vector(double const& data) : VectorImpl(data) { }

	Vector<SIZE>& operator+= (const Vector<SIZE>& other) {
		data = Data::Arith::add(this->data, other.data);
		return *this;
	}
	Vector<SIZE>& operator-= (const Vector<SIZE>& other) {
		data = Data::Arith::subtract(this->data, other.data);
		return *this;
	}
	Vector<SIZE>& operator*= (double d) {
		data = Data::Arith::scale(this->data, d);
		return *this;
	}
	Vector<SIZE>& operator/= (double d) {
		data = Data::Arith::scale(this->data, 1/d);
		return *this;
	}
	double operator* (Vector const& a, Vector const& b) {
		return Data::Arith::dotProd(a.data, b.data);
	}

	ElmtDouble operator[] (int index);
	
	int size();

	double length();
};

//for convinience
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
}
#endif
	Vector<SIZE>& operator-= (const Vector<SIZE>& other) {
		data = Data::Arith::subtract(this->data, other.data);
		return *this;
	}
	//Multiplies by scalar
	Vector<SIZE>& operator*= (double d) {
		data = Data::Arith::scale(this->data, d);
		return *this;
	}
	//Divides by scaler
	Vector<SIZE>& operator/= (double d) {
		data = Data::Arith::scale(this->data, 1/d);
		return *this;
	}
	//Returns the dot product of this and v
	double operator* (Vector const& v) {
		return Data::Arith::dotProd(this->.data, v.data);
	}

	//Returns the standard norm
	double length() {
		return sqrt(Data::Arith::dotProd(this->data, this->data));
	}
	//Returns the element of data of this index
	double& operator[] (int index) {
		return data[index];
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

//for convinience
typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
}
#endif
