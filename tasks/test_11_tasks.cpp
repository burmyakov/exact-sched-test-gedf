#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include "../custom_types/ts.h"
#include "../custom_types/state.h"
#include "../custom_types/map_11_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"



using namespace std;

namespace NS_11tasks {

vector<my_bitset> bKeys_pj;

unsigned long savedStatesNum = 0;
unsigned long visitedStatesNum = 0;







bool find_dominating_state(const state& s, const unsigned short m, mt24& visitedStates, const string priorities) {
    
    mt24::iterator itr24;
    itr24 = visitedStates.find(priorities);
    if (itr24 != visitedStates.end()) {
        
        unsigned int keysNum_pj = 0;
        get_keys_pj(s, m, keysNum_pj, bKeys_pj);
        
        for (unsigned int i23 = 0; i23 < keysNum_pj; i23++) {
            
            mt23::iterator itr23;
            itr23 = (itr24->second).find(bKeys_pj[i23]);
            if (itr23 != (itr24->second).end()) {
                
                for (mt22::iterator itr22 = (itr23->second).begin(); itr22 != (itr23->second).end(); itr22++) {
                    if (itr22->first > s.p[10]) break;
                    else {
                        
                        for (mt21::iterator itr21 = (itr22->second).begin(); itr21 != (itr22->second).end(); itr21++) {
                            if (itr21->first > s.p[9]) break;
                            else {
                                
                                for (mt20::iterator itr20 = (itr21->second).begin(); itr20 != (itr21->second).end(); itr20++) {
                                    if (itr20->first > s.p[8]) break;
                                    else {
                                        
                                        for (mt19::iterator itr19 = (itr20->second).begin(); itr19 != (itr20->second).end(); itr19++) {
                                            if (itr19->first > s.p[7]) break;
                                            else {
                                                
                                                for (mt18::iterator itr18 = (itr19->second).begin(); itr18 != (itr19->second).end(); itr18++) {
                                                    if (itr18->first > s.p[6]) break;
                                                    else {
                                                        
                                                        for (mt17::iterator itr17 = (itr18->second).begin(); itr17 != (itr18->second).end(); itr17++) {
                                                            if (itr17->first > s.p[5]) break;
                                                            else {
                                                                
                                                                for (mt16::iterator itr16 = (itr17->second).begin(); itr16 != (itr17->second).end(); itr16++) {
                                                                    if (itr16->first > s.p[4]) break;
                                                                    else {
                                                                        
                                                                        for (mt15::iterator itr15 = (itr16->second).begin(); itr15 != (itr16->second).end(); itr15++) {
                                                                            if (itr15->first > s.p[3]) break;
                                                                            else {
                                                                                
                                                                                for (mt14::iterator itr14 = (itr15->second).begin(); itr14 != (itr15->second).end(); itr14++) {
                                                                                    if (itr14->first > s.p[2]) break;
                                                                                    else {
                                                                                        
                                                                                        for (mt13::iterator itr13 = (itr14->second).begin(); itr13 != (itr14->second).end(); itr13++) {
                                                                                            if (itr13->first > s.p[1]) break;
                                                                                            else {
                                                                                                
                                                                                                for (mt12::iterator itr12 = (itr13->second).begin(); itr12 != (itr13->second).end(); itr12++) {
                                                                                                    if (itr12->first > s.p[0]) break;
                                                                                                    else {
                                                                                                        
                                                                                                        for (mt11::reverse_iterator itr11 = (itr12->second).rbegin(); itr11 != (itr12->second).rend(); itr11++) {
                                                                                                            if (itr11->first < s.c[10]) break;
                                                                                                            else {
                                                                                                                for (mt10::reverse_iterator itr10 = (itr11->second).rbegin(); itr10 != (itr11->second).rend(); itr10++) {
                                                                                                                    if (itr10->first < s.c[9]) break;
                                                                                                                    else {
                                                                                                                        for (mt9::reverse_iterator itr9 = (itr10->second).rbegin(); itr9 != (itr10->second).rend(); itr9++) {
                                                                                                                            if (itr9->first < s.c[8]) break;
                                                                                                                            else {
                                                                                                                                for (mt8::reverse_iterator itr8 = (itr9->second).rbegin(); itr8 != (itr9->second).rend(); itr8++) {
                                                                                                                                    if (itr8->first < s.c[7]) break;
                                                                                                                                    else {
                                                                                                                                        for (mt7::reverse_iterator itr7 = (itr8->second).rbegin(); itr7 != (itr8->second).rend(); itr7++) {
                                                                                                                                            if (itr7->first < s.c[6]) break;
                                                                                                                                            else {
                                                                                                                                                for (mt6::reverse_iterator itr6 = (itr7->second).rbegin(); itr6 != (itr7->second).rend(); itr6++) {
                                                                                                                                                    if (itr6->first < s.c[5]) break;
                                                                                                                                                    else {
                                                                                                                                                        for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend(); itr5++) {
                                                                                                                                                            if (itr5->first < s.c[4]) break;
                                                                                                                                                            else {
                                                                                                                                                                for (mt4::reverse_iterator itr4 = (itr5->second).rbegin(); itr4 != (itr5->second).rend(); itr4++) {
                                                                                                                                                                    if (itr4->first < s.c[3]) break;
                                                                                                                                                                    else {
                                                                                                                                                                        for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend(); itr3++) {
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
        }
    }
    
    return false;
}








void add_state_to_map(const state& s, mt24& visitedStates, const string priorities) {
    my_bitset bs_pj;
    for (int i = 0; i < s.ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);
    visitedStates[priorities][bs_pj][s.p[10]][s.p[9]][s.p[8]][s.p[7]][s.p[6]][s.p[5]][s.p[4]][s.p[3]][s.p[2]][s.p[1]][s.p[0]][s.c[10]][s.c[9]][s.c[8]][s.c[7]][s.c[6]][s.c[5]][s.c[4]][s.c[3]][s.c[2]][s.c[1]][s.c[0]] = true;
}



// Compare a given state s with the ones stored in map "generated".
// Discard state s, if some other state from the map dominates it;
// Otherwise, add state s into the map
bool update_map(const state& s, const unsigned short m, mt24& visitedStates) {
    
    // To check: to reuse "perm" values from "examined states" for efficiency ???
    // How to aggregate task priorities in a more efficient way (string, unsigned int, long) ?
    unsigned short* perm = new unsigned short [s.ts.n];
    sort_tasks_by_priorities(s, perm);
    string priorities = "";
    for (int i = 0; i < s.ts.n; i++) priorities += to_string(perm[i]*pow(100,i));
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
                if (s.p[i] == 0) {noReleasePossible = false; break;}
            
            if (noReleasePossible) iterateScheduler = true;
        } else return algMoveCode; // state is either pruned or unschedulable
    } // end of scheduler iterations
    
    return algMoveCode;
}




bool populate(const unsigned short m, const TS& ts) {
    
    init(m, ts);
    
    bool schedulable = true;
    short stateCode;
    mt24 generated;
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
                for (int successorItr = 0; successorItr < successors.size(); successorItr++)
                    if (check_adversary_pruning_conditions(successors[successorItr], m))
                        q.push(successors[successorItr]);
            }
        } else {} // this state is pruned
    }

    q = priority_queue <state>();
    generated.clear();
    return schedulable;
}
} // end of namespace NS_11tasks_p2





bool test_11_tasks(const unsigned short m_, const TS& ts_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {
    
    bool schedulable = NS_11tasks::populate(m_, ts_);
    savedStatesNum_ = NS_11tasks::savedStatesNum;
    visitedStatesNum_ = NS_11tasks::visitedStatesNum;
    
    return schedulable;
}
