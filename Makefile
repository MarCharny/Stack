# building googletest system 
build_googletest: googletest
	mkdir $@
	cd $@ && cmake ../$< && make && make install

clean_googletest: build_googletest
	rm -rd $<

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CC = g++

CFLAGS = -std=c++14 -Wall -Wextra -lgtest -lgtest_main -pthread

ifeq ($(DEBUG),1)
	CFLAGS += -g
else
	CFLAGS += -O2
endif

INCLUDES = \
	include/Stack.hpp

CFLAGS += -I $(abspath include)

SOURCES = \
	StackTests.cpp
OBJECTS = $(SOURCES:%.cpp=build/%.o)
TEST = build/longNumberTest
EXECPI = build/CalculatePi

default: $(EXECUTABLE)

$(TEST): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


build/%.o: src/%.cpp $(INCLUDES)
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

test: $(TEST)
	./$(TEST)	

clean:
	rm -rf build

.PHONY: test clean default

	
	