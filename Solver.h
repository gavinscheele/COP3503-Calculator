//
//  Solver.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Solver__
#define __Calculator__Solver__

#include <iostream>
#include <vector>
#include <stack>
#include <iostream>
#include "Expression.h"
#include "Logarithm.h"
#include "Pi.h"
#include "Euler.h"
#include "Rational.h"
#include "Exponential.h"
#include "Integer.h"
#include "nthRoot.h"

using namespace std;
class Solver{
public:
    Solver(string a);
    ~Solver();
    string solve();
private:
    string localExpression;
    vector<string> expressions;
    stack<string> tokenStack;
    string output;
    void shuntingYard();
    bool isAnOperator(string tkn);
    bool isLeftAssociative(string tkn);
    int getOperatorPrecedence(string tkn);
    string evaluateString();
    Expression* bindToExpressionType(string e);

};
#endif /* defined(__Calculator__Solver__) */
