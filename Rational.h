//
//  Rational.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Rational__
#define __Calculator__Rational__

#include <iostream>
#include "Expression.h"
using namespace std;
class Rational : public Expression {
public:
    Rational(int numerator, int denominator);
    ~Rational();
    Expression simplify();
    friend ostream& operator<<(ostream& output, const Rational& obj);
    
    Expression* add(Expression* a, Expression* b);
    Expression* subtract(Expression* a, Expression* b);
    Expression* multiply(Expression* a, Expression* b);
    Expression* divide(Expression* a, Expression* b);
private:
    int findCommonFactor(int n);
    int numerator;
    int denominator;
};
#endif /* defined(__Calculator__Rational__) */
