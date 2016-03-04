CXX=g++
INCLUDE=include
CXXFLAGS=-g -Wall -std=c++11
CXXFLAGS+=-I $(INCLUDE)

SRCDIR=src
OBJDIR=obj
BINDIR=bin

vpath %.o ./$(OBJDIR)
vpath %.cpp ./$(SRCDIR)
vpath %Test.cpp ./$(SRCDIR)/test

SRC = $(wildcard $(SRCDIR)/*.cpp)
TEST_SRC = $(wildcard $(SRCDIR)/test/*.cpp) 
TARGET_SRC= $(wildcard $(SRCDIR)/main/*.cpp)

OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TEST_TARGET = $(patsubst %.cpp,$(BINDIR)/test/%, $(TEST_SRC))
TARGET = $(patsubst %.cpp,$(BINDIR)/main/%, $(TARGET_SRC))


$(OBJ): | $(OBJDIR)

$(TEST_TARGET): | bin/test

$(TARGET): | bin/main

$(OBJDIR):
	@mkdir -p $@
$(BINDIR)/test:
	@mkdir -p $@
$(BINDIR)/main:
	@mkdir -p $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "$(CXX) $(CXXFLAGS) -c $< -o $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

 
.PHONY: clean

clean:
	@rm -rf $(OBJDIR) $(BINDIR) 
