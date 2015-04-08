p1:  
	g++ -Wall p1.cpp
	./a.out
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log --track-origins=yes ./a.out
p2: 
	g++ -Wall p2.cpp
	./a.out	
p3: 
	g++ -Wall p3.cpp
	./a.out

p4: 	
	g++ -Wall p4.cpp
	./a.out

p5: 
	g++ -Wall p5.cpp
	./a.out
test: 
	gcc -Wall -O0 test.c
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log --track-origins=yes ./a.out
