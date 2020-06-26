#include<iostream>
#include"Vector.cpp"

int main() {
	Vector3 vec3 = Vector3();
	vec3[0] = 30;
	vec3[1] = 20;
	cout << vec3[2] << endl;
	cout << vec3[0] <<", "<< vec3[1] <<", "<< vec3[2] << endl;

	//The following lines create an error, so the VectorDouble class probably class works
	/*
	double& x = vec3[0];
	x = 10;
	cout << x << endl;
	*/

	//Checking if multipication by scalar works
	vec3 = 2 * vec3; 
	cout << vec3[0] <<", "<< vec3[1] <<", "<< vec3[2] << endl;
}
