CC = g++
CFLAGS = --std=c++17 -Wall
COMPILE = $(CC) $(CFLAGS)

fn_partial_apply: fn_partial_apply.cpp
	$(COMPILE) $< -o $@

clean: fn_partial_apply
	rm $<
