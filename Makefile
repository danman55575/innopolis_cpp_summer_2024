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
	$(CC) $(FLAGS) -o myapp main.o format.o base_substitution.o format_exceptions.o $(TEST_FLAGS)

main.o: main.cpp format.cpp format.hpp
	$(CC) $(FLAGS) -c main.cpp

format.o: format.cpp format.hpp base_substitution.o format_exceptions.o
	$(CC) $(FLAGS) -c format.cpp

base_substitution.o: base_substitution.cpp base_substitution.hpp
	$(CC) $(FLAGS) -c base_substitution.cpp

format_exceptions.o: format_exceptions.cpp format_exceptions.hpp
	$(CC) $(FLAGS) -c format_exceptions.cpp

clean:
	rm -rf $(OBJECTS)