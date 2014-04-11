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
    Pi *p = new Pi();
    Pi *pi = new Pi();
    Rational *a = new Rational(p,pi);
    Rational *b = new Rational(1,-8);
    Rational *c = new Rational(2,1);
    Integer *d = new Integer(4);
    Integer *e = new Integer(-1);
    Integer *f = new Integer(0);
    
    cout << *a << endl;
    cout << *a->subtract(d) << endl;
    cout << *a->multiply(e) << endl;
    cout << *a->divide(b) << endl;
    
    return 0;
}