#CXX=g++-4.8
#CXXFLAGS=-std=c++11 -O3
CXXFLAGS=-std=c++11 -g

all: testapp

test: testapp
	./testapp

testapp: lib.o test.o
	$(CXX) -pthread -g -Wall $^ -o $@

clean:
	-$(RM) -f *.o testapp results*.txt
