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
    Rational *a = new Rational(1,4);
    Rational *b = new Rational(-1,8);
    Rational *c = new Rational(2,-1);
    Integer *d = new Integer(4);
    Integer *e = new Integer(-1);
    Integer *f = new Integer(0);
    
    cout << *a->add(c) << endl;
    cout << *a->subtract(b) << endl;
   // cout << *a->multiply(b) << endl;
    //cout << *a->divide(b) << endl;
    
    return 0;
}