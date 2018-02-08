OBJECT=public-class-data-members-bitwise public-struct-data-members-bitwise \
	private-data-members-bitwise

all:$(OBJECT)

./public-class-data-members-bitwise:./public-class-data-members-bitwise.cpp
	g++ -o $@ -Wall $<

./public-struct-data-members-bitwise:./public-struct-data-members-bitwise.cpp
	g++ -o $@ -Wall $<

./private-data-members-bitwise:./private-data-members-bitwise.cpp
	g++ -o $@ -Wall $< 

clean:
	rm -rf ./$(OBJECT)
