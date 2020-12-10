CFLAGS=-g -Wall

all: test

test: test_gate.o And.o Gate_comb.o Gate.o
	g++ -o test $^


%.o	:%.cpp
	g++ -c  $< $(CFLAGS)

clean :
	rm -f *.o  *~ test
