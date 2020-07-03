VectorTest: Tests/VectorTest.cpp Vector.h 
	g++ Tests/VectorTest.cpp
Matrix: Matrix.h
	g++ -std=c++17 Matrix.h
clean:
	rm *.o
	rm a.*
