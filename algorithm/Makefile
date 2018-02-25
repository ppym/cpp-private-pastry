SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS)) #elide .cpp

all:$(TARGETS)
	@echo "make all done " $(TARGETS)

clean:
	rm -rf ./$(TARGETS)

./knapsack1:./knapsack1.cpp
	g++ -std=c++11 -o $@ -Wall $< 

