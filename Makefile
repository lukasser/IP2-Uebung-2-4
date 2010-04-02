all: uebung2_4

uebung2_4: main.o binary_tree.o
	g++ main.o binary_tree.o -Wall -o uebung2_4

main.o: main.cc
	g++ -c main.cc -Wall

binary_tree.o: binary_tree.cc
	g++ -c binary_tree.cc -Wall

clean:
	rm -rf *.o uebung2_4
