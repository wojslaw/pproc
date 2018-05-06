appname := przejproc

CC=gcc
CXX=g++
CXXFLAGS := -g -std=c++11

cppsourcefiles := $(shell find . -name "*.cpp")
cppobjectfiles := $(patsubst %.cpp, %.o, $(cppsourcefiles))

objects := $(cppobjectfiles)

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

clean: 
	rm -f $(objects)

