CC = g++
CFLAGS = --std=c++17 -Wall
COMPILE = $(CC) $(CFLAGS)
PROGRAM = fn_partial_apply

fn_partial_apply: fn_partial_apply.cpp
	$(COMPILE) $< -o $@

clean: 
	rm $(PROGRAM)
