#include<iostream>
#include"../../Matrix.h"
using namespace std;
using namespace matrix;
using namespace vector;

int main() {
	Matrix<2,2> mat1(7);
	cout << mat1 << endl; //[[7, 0],[0, 7]]
	mat1(0,0) = 1;
	mat1(0,1) = 2;
	mat1(1,0) = 3;
	mat1(1,1) = 4;
	cout << mat1 << endl; //[[1, 2],[3, 4]]
	cout << mat1.det() << endl; //-2
	cout << mat1.hasInv() << endl; //true
	cout << mat1.adj() << endl; //[[4, -2],[-3, 1]]
	cout << mat1.inv() << endl; //[[-2, 1],[1.5, -0.5]]
	cout << (Vector2)mat1.row(0) << endl; //[1, 2]
	cout << (Vector2)mat1.col(0) << endl; //[1, 3]
	mat1.row(0) = 2 * (Vector2)mat1.row(0);
	cout << mat1 << endl; //[[2, 4],[3, 4]]
	mat1.col(1) = (Vector2)mat1.col(0) + (Vector2)mat1.col(1);
	cout << mat1 << endl; //[[2, 6],[3, 7]]

	Matrix<3,4> (mat2);
	mat2(0,2) = 4;
	mat2(2,1) = mat2(0,2) + 3;
	cout << mat2 << endl; //[[0,0,4,0],[0,0,0,0],[0,7,0,0]]
	Matrix<2,3> mat3 = mat2.minor(2,3);
	cout << mat3 << endl; //[[0,0,4],[0,0,0]]
}/*

	Matrix<2,3> mat4 = mat1 * mat3;
	cout << mat4 << endl; //[[0,0,8],[0,0,12]]
	mat3 += mat4;
	cout << mat3 << endl; //[[0,0,12],[0,0,12]]

	mat3 /= 6;
	cout << mat3 << endl; //[[0,0,2],[0,0,2]]
	Vector<3> (v1);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	mat3.row(0) = v1;
	cout << mat3 << endl; //[[0,0,2],[1,2,3]]
	cout << mat3 * v1 << endl; //[6, 14] 

	Matrix<2,2> (mat5);
	mat5(0,0) = 5;
	mat5(0,1) = 10;
	mat5(1,0) = 15;
	mat5(1,1) = 20;
	cout << mat5 - mat1 << endl; //[[3, 4],[12, 13]]
	cout << mat5 * 2 << endl; //[[10, 20],[30, 40]]
}
*/
