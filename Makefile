PROJECTNAME=sat-simulated-annealing

SRCDIR=./src
OBJDIR=./obj
BINDIR=./bin

CPPSRCS=$(wildcard $(SRCDIR)/*.cpp)
HSRCS=$(wildcard $(SRCDIR)/*.h)
OBJ=$(subst .cpp,.o,$(subst $(SRCDIR),$(OBJDIR),$(CPPSRCS)))

CXX=g++
CXXFLAGS=-c -g -Wall -lm -std=c++11
LDFLAGS=-g -Wall -lm -std=c++11

RM = rm -rf

all: objdir bindir $(PROJECTNAME)

$(PROJECTNAME): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $(BINDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) $< $(CXXFLAGS) -o $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(HSRCS)
	$(CXX) $< $(CXXFLAGS) -o $@

objdir:
	@ mkdir -p $(OBJDIR)

bindir:
	@ mkdir -p $(BINDIR)


clean:
	@ $(RM) $(OBJDIR) $(BINDIR)