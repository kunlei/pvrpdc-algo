SYSTEM = x86-64_osx
LIBFORMAT = static_pic
CPLEXDIR = /Applications/CPLEX_Studio129/cplex
CONCERTDIR = /Applications/CPLEX_Studio129/concert

# Link options and libraries
CPLEXLIBDIR = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)
CCLNFLAGS = -lconcert -lilocplex -lcplex -lm -pthread

# include header files
CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR = $(CPLEXDIR)/include
BOOSTINCDIR = /usr/local/include/

CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -DIL_STD -std=c++17 -pthread
LDFLAGS  := -L/usr/lib -lstdc++ -L/usr/local/lib -lboost_date_time $(CCLNFLAGS)
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := ./
TARGET   := main
INCLUDE  := -I. -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) -I$(BOOSTINCDIR)
SRC      :=                      \
	$(wildcard src/data/*.cpp) \
	$(wildcard *.cpp) \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) -o $@ -c $< $(CXXFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) $(CCLNDIRS) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) 

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*