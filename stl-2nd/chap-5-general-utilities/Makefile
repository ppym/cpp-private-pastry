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

./shared-ptr-cyclic-ref:./shared-ptr-cyclic-ref.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./weak-ptr1:./weak-ptr1.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./weak-ptr2:./weak-ptr2.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./weak-ptr3:./weak-ptr3.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./weak-ptr4:./weak-ptr4.cpp
	g++ -std=c++11 -o $@ -Wall $< 

./weak-ptr5:./weak-ptr5.cpp
	g++ -std=c++11 -o $@ -Wall $< -pthread

./unique-ptr:./unique-ptr.cpp
	g++ -std=c++11 -o $@ -Wall $< 

clean:
	rm -rf ./$(TARGETS)
