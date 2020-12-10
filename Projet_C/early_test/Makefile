CFLAGS=-g -Wall

all: testParser.o

testParser: testLecture.o
	g++ -o testLecture $^


%.o	:%.cpp
	g++ -c  $< $(CFLAGS)

clean :
	rm -f *.o  *~ test
