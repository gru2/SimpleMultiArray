
OPT_FLAGS = -g

CPPFLAGS = $(OPT_FLAGS) -I.

TARGETS = SimpleMultiArrayTest

all: $(TARGETS)

SimpleMultiArrayTest: SimpleMultiArrayTest.o
	g++ -o SimpleMultiArrayTest SimpleMultiArrayTest.o

%.o: %.cpp
	g++ -c $(CPPFLAGS) $< -o $@

clean::
	-rm -vf $(TARGETS) *.o
