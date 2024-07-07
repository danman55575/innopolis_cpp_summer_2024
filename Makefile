TARGET := myapp

SOURCES := $(wildcard *.cpp)

OBJECTS := $(SOURCES:.cpp=.o)

CC := g++

FLAGS := -std=c++20 -Wall -Werror -Wextra -Wno-unused-variable

TEST_FLAGS := -lgtest -lpthread

all: build

test: build lint check
	./$(TARGET)

lint: 
	cpplint --filter=-legal/copyright,-build/include_subdir --recursive .

check:
	cppcheck --enable=all --suppress=missingIncludeSystem -I src .

build: $(OBJECTS)
	$(CC) $(FLAGS) -o myapp main.o bigint.o mylist.o $(TEST_FLAGS)

main.o: main.cpp bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c main.cpp

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c bigint.cpp

mylist.o: mylist.cpp mylist.hpp
	$(CC) $(FLAGS) -c mylist.cpp

clean:
	rm -rf $(OBJECTS)