CFLAGS=-g -Wall

all : test

test : main_test.o Parser_gate.o ../Porte/Combinatoire/And.o ../Porte/Gate_comb.o ../Porte/Gate.o
	g++ -o test $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test ../Porte/Combinatoire/*o ../Porte/*o
