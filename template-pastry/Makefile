SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS)) #elide .cpp

all:$(TARGETS)
	@echo $(TARGETS)

./variadic-template:./variadic-template.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./member-template:./member-template.cpp
	g++ -std=c++11 -o $@ -Wall $< 

clean:
	rm -rf ./$(TARGETS)
