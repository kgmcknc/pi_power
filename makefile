CURDIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR = $(CURDIR)src
OUTDIR = $(CURDIR)obj
PRJNAME = $(shell basename $(CURDIR))
LIBRARIES = -lwiringPi

CC=g++
CFLAGS=-I$(SRCDIR) -DSPI_MASTER -DINTERFACE

SRC = $(wildcard $(SRCDIR)/*.cpp)
DEPS = $(wildcard $(SRCDIR)/*.h)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OUTDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(OUTDIR)/%.o: $(COMDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pi_power: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBRARIES)

objects:
	echo $(OBJ)
	
sources:
	echo $(SRC)

dependencies:
	echo $(DEPS)
	
includes:
	echo $(wildcard $(DEPS)/*)

.PHONY: clean

clean:
	rm -f $(OUTDIR)/*.o *~ core $(COMDIR)/*~

$(info $(shell mkdir -p $(OUTDIR)))