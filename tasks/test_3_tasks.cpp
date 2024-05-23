#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include "../custom_types/ts.h"
#include "../custom_types/state.h"
#include "../custom_types/map_3_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"


using namespace std;


namespace NS_3tasks {

vector<my_bitset> bKeys_pj;
unsigned long savedStatesNum = 0;
unsigned long visitedStatesNum = 0;







bool find_dominating_state(const state& s, const unsigned short m, mt8& visitedStates, const unsigned priorities) {
    
    mt8::iterator itr8;
    itr8 = visitedStates.find(priorities);
    if (itr8 != visitedStates.end()) {
        
        unsigned int keysNum_pj = 0;
        get_keys_pj(s, m, keysNum_pj, bKeys_pj);
        
        for (unsigned int i7 = 0; i7 < keysNum_pj; i7++) {
            
            mt7::iterator itr7;
            itr7 = (itr8->second).find(bKeys_pj[i7]);
            if (itr7 != (itr8->second).end()) {
                
                for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end(); itr6++) {
                    if (itr6->first > s.p[2]) break;
                    else {
                        
                        for (mt5::iterator itr5 = (itr6->second).begin(); itr5 != (itr6->second).end(); itr5++) {
                            if (itr5->first > s.p[1]) break;
                            else {
                                
                                for (mt4::iterator itr4 = (itr5->second).begin(); itr4 != (itr5->second).end(); itr4++) {
                                    if (itr4->first > s.p[0]) break;
                                    else {
                                        
                                        for (mt3::reverse_iterator itr3 = ((itr4->second)).rbegin(); itr3 != ((itr4->second)).rend(); itr3++) {
                                            if (itr3->first < s.c[2]) break;
                                            else {
                                                for (mt2::reverse_iterator itr2 = (itr3->second).rbegin(); itr2 != (itr3->second).rend(); itr2++) {
                                                    if (itr2->first < s.c[1]) break;
                                                    else {
                                                        for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                                                            if (itr1->first < s.c[0]) break;
                                                            else {
                                                                // state s is dominated by
                                                                // another state in the map
                                                                /*cout << "dominating state found:" << endl;
                                                                cout << itr8->first << endl;
                                                                cout << "( " << itr1->first << ", " << itr4->first << " )" << endl;
                                                                cout << "( " << itr2->first << ", " << itr5->first << " )" << endl;
                                                                cout << "( " << itr3->first << ", " << itr6->first << " )" << endl;*/
                                                                return true;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}






void add_state_to_map(const state& s, mt8& visitedStates, const unsigned priorities) {
    my_bitset bs_pj;
    for (int i = 0; i < s.ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);
    visitedStates[priorities][bs_pj][s.p[2]][s.p[1]][s.p[0]][s.c[2]][s.c[1]][s.c[0]] = true;
}


// Compare a given state s with the ones stored in map "generated".
// Discard state s, if some other state from the map dominates it;
// Otherwise, add state s into the map
bool update_map(const state& s, const unsigned short m, mt8& visitedStates) {
    
    // To check: to reuse "perm" values from "examined states" for efficiency ???
    // How to aggregate task priorities in a more efficient way (string, unsigned int, long) ?
    unsigned short* perm = new unsigned short [s.ts.n];
    sort_tasks_by_priorities(s, perm);
    unsigned priorities = 0;
    for (int i = 0; i < s.ts.n; i++) priorities += perm[i]*pow(10,i);
    delete [] perm;
    
    if (visitedStates.empty()) {add_state_to_map(s, visitedStates, priorities); savedStatesNum++; return true;} // adding initial state to map
    else {
        // States with no pending jobs are discarded,
        // as they are dominated by the intial state {(0,0)}_i=1^n
        bool hasActiveJob = false;
        for (unsigned short j = 0; j < s.ts.n; j++)
            if (s.c[j] > 0) {hasActiveJob = true; break;}
        
        if (hasActiveJob) {
            if (find_dominating_state(s, m, visitedStates, priorities)) return false; // State s is dominated by some other state stored in map "generated"
            else {add_state_to_map(s, visitedStates, priorities); savedStatesNum++; return true;} // State s added into map "generated" 
        } else return false; // A given state is dominated by an initial state {(0,0)}_i=1^n
    }
}


void init(const unsigned short m, const TS& ts) {    
    bKeys_pj.reserve(pow(2.0, ts.n));
    return;
}


// Explore the successors of a given state s;
// Return codes:
// 0 - the successors of this state should be explored further;
// 1 - state is pruned by ALG condition;
// -1 - state is unschedulable
short explore_state(state& s, const unsigned short m) {

    short algMoveCode = 0;
    bool iterateScheduler = true;
    bool noReleasePossible;
    
    // Iterate scheduler until one of these conditions is meet:
    // - state is unschedulable;
    // - state can be pruned due to ALG or ADV pruning rules;
    // some task can release a new job, that is some p[i] becomes 0
    while (iterateScheduler) {
        iterateScheduler = false;
        visitedStatesNum++;
        
        algMoveCode = algorithm_move(s, m);
        if (algMoveCode == 0) {
            noReleasePossible = true;
            for (unsigned short i = 0; i < s.ts.n; i++)
                if (s.p[i] == 0) {noReleasePossible = false; return algMoveCode;}
            
            if (noReleasePossible) {iterateScheduler = true;}
        } else return algMoveCode; // state is either pruned or unschedulable
    } // end of scheduler iterations
    
    return algMoveCode;
}






bool populate(const unsigned short m, const TS& ts) {
    
    init(m, ts);
    
    bool schedulable = true;
    short stateCode;
    mt8 generated;
    vector<state> successors;
    
    state s(ts);
    priority_queue<state> q;
    q.push(s);
    
    while (!q.empty()) {
        s = q.top();
        q.pop();
        
        stateCode = explore_state(s, m);
        if (stateCode == -1) {schedulable = false; return schedulable;}
        else if (stateCode == 0) {
            // Check if a given state is dominated by any other state stored in map "generated"
            if (update_map(s, m, generated)) {
                generate_successors(s, m, successors);
                for (int successorItr = 0; successorItr < successors.size(); successorItr++) {
                    if (check_adversary_pruning_conditions(successors[successorItr], m))
                        q.push(successors[successorItr]);
                }
            }
        } else {} // this state is pruned
    }

    q = priority_queue <state>();
    generated.clear();
    return schedulable;
}
} // end of namespace NS_3tasks





bool test_3_tasks(const unsigned short m_, const TS& ts_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {
    
    bool schedulable = NS_3tasks::populate(m_, ts_);
    savedStatesNum_ = NS_3tasks::savedStatesNum;
    visitedStatesNum_ = NS_3tasks::visitedStatesNum;
    
    return schedulable;
}
