CC    = g++

FLAGS = -std=c++11 -g -Wall -pedantic -lgmpxx -lgmp

main.out: main.cpp factorial.o
	$(CC) main.cpp factorial.o -o run $(FLAGS)

factorial.o: factorial.cpp factorial.h
	$(CC) -c factorial.cpp $(FLAGS) # -c = Compile Only (no executable created)