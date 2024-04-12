# Pelda Makefile a generikus tomb feladat megoldasanak forditasara 
# Solaris (ural2) es Linux ala.

# forditando obj. fajlok
objs = gen_array_iter2_test.o

# headerek, melyektol az egyszeruseg kedveert minden fugg
heads = gen_array_iter2.hpp

prog = gen_array_iter2_test         # a program neve

CXX = g++                           # a C++ fordito neve
CXXFLAGS = -pedantic -Wall          # C++ kapcsolok: legyen bobeszedu, 
CXXFLAGS += -g                      # ... es forduljon debug info is

# alapertelmezett cel: tesztprogram linkelese
all: $(prog)

$(prog): $(objs) $(objs2)
	$(CXX) $(objs) $(objs2) -o $@

$(objs): $(heads)

# takaritas igeny szerint
clean:
	rm -f $(objs) $(prog)
