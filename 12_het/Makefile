all: program

program: variadic_templates.o
	g++ -Wall variadic_templates.o -o program

variadic_templates.o: variadic_templates.cpp
	g++ -Wall -c variadic_templates.cpp -o variadic_templates.o

clean:
	rm -f program *.o
