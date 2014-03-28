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
    //need to find a way to split stirng into expressions and call the simplify methods
    //here is an example of using the Expression methods
    
    /* Rational a = *new Rational(4, 6);
     a.simplify();
     cout << a << endl;
     
     Rational b = *new Rational(9,4);
     b.simplify();
     cout << b << endl;
     
     cout << a.canAdd(&b) << endl;
     */
    
    
    return localExpression;
}
