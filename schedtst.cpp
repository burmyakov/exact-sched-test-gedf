#include <iostream>
#include <string>
#include <fstream>
#include "custom_types/ts.h"
#include "tasks/test_3_tasks.h"
#include "tasks/test_4_tasks.h"
#include "tasks/test_5_tasks.h"
#include "tasks/test_6_tasks.h"
#include "tasks/test_7_tasks.h"
#include "tasks/test_8_tasks.h"
/*#include "tasks/test_9_tasks.h"
#include "tasks/test_10_tasks.h"
#include "tasks/test_11_tasks.h"
#include "tasks/test_12_tasks.h"*/


using namespace std;
ofstream fileResults;



int main(int argc, char* argv[]) {
    
    TS ts;
    unsigned short m;
    
    
    m = (unsigned short) strtoul(argv[1], NULL, 0);
    ts.n = (unsigned short) strtoul(argv[2], NULL, 0);
    
    int C, D, P;
    for (int i = 0; i < ts.n; i++) {
        C = (int) strtoul(argv[3+3*i], NULL, 0);
        D = (int) strtoul(argv[4+3*i], NULL, 0);
        P = (int) strtoul(argv[5+3*i], NULL, 0);
        ts.setTask(i, C, D, P);
    }
    
    /*cerr << "Number of processors?" << endl;
    cin >> m;
    cerr << "Number of tasks?" << endl;
    cin >> ts.n;
    
    bool implicitDeadlines = false;
    cerr << "Tasks have implicit deadlines? (1 - yes, 0 - no)" << endl;
    cin >> implicitDeadlines;
    
    unsigned short C, D, P;
    for (unsigned short i = 0; i < ts.n; i++) {
        cerr << "C[" << i << "]?" << endl;
        cin >> C;
        
        if (!implicitDeadlines) {
            cerr << "D[" << i << "]?" << endl;
            cin >> D;
        }
        
        cerr << "P[" << i << "]?" << endl;
        cin >> P;
        if (!implicitDeadlines) ts.setTask(i, C, D, P);
        else ts.setTask(i, C, P, P);
    }*/
    
    
    
    unsigned long int savedStatesNum = 0;
    unsigned long int visitedStatesNum = 0;
    unsigned long int savedStatesNumIncr = 0;
    unsigned long int visitedStatesNumIncr = 0;
    
    bool sched = true;
    
    unsigned long int t0;
    unsigned long int tExecution_p1;
    unsigned long int tExecutionTotal_p1 = 0;
    
    
    switch (ts.n) {
        case 3:
            t0 = clock();
            sched = test_3_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        case 4:
            t0 = clock();
            sched = test_4_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        case 5:
            t0 = clock();
            sched = test_5_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        case 6:
            t0 = clock();
            sched = test_6_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        case 7:
            t0 = clock();
            sched = test_7_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        case 8:
            t0 = clock();
            sched = test_8_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        /*case 9:
            t0 = clock();
            sched = test_9_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
        case 10:
            t0 = clock();
            sched = test_10_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
            tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
            
            savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
            break;
            
         case 11:
             t0 = clock();
             sched = test_11_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
             tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
             
             savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
             break;
             
         case 12:
             t0 = clock();
             sched = test_12_tasks(m, ts, savedStatesNumIncr, visitedStatesNumIncr);
             tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;
             
             savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
             break;*/
            
        default: cout << "No function defined to test " << ts.n << " tasks!" << endl;
    }
    
    const char* fileName = (argv[5+3*(ts.n)]);

    fileResults.open(fileName, ios::app);
    fileResults << "\t" << sched << "\t" << tExecutionTotal_p1 << "\t" << savedStatesNum;
    fileResults.close();
    
    cout << "v6d. with priors:\t" << (float)(tExecutionTotal_p1*1000000/CLOCKS_PER_SEC)/1000000 << " sec,  \t / " << savedStatesNum << " stored" << "  \t / " << visitedStatesNum << " visited";
    
    if (sched) cout << "  \t / SCHED" << endl;
    else cout << "  \t / UNSCHED" << endl;
    
    return sched;
}
