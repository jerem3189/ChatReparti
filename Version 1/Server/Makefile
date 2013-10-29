CC=g++
CFLAGS=-Wall -g
LDFLAGS=lpthread
EXEC=server
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

server: $(OBJ)
	$(CC) -o bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o obj/$@ -c $< $(CFLAGS)

clean:
	rm -f *.o
