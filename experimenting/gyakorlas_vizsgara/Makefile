CC = g++
CFLAGS = --std=c++17 -Wall
COMPILE = $(CC) $(CFLAGS)

uniform_init: uniform_init.cpp
	$(COMPILE) $^ -o $@

clean: uniform_init
	rm $^
