MatrixTest: Tests/MatrixTest/MatrixTest.cpp Matrix.h Vector.h 
	g++ -std=c++17 Tests/MatrixTest/MatrixTest.cpp
VectorTest: Tests/VectorTest.cpp Vector.h 
	g++ -std=c++17 Tests/VectorTest.cpp
Matrix: Matrix.h
	g++ -std=c++17 Matrix.h
clean:
	rm *.o
	rm a.*
