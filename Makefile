# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make test   - run all test suites.
#   make clean  - removes all files generated by make.

# Location of the source code.
SOURCE_DIR = ./src

# All tests produced by this Makefile.
# Remember to add new tests you created to the list.
TESTS = Integer_test
TEST_OBJ_FILES = $(shell echo "$(TESTS) " | sed 's/ /\.o /g')
TEST_TARGET_OBJ_FILES = $(shell echo "$(TESTS) " | sed 's/_test /\.o /g')

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ./googletest/googletest

CXX = g++
AR = ar
ARFLAGS = rv

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++0x

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

# Run all tests, method 1.
# test : $(TESTS)
# 	printf "%s\0" $^ | xargs -0 -I TEST bash -c ./TEST

# Run all tests, method 2.
test : all_tests
	./all_tests

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o *_test *_tests

# General rules.

%.o : $(SOURCE_DIR)/%.cc $(SOURCE_DIR)/%.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Build tests.

%_test.o : $(SOURCE_DIR)/%_test.cc \
               $(SOURCE_DIR)/%.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

%_test : %.o %_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

all_tests : $(TEST_TARGET_OBJ_FILES) $(TEST_OBJ_FILES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
