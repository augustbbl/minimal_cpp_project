##########################################################################################

TARGET := 
OBJECTS := 

TEST_DIR := test
TEST_TARGET := $(TEST_DIR)/test_$(TARGET)
TEST_OBJECTS := $(OBJECTS:%.o=$(TEST_DIR)/%.test.o)

CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -g -fsanitize=address 
CXX := g++
CXXFLAGS := --std=c++1y

##########################################################################################

default: $(OBJECTS) init.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -o $(TARGET)

test: $(OBJECTS) $(TEST_OBJECTS) $(TEST_DIR)/init.test.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) $^ -o $(TEST_TARGET)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $< -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(TEST_DIR)/*.o $(TARGET) $(TEST_TARGET)

tar: clean
	tar -cvzf *

zip: clean
	zip -r *

sandwich:
	@bash -c "if [[ $EUID -ne 0 ]]; then echo make\ it\ yourself.; else echo okay.; fi"

.PHONY: clean tar zip sandwich

##########################################################################################
