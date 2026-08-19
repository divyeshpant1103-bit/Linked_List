all: singly

main.o: main.cpp singly.hpp
	g++ -std=c++17 -c main.cpp -o main.o

singly.o: singly.cpp singly.hpp
	g++ -std=c++17 -c singly.cpp -o singly.o

singly: main.o singly.o
	g++ -std=c++17 main.o singly.o -o singly

run: singly
	./singly

clean:
	rm -f main.o singly.o singly