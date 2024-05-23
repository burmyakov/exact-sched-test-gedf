#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"





bool prefer(const state& s, int i, int k) {
    if(s.c[i]==0 && s.c[k]==0) return (i < k);         // no active job from i or k -- use default ordering
    if(s.c[i]==0 || s.c[k]==0) return s.c[i] > 0;     // only 1 active -- prefer that one
    if(s.d(i) == s.d(k)) return (i < k);             // break ties as necessary
    return (s.d(i) < s.d(k));                         // EDF rule
}



unsigned short delta_t(const state& s, const unsigned short m, const unsigned short* perm) {
    unsigned short dt = 1000;
    
    unsigned short i = 0;
    
    // Determining the time until the earliest next completion
    for (; i < m; i++) {
        // According to the GEDF priority ordering,
        // if s.c[[perm[i]]] == 0, then s.c[[perm[j]]] == 0 for j > i
        if (s.c[perm[i]] == 0) {break;}
        // If s.c[perm[i]] == 1, then then next scheduling instant is in 1 clock cycle
        // To check: if the number of pending jobs < m, is it possible to increase dt value?
        else if (s.c[perm[i]] == 1) {dt = 1; return dt;}
        // Other cases for s.c[perm[i]] > 1
        else if (s.c[perm[i]] < dt) dt = s.c[perm[i]];
    }
    
    // Determining the time until the earliest next release
    for (; i < s.ts.n; i++) {
        if ((s.p[perm[i]] == 0)||(s.p[perm[i]] == 1)) {dt = 1; return dt;}
        else if (s.p[perm[i]] < dt) dt = s.p[perm[i]];
    }
    
    return dt;
}



void sort_tasks_by_priorities(const state& s, unsigned short* perm) {
    
    for (unsigned short i = 0; i < s.ts.n; i++) perm[i] = i;
    
    for (unsigned short i = 0; i < s.ts.n; i++)
        for (unsigned short k = i+1; k < s.ts.n; k++)
            if (!prefer(s, perm[i], perm[k]))
                swap(perm[i], perm[k]);
}



void update_interferance_flags(state& s, const unsigned short m, const unsigned short pendJobsNum, const unsigned short* perm) {
    
    if (pendJobsNum > m)
        for (unsigned short i = 0; i < m; i++)
            s.interferred[perm[i]] = true;
}


bool condition_job_interference(const state& s, const unsigned short m, const unsigned short dt, const unsigned short* perm) {
    
    for (unsigned short i = 0; i < m; i++)
        if ((s.c[perm[i]] > 0) && (s.c[perm[i]] <= dt))
            if (!s.interferred[perm[i]]) {
                return false;
            }
    
    return true;
}



// Necessary condition of interference at job completion:
// Let:
// 1) some job not to interfer with any lower-priority job at its last execution time slot, just before its completion, and
// 2) the release time of that job could be shifted left to an earlier time
// Then: such an execution scenario can be discarded from the analysis
bool condition_of_interference_at_job_completion(const state& s, const unsigned short m, const unsigned short pendJobsNum, const unsigned short dt, const unsigned short* perm){

    if (pendJobsNum > m) return true;
    else {
        for (unsigned short j = 0; j < m; j++) {
            if ((s.c[perm[j]] > 0) && (s.c[perm[j]] <= dt)) {
                // this job is to complete its execution, but
                // this job will not interfer with any lower-priority job at its completion slot
                if (s.jobCouldBeReleasedEarlier[perm[j]]) return false; // the release of this job can be shifted to an earlier time
            }
        }
    }
    
    return true;
}



// return codes:
// -1 - deadline miss
// 0 - continue traversal of successors
// 1 - schedule can be discarded
short int algorithm_move(state& s, const unsigned short m) {

    unsigned short* perm = new unsigned short [s.ts.n];
    
    sort_tasks_by_priorities(s, perm);
    
    unsigned short pendJobsNum = 0;
    for (unsigned short i = 0; i < s.ts.n; i++) {
        if (s.c[i] > 0) {
            pendJobsNum++;
            if (pendJobsNum > m) break;
        }
    }
        
    update_interferance_flags(s, m, pendJobsNum, perm);
    
    unsigned short dt = delta_t(s, m, perm);
    //unsigned short dt = 1;
    bool interfCondsHold = (condition_job_interference(s, m, dt, perm) && condition_of_interference_at_job_completion(s, m, pendJobsNum, dt, perm));

    
    if (!interfCondsHold) {
        // Interference condition is violated.
        // Still, the condition for a deadeline miss must be checked;
        // There are cases, when a certain state violated the interference condition,
        // but misses some deadline as well
        for (int i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        delete [] perm;
        for (int i = 0; i < s.ts.n; i++) s.p[i] = max(s.p[i] - dt, 0);
        
        for (int i=0; i<s.ts.n; i++) {
            if (s.d(i) < s.c[i]) return -1; // deadline miss
        }
        
        return 1; // no deadline miss, but interference condition is violated
        
    } else { // Interference condition holds
        for (int i=0; i<m; i++) s.c[perm[i]] = max(s.c[perm[i]]-dt,0);
        delete [] perm;
        
        for (int i=0; i<s.ts.n; i++) {
            // Update ".jobCouldBeReleasedEarlier" flag based on the transition interval:
            // 1) t_i > dt: the flag is unchanged;
            // 2) t_i < dt (incl. case t_i == 0): task does not release its job at the earliest legal release time;
            // 3) if t_i == dt, then task can release a job at the next state (this would be the earliest possible release after the preceeding job release)
            // Regarding flag values for the initial state:
            // 1) the first move of the algorithm is from the adversary;
            // 2) the flag however is updated only in the algorithm move;
            // 3) thus, it is sufficient to set the flag to "false" for the initial state (see state(TS& ts_) constructor)
            if (s.p[i] == dt) s.jobCouldBeReleasedEarlier[i] = false;
            else if (s.p[i] < dt) s.jobCouldBeReleasedEarlier[i] = true;
            
            s.p[i] = max(s.p[i] - dt, 0);
            if (s.d(i) < s.c[i]) return -1; // return a deadline miss
        }
    }

    
    return 0;
}
