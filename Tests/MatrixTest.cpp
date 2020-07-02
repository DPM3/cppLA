#include"Matrix.h"
using namespace matrix;
using namespace vector;

int main() {
	Matrix<2,2> mat(1);
	cout << mat.det() << endl;
	cout << mat(0,0) << endl;
	cout << mat.col(1)[0] << endl;
	cout << mat.minor(0,0)(0,0) << endl;
}
