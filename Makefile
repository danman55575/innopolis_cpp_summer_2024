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
	$(CC) $(FLAGS) -o myapp main.o tknparser.o $(TEST_FLAGS)

main.o: main.cpp tknparser.hpp
	$(CC) $(FLAGS) -c main.cpp $(TEST_FLAGS)

tknparser.o: tknparser.cpp tknparser.hpp
	$(CC) $(FLAGS) -c tknparser.cpp

clean:
	rm -rf $(OBJECTS)
