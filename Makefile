TARGET := myapp.exe

SOURCES := $(wildcard *.cpp)

OBJECTS := $(SOURCES:.cpp=.o)

CC := g++

FLAGS := -std=c++20 -Wall -Werror -Wextra -Wno-unused-variable

TEST_FLAGS := -lgtest -lpthread

test: build
	./myapp.exe

build: $(TARGET)

$(TARGET): main.o allocator.o
	$(CC) $(FLAGS) -o myapp main.o allocator.o $(TEST_FLAGS)

main.o: main.cpp allocator.hpp
	$(CC) $(FLAGS) -c main.cpp $(TEST_FLAGS)

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) -c allocator.cpp

clean:
	rm -rf $(OBJECTS)
