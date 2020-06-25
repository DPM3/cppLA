#include <iostream>
using namespace std;

template<int SIZE> class Vector {
private:
	double vals[SIZE];
public:
	Vector(double* arr) {
		for (int i = 0; i < SIZE; i++) {
			vals[i] = arr[i];
		}
	}

	Vector<SIZE>& operator+= (Vector<SIZE> other) {
		for(int i = 0; i < SIZE; i++) {
			vals[i] += other.vals[i];
		}
		return *this;
	}

	Vector<SIZE>& operator-= (Vector<SIZE> other) {
		for(int i = 0; i < SIZE; i++) {
			vals[i] -= other.vals[i];
		}
		return *this;
	}

	double& operator[] (int index) {
		return vals[index];
	}
	
	int size() {
		return SIZE;
	}
};

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
