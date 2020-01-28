CXX=g++
CC=gcc
PIN_HOME = /usr/home/grads/courses/ple074/pin-2.10-45467-gcc.3.4.6-ia32_intel64-linux

DBG= -g -DVERBOSE
OPT= -O3

CXXFLAGS= -Wall -Wno-unknown-pragmas -Wno-deprecated $(DBG) $(OPT) -MMD

PIN_KIT=$(PIN_HOME)
KIT=1

include $(PIN_HOME)/source/tools/makefile.gnu.config

PINTOOL = sim_pin.so
#SOURCES = sim.cpp sim_pin.cpp trace.cpp 
SOURCES = sim_pin.cpp sim_uop.cpp
OBJECTS=$(SOURCES:.cpp=.o)


all: $(SOURCES) $(PINTOOL)

%.o : %.cpp  
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) $(OPT) $(DBG) -o $@ $<

$(PINTOOL): $(OBJECTS)
$(PINTOOL) : %.so : %.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) -o $@ $(OBJECTS) ${PIN_LPATHS} $(PIN_LIBS) -lz $(DBG)

clean:
	-rm -f *.so *.o *.out *.tested *.failed *.d

-include *.d


