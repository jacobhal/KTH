FLAGS = -g -Wall -std=c++11
CFLAGS = -c $(FLAGS)

julian.o: julian.cpp julian.hpp
	g++ $(CFLAGS) -o julian.o julian.cpp 

gregorian.o: gregorian.cpp gregorian.hpp
	g++ $(CFLAGS) -o gregorian.o gregorian.cpp

date.o: date.cpp date.hpp
	g++ $(CFLAGS) -o date.o date.cpp

kattistime.o: kthfiles/kattistime.cpp kthfiles/kattistime.h
	g++ $(CFLAGS) -o kattistime.o kthfiles/kattistime.cpp

main.out: main.cpp julian.o gregorian.o date.o kattistime.o
	g++ $(FLAGS) main.cpp julian.o gregorian.o date.o kattistime.o

test.out: kthfiles/datetest.cpp julian.o gregorian.o date.o kattistime.o
	g++ $(FLAGS) -o test.out kthfiles/datetest.cpp julian.o gregorian.o date.o kattistime.o

mainC.out: main.cpp julian.o gregorian.o date.o kattistime.o calendar.hpp 
	g++ $(FLAGS) main.cpp julian.o gregorian.o date.o kattistime.o calendar.hpp

test22.out: kthfiles/cprog09lab22a.cpp julian.o gregorian.o date.o kattistime.o julian.hpp date.hpp
	g++ $(FLAGS) kthfiles/cprog09lab22a.cpp julian.o gregorian.o date.o kattistime.o julian.hpp date.hpp
	#./test22.out < kthfiles/lab22a.in

test22c.out: kthfiles/cprog09lab22c.cpp julian.o gregorian.o date.o kattistime.o calendar.hpp julian.hpp date.hpp
	g++ $(FLAGS) -o test22c.out kthfiles/cprog09lab22c.cpp julian.o gregorian.o date.o kattistime.o calendar.hpp julian.hpp date.hpp
	#./test22c.out < kthfiles/lab22c.in

comp: comparefiles.cpp
	g++ -g -Wall -o comp comparefiles.cpp
	#./comp

test23.out: kthfiles/cprog09lab23.cpp julian.o gregorian.o date.o kattistime.o calendar.hpp julian.hpp date.hpp
	g++ $(FLAGS) -o test23.out kthfiles/cprog09lab23.cpp julian.o gregorian.o date.o kattistime.o calendar.hpp julian.hpp date.hpp
	#./test23.out < kthfiles/lab23.in 

CC    = g++
#CC   = clang++-3.6 -L /usr/lib/gcc/x86_64-linux-gnu/4.8 -I /usr/include/x86_64-linux-gnu/c++/4.8 -I /usr/include/c++/4.8 
FLAGS2 = -std=c++11 -O2 -Wall -pedantic

# 
yourprogram.out: calendar.hpp julian.o gregorian.o date.o kattistime.o
	 $(CC) $(FLAGS2) data/calendar15test.cpp calendar.hpp julian.o gregorian.o date.o kattistime.o

youroutputs:
	cat data/calendar15.01.in | ./yourprogram.out > data/calendar15.01.out
	cat data/calendar15.02.in | ./yourprogram.out > data/calendar15.02.out
	cat data/calendar15.03.in | ./yourprogram.out > data/calendar15.03.out
	cat data/calendar15.04.in | ./yourprogram.out > data/calendar15.04.out
	cat data/calendar15.05.in | ./yourprogram.out > data/calendar15.05.out
	cat data/calendar15.06.in | ./yourprogram.out > data/calendar15.06.out
	cat data/calendar15.07.in | ./yourprogram.out > data/calendar15.07.out
	cat data/calendar15.08.in | ./yourprogram.out > data/calendar15.08.out
	cat data/calendar15.09.in | ./yourprogram.out > data/calendar15.09.out

# Cannot be done on windows
answers:
	cat data/calendar15.01.in | data/calendar15test.out > data/calendar15.01.ans
	cat data/calendar15.02.in | data/calendar15test.out > data/calendar15.02.ans
	cat data/calendar15.03.in | data/calendar15test.out > data/calendar15.03.ans
	cat data/calendar15.04.in | data/calendar15test.out > data/calendar15.04.ans
	cat data/calendar15.05.in | data/calendar15test.out > data/calendar15.05.ans
	cat data/calendar15.06.in | data/calendar15test.out > data/calendar15.06.ans
	cat data/calendar15.07.in | data/calendar15test.out > data/calendar15.07.ans
	cat data/calendar15.08.in | data/calendar15test.out > data/calendar15.08.ans
	cat data/calendar15.09.in | data/calendar15test.out > data/calendar15.09.ans