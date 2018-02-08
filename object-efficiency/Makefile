SRCS=$(wildcard *.cpp)
TARGETS=$(patsubst %.cpp,%,$(SRCS)) #elide .cpp

all:$(TARGETS)
	@echo $(TARGETS)

./public-class-data-members-bitwise:./public-class-data-members-bitwise.cpp
	g++ -o $@ -Wall $<

./public-struct-data-members-bitwise:./public-struct-data-members-bitwise.cpp
	g++ -o $@ -Wall $<

./private-data-members-bitwise:./private-data-members-bitwise.cpp
	g++ -o $@ -Wall $< 

./single-inheritance-bitwise:./single-inheritance-bitwise.cpp
	g++ -o $@ -Wall $< 

./multiple-inheritance-bitwise:./multiple-inheritance-bitwise.cpp
	g++ -o $@ -Wall $< 

./single-inheritance-one-level-virtual-func:./single-inheritance-one-level-virtual-func.cpp
	g++ -o $@ -Wall $< 

./single-inheritance-two-level-virtual-func:./single-inheritance-two-level-virtual-func.cpp
	g++ -o $@ -Wall $< 

./abstract-data-type-virtual-func:./abstract-data-type-virtual-func.cpp
	g++ -o $@ -Wall $< 

./multiple-inheritance-virtual-func:./multiple-inheritance-virtual-func.cpp
	g++ -o $@ -Wall $< 

./multiple-virtual-inheritance-one-level:./multiple-virtual-inheritance-one-level.cpp
	g++ -o $@ -Wall $< 

./multiple-virtual-inheritance-two-level:./multiple-virtual-inheritance-two-level.cpp
	g++ -o $@ -Wall $< 

clean:
	rm -rf ./$(TARGETS)
