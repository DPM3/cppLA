#include<iostream>
#include"../Vector.h"
using namespace vector;

int main() {
	Vector3 vec3 = Vector3();
	vec3[0] = 30;
	vec3[1] = 20;
	cout << vec3[2] << endl; //should output 0
	cout << vec3 << endl; //should output 30, 20, 0

	vec3 *= 2;
	cout << vec3.len() << endl;
	cout << vec3.size() << endl; //should be 3
}
