VectorTest: VectorTest.cpp Vector.h Vector.cpp
	g++ -Wno-deprecated VectorTest.cpp
MatrixTest: MatrixTest.cpp Matrix.h Matrix.cpp
	g++ -Wno-deprecated MatrixTest.cpp
clean:
	rm *.o
	rm a.*
