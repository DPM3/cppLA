VectorTest.o: VectorTest.cpp Vector.h Vector.cpp
	g++ -Wno-deprecated VectorTest.cpp
Matrix.o: Matrix.h Vector.h Vector.cpp
	g++ -Wno-deprecated Matrix.h
clean:
	rm *.o
	rm a.*
