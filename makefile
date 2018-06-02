##########################################################################################

TARGET := 
TEST_TARGET := test_$(TARGET)
OBJECTS := 

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CXX := g++
CXXFLAGS := --std=c++1y

##########################################################################################

default: $(OBJECTS) init.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -o $(TARGET)

debug: $(OBJECTS) init.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) -g -fsanitize=address $^ -o $(TARGET)

test: $(OBJECTS) test.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -o $(TEST_TARGET)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)

tar: clean
	tar -cvzf *

zip: clean
	zip -r *

sandwich:
	@bash -c "if [[ $EUID -ne 0 ]]; then echo make\ it\ yourself.; else echo okay.; fi"

.PHONY: clean tar zip sandwich

##########################################################################################
