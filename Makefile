 # Makefile
 # Auguste Brown
 # COMP15
 # Spring 2020
 #
 # Creates executables relating to FlooHub

CXX      = /usr/sup/bin/clang++
CXXFLAGS = --std=c++11 -Wshadow -Wall -Wextra -g3

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

findpath: main.o Location.o Graph.o
	$(CXX) -o $@ $^

testgraph: testGraph.o Location.o Graph.o
	$(CXX) -o $@ $^

clean: 
	rm -f rt findpath *.o

provide:
	provide comp15 rt README Makefile main.cpp \
	        Node.h Graph.h Graph.cpp testGraph.cpp test_commands.txt 

# Add some rules for rt website
include Makefile.publish

