all: 
	g++ -Wall p1.cpp
	./a.out
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log --track-origins=yes ./a.out
