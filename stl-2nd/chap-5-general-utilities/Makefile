SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS)) #elide .cpp

all:$(TARGETS)
	@echo "make all done " $(TARGETS)

./pair:./pair.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./tuple:./tuple.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./shared_ptr:./shared_ptr.cpp
	g++ -std=c++11 -o $@ -Wall $< 

clean:
	rm -rf ./$(TARGETS)
