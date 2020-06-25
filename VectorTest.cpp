#include<iostream>
#include"Vector.cpp"

int main() {
	Vector3 vec3 = Vector3();
	vec3[0] = 30;
	vec3[1] = 20;
	cout << vec3[2] << endl;
	cout << vec3[0] <<", "<< vec3[1] <<", "<< vec3[2] << endl;
}
