CFLAGS=-g -Wall

all: testParser.o

test: AND.o
	g++ -o test $^


%.o	:%.cpp
	g++ -c  $< $(CFLAGS)

clean :
	rm -f *.o  *~ test
