CC=clang++
CFLAGS=-Wall -g -pthread 
LDFLAGS=-pthread
EXEC=server clean
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

server: $(OBJ)
	$(CC) -o bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f src/*.o
