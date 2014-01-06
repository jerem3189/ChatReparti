CC=clang++
CFLAGS=-Wall -g -pthread -Wuninitialized -O1 -Wunused-parameter 
LDFLAGS=-pthread
EXEC=server.exe clean
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

server.exe: $(OBJ)
	$(CC) -o bin/$@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f src/*.o
