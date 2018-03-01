SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS)) #elide .cpp

all:$(TARGETS)
	@echo "make all done " $(TARGETS)

clean:
	rm -rf ./$(TARGETS)

./monk_monster:./monk_monster.cpp
	g++ -std=c++11 -o $@ -Wall $< 

