SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS)) #elide .cpp

all:$(TARGETS)
	@echo $(TARGETS)

./first-test:./first-test.cpp
	g++ -o $@ -Wall $< 

./base-class-array:./base-class-array.cpp
	g++ -o $@ -Wall $< 

./operator-new:./operator-new.cpp
	g++ -o $@ -Wall $< 

./operator-new-debug:./operator-new-debug.cpp
	g++ -o $@ -Wall $< 

./mem-leak-trace:./mem-leak-trace.cpp
	g++ -o $@ -Wall $< -g -pthread

clean:
	rm -rf ./$(TARGETS)
