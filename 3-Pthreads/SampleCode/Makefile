all: pthread_example

pthread_example: main.o
	g++ main.o -lpthread -o pthread_example

main.o: 
	g++ -c main.cpp -pthread 

clean:
	rm -rf *.o pthread_example
