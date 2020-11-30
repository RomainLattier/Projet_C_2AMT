CFLAGS=-g
LDFLAGS=

test_basic :  Parser_gate.o main_test.o
	g++ -o test $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test_basic test?
