//
//  Solver.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Solver.h"
Solver::Solver(std::string a){
    this->localExpression = a;
}
Solver::~Solver(){
    
}
std::string Solver::solve(){
    //need to find a way to split string into expressions and call the simplify methods
    //here is an example of using the Expression methods
    
 /* Expression *a = new Pi();
    Expression *b = new Pi();

    cout << *a << endl;
    Expression *c = new Rational(a, b);
    cout << *c << endl;
    Expression *d = new Rational(9,4);
    cout << *d << endl;
    Expression *e = new Euler();
    cout << *e << endl;
    Expression *f = new Integer(2);
    Expression *g = new Integer(3);
    Expression *h = new Exponential(f,g);
    cout << *h << endl;
    Expression *i = new Logarithm(2,3);
    cout << *i << endl;
    Expression *j = new nthRoot(3,8);
    cout << *j << endl;
    
    Expression *k = new Euler();
    Expression *l = new Rational(9,4);
    Expression *m = new Rational(k,l);
    cout << *m << endl;  */

    
    
    
    
    
    return "Result: " + localExpression;
}

