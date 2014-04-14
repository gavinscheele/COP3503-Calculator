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
#include <math.h>
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
    Solver() {};
    ~Solver();
    string solve(bool floatingPoint);
    bool replace(std::string& str, const std::string& from, const std::string& to);

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
    string evaluateFloatString();
    Expression* bindToExpressionType(string e);
    

};
#endif /* defined(__Calculator__Solver__) */
