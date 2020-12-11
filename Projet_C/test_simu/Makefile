CFLAGS=-g -Wall

all: test

test: test_simulateur.o ../Porte/Gate.o ../Porte/Gate_comb.o ../Porte/Gate_out.o ../Porte/Combinatoire/And.o
	g++ -o test $^ $(LDFLAGS)


%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean :
	rm -f *.o  ../Porte/*.o ../Porte/Combinatoire/*.o  *~ test
