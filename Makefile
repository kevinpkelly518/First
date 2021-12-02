CC = g++
CFLAGS = -Wall -std=c++11
OBJECTS = *.cpp

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main $(CFLAGS)

run: main
	./main -nr
	make clean

test: main
	./main -e
	make clean

clean:
	rm main