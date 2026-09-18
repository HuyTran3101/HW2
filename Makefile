all: 
	g++ -Wall -g -O3 TimeCode.cpp TimeCodeTests.cpp -o tct

clean: 
	rm -f tct