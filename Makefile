all: build

test: build check
	python3 ./test.py

check:
	cppcheck --enable=all --suppress=missingIncludeSystem -I src .

build:
	sudo python3 ./setup.py install
