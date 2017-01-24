# Include path to Empirical root--assume in adjacent
EMP_root = ../Empirical/
EMP_include = -I$(EMP_root)
#EMP_include := -I.

CXX_native := g++
OFLAGS_native := -O3
OFLAGS_debug := -g
CFLAGS_all := -Wall -Wno-unused-function -std=c++11


CFLAGS_native := $(CFLAGS_all) $(OFLAGS_native) $(EMP_include)
CFLAGS_debug := $(CFLAGS_all) $(OFLAGS_debug) $(EMP_include)

EVO_DEPEND := $(EMP_root)/evo/PopulationManager.h $(EMP_root)/evo/World.h
QUORUM_DEPEND := QuorumOrg.h QuorumManager.h

TARGETS := standard-grid-quorum mixed-grid-quorum grid-pools-quorum

$(TARGETS): % : %.cc $(EVO_DEPEND) $(QUORUM_DEPEND)
	$(CXX_native) $(CFLAGS_native) $< -o $@.out

debug-%: $*.cc $(EVO_DEPEND) $(QUORUM_DEPEND)
	$(CXX_NATIVE) $(CFLAGS_debug) $< -o $@.debug

all: $(TARGETS)

test:
	cd ./tests && make test

clean:
	rm -rf *.out
	rm -rf *.debug
