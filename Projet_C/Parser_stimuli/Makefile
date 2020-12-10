CFLAGS=-g -Wall

all : test

test : main_test.o Parser_stimuli.o

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test
