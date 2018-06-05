appname := przejproc

CC=gcc
CXX=g++
CXXFLAGS := -g -std=c++17

cppsourcefiles := $(shell find . -name "*.cpp")
cppobjectfiles := $(patsubst %.cpp, %.o, $(cppsourcefiles))

objects := $(cppobjectfiles)

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)



.PHONY: distclean
distclean: 
	rm -f $(objects) $(appname)

.PHONY: clean
clean: 
	rm -f $(objects)
