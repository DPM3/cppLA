VectorTest: VectorTest.cpp Vector.h Vector.cpp
	g++ VectorTest.cpp
Matrix: Matrix.h Vector.h Vector.cpp
	g++ Matrix.h
clean:
	rm *.o
	rm a.*
