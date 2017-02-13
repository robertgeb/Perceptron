all: perceptron

perceptron: perceptron.o
		gcc -o perceptron perceptron.o -Wall

perceptron.o: perceptron.c
		gcc -c perceptron.c

clean:
		rm perceptron.o perceptron
