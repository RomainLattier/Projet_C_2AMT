CFLAGS=-g -Wall

all: test

test: test_gate.o Gate_comb.o Gate.o ./Combinatoire/And.o
	g++ -o test $^ $(LDFLAGS)


%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean :
	rm -f *.o ./Combinatoire/*.o  *~ test
