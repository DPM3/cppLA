VectorTest: VectorTest.cpp Vector.o
	g++ VectorTest.cpp Vector.o
Vector.o: Vector.cpp
	g++ -c Vector.cpp
clean:
	rm *.o
	rm a.*
