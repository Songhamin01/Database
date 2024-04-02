FLAGS = -Werror -std=c++11

main: main.o database.o database.h
	g++ -c main main.o database.o

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

database.o: database.o database.h
	g++ ${FLAGS} -c database.cpp


	