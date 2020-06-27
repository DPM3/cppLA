#include<iostream>
#include"Vector.cpp"

int main() {
	Vector3 vec3 = Vector3();
	vec3[0] = 30;
	vec3[1] = 20;
	cout << vec3[2] << endl; //should output 0
	cout << vec3[0] <<", "<< vec3[1] <<", "<< vec3[2] << endl; //should output 30, 20, 0

	//The following lines create an error, so the VectorDouble class probably class works
	/*
	double& x = vec3[0];
	x = 10;
	cout << x << endl;
	*/

	vec3 *= 2;
	cout << vec3[0] <<", "<< 2*vec3[1] <<", "<< vec3[2] + 3 << endl; //should output 60, 80, 3
}
