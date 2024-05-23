#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


const unsigned short PROC_NUM = 2;


struct state {
    const TS& ts;
    
    unsigned short* c; // remaining execution time
    unsigned short* p; // time to next period
    bool* interferred; // interference flags
    bool* jobCouldBeReleasedEarlier; // used for certain pruning rules
    
    state(const TS& ts_): ts(ts_) {
        c = new unsigned short[ts.n];
        p = new unsigned short[ts.n];
        interferred = new bool[ts.n];
        jobCouldBeReleasedEarlier = new bool[ts.n];
        
        for (int i = 0; i < ts.n; i++) {
            c[i] = 0;
            p[i] = 0;
            interferred[i] = false;
            jobCouldBeReleasedEarlier[i] = false;
        }
    }
    
    // copy constructor
    state(const state& s) : ts(s.ts) {
        c = new unsigned short[ts.n];
        p = new unsigned short[ts.n];
        interferred = new bool[ts.n];
        jobCouldBeReleasedEarlier = new bool[ts.n];
        
        for (int i = 0; i < ts.n; i++) {
            c[i] = s.c[i];
            p[i] = s.p[i];
            interferred[i] = s.interferred[i];
            jobCouldBeReleasedEarlier[i] = s.jobCouldBeReleasedEarlier[i];
        }
    }
    
    state& operator=(const state& s) {
        if(this != &s) {
            for(unsigned short i = 0; i < ts.n; i++) {
                c[i] = s.c[i];
                p[i] = s.p[i];
                interferred[i] = s.interferred[i];
                jobCouldBeReleasedEarlier[i] = s.jobCouldBeReleasedEarlier[i];
            }
        }
        return *this;
    }
    
    
    bool operator<(const state& s) const {
        /*for(int i=0; i<n; i++) {
            if(c[i]<s.c[i]) return true; 
            if(s.c[i]<c[i]) return false; 
            if(p[i]<s.p[i]) return true; 
            if(s.p[i]<p[i]) return false; 
        }
        return false;*/
        
        float rt1 = 0;
        for (int i = 0; i < ts.n; i++) {
            if (c[i] > 0) rt1 += (float)(p[i] - c[i])/p[i];
            else rt1 += 1; // to be refined through C[i]
        }
        
        float rt2 = 0;
        for (int i = 0; i < ts.n; i++) {
            if (s.c[i] > 0) rt2 += (float)(s.p[i] - s.c[i])/s.p[i];
            else rt2 += 1; // to be refined through C[i]
        }
        
        if (rt1 > rt2) return true;
        else if (rt1 < rt2) return false;
        else {
            for(int i = 0; i < ts.n; i++) {
                if(c[i]<s.c[i]) return true; 
                if(s.c[i]<c[i]) return false; 
                if(p[i]<s.p[i]) return true; 
                if(s.p[i]<p[i]) return false; 
            }
        }
        
        return false;
    }
    
    
    
    
    
    // Time to next deadline of a task
    inline int d(int i) const { return max(p[i] - (ts.P[i] - ts.D[i]), 0); } 
    
    // Printing function
    void print() const {
        
        for (int i = 0; i < ts.n; i++) {
            cout << "( " << (int)c[i] << ", " << (int)p[i] << " )" << endl;
        }
    }
    
    // destructor
    ~state() {
        delete [] c;
        delete [] p;
        delete [] interferred;
        delete [] jobCouldBeReleasedEarlier;
    }
};
