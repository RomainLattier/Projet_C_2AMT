CFLAGS=-g
LDFLAGS=

test_basic :  Parser_gate.o Gate.o main_test.o
	g++ -o test $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test test?
