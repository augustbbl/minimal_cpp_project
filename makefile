##########################################################################################

TARGET := asdf
OBJECTS := 

TEST_DIR := test
TEST_TARGET := test_$(TARGET)
TEST_OBJECTS := $(OBJECTS:%.o=$(TEST_DIR)/%.test.o) test/unique_ptr.test.o

INCLUDE_DIR := include

CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra -Wpedantic -Werror -g -fsanitize=address -fsanitize=leak -fsanitize=undefined 
CXXFLAGS := -std=c++1y $(CFLAGS) -I $(INCLUDE_DIR)

##########################################################################################

default: $(OBJECTS) init.o
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

test: $(OBJECTS) $(TEST_OBJECTS) $(TEST_DIR)/init.test.o
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_TARGET)
	./$(TEST_TARGET)

%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

%.o: %.c %.h
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
