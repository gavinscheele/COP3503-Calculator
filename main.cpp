//
//  main.cpp
//  Calculator
//
//  Created by Gavin Scheele on 4/6/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Solver.h"
using namespace std;
int main(int argc, char * argv[])
{
    Solver *solver = new Solver("2 * 4rt:1 / ( 3 ^ pi ^ ( 1 / pi ) - 2011 * log_2:4 )");
    cout << solver->solve() << endl;
   // Expression *a = new Rational(1,2);
   // Expression *b = new Integer(-4);
   // cout << *a->add(b) << endl;
    
    return 0;
}