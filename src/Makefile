CXX := g++
TARGET := ../bin/TPLE
OPENMPFLAG := -fopenmp
CXXFLAGS := -std=c++11 -O3 -Wall -Wextra
INCLUDE := source/include
SRC_DIRS := source\
			source/lib\
          source/lib/InputDataHandler\
          source/lib/Calculator\
          source/lib/Graph\
          source/lib/GraphHandler\
          source/lib/ShortestPath\
          source/lib/Agent
SRCS := $(wildcard $(SRC_DIRS:=/*.cpp))
OBJS := $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

ifndef BOOST_LIBRARY_PATH
BOOST_LIBRARY_PATH := ""
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ -lpthread $(OPENMPFLAG)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OPENMPFLAG) -I $(INCLUDE) -isystem $(BOOST_LIBRARY_PATH) -MMD -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS) $(DEPS)

ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_CASE_ID := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_CASE_ID):;@:)
endif

test: $(TARGET)
	@echo test on case$(TEST_CASE_ID)

.PHONY: all clean test
-include $(DEPS)