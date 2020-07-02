#include<iostream>
#include"../Vector.h"
using namespace vector;

int main() {
	Vector3 v1 = Vector3();
	cout << v1.size() << endl; //should output 3
	v1[0] = 30;
	v1[1] = 20;
	cout << v1[2] << endl; //should output 0
	cout << v1 << endl; //should output 30, 20, 0
	cout << v1.len() << endl; //should output ~36.056

	v1 *= 2;
	cout << v1 << endl; //should output 60, 40, 0

	double arr[3] = {1, 2, 3};
	Vector3 v2 = Vector3(arr);
	cout << v1 + v2 << endl; //61, 42, 3
	cout << v1 - v2 << endl; //59, 38, -3
	cout << v2 * 5 << endl; //5, 10, 15
	cout << v1 * v2 << endl; //140
}
