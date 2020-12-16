CFLAGS=-g -Wall

all : test

test : main_test.o Parser_stimuli.o ../Parser_gate/Parser_gate.o ../Porte/Combinatoire/And.o ../Porte/Gate_comb.o ../Porte/Gate_mux.o ../Porte/Gate.o ../Porte/Gate_out.o ../Porte/Combinatoire/Inv.o ../Porte/Combinatoire/Nand.o ../Porte/Combinatoire/Nor.o ../Porte/Combinatoire/Or.o ../Porte/Combinatoire/Xnor.o ../Porte/Combinatoire/Xor.o
	g++ -o test $^ $(LDFLAGS)

%.o:%.cc
	g++ $(CFLAGS) -c -g $^

clean:
	rm -f *.o *~ test ../Parser_gate/*.o ../Porte/*.o ../Porte/Combinatoire/*.o
