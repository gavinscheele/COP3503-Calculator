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
   // Solver *solver = new Solver("412 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
   // cout << solver->solve() << endl;
    Expression *a = new Rational(1,2);
    Expression *b = new Integer(-4);
    cout << *a->add(b) << endl;
    
    return 0;
}