CC = g++
CLFAGS = -Wall -Werror -Wpedantic -g
LFLAGS =
BIN = test

.PHONY: all
all: $(BIN)

.PHONY: clean
clean:
	rm -f *.o $(BIN)

plan.o: plan.cpp plan.hpp types.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

test.o: test.cpp plan.hpp plan.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

tariff.o: tariff.cpp tariff.hpp types.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

planner.o: planner.cpp planner.hpp tariff.hpp plan.hpp types.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

planner_bf.o: planner_bf.cpp planner_bf.hpp tariff.hpp plan.hpp types.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

test: test.o plan.o tariff.o planner.o planner_bf.o
	$(CC) -o $@ $^ $(LFLAGS)
