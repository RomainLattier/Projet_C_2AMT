CFLAGS=-g
LDFLAGS=

test_basic :  lecture.o
	g++ -o test $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test_basic test?
