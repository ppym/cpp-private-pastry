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

clean:
	rm -rf ./$(TARGETS)
