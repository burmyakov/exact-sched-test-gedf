#include <iostream>
#include <climits>
#include <vector>
#include "custom_types/ts.h"
#include "custom_types/state.h"

using namespace std;


void generate_successors(const state& s, const unsigned short m, vector<state>& successors) {
    
    successors.clear();
    unsigned int curSuccessorsNum;
    successors.push_back(s);
    
    for (unsigned short i = 0; i < s.ts.n; i++) {
        if (s.p[i] == 0) {
            curSuccessorsNum = successors.size();
            for (unsigned int successorItr = 0; successorItr < curSuccessorsNum; successorItr++) {
                successors.push_back(successors[successorItr]);
                successors[successorItr].c[i] = s.ts.C[i];
                successors[successorItr].p[i] = s.ts.P[i];
                successors[successorItr].interferred[i] = false;
            }
        }
    }
}
