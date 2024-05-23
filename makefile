#CXX=/usr/local/bin/g++-13
CCOPT = -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD

CCLNFLAGS = -m64 -lm -lpthread
OPTIONS = -ansi -Wall -Wno-sign-compare $(CCLNFLAGS)

AUX = custom_types/ts.cpp generate_successors.cpp pruning_constraints.cpp algorithm_move.cpp get_map_binary_keys.cpp tasks/test_3_tasks.cpp tasks/test_4_tasks.cpp tasks/test_5_tasks.cpp tasks/test_6_tasks.cpp tasks/test_7_tasks.cpp tasks/test_8_tasks.cpp

all: gedf_test

gedf_test: schedtst.cpp $(AUX)
	clang++ $(OPTIONS) $(CCOPT) -Ofast -std=c++17 -o gedf_test schedtst.cpp $(AUX)

clean: 
	rm gfp_test





