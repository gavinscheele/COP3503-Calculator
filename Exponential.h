//
//  Exponent.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Exponential__
#define __Calculator__Exponential__

#include <iostream>
#include "Expression.h"
#include "Rational.h"
#include "Integer.h"
#include "nthRoot.h"

class Exponential : public Expression{
public:
    Exponential(Expression* base, Rational* exponent);
    ~Exponential();
    Expression* exponentiate();
    Rational getExponent();
    Expression* getBase();
    void setExponent(Rational e);
    void setBase(Expression* e);
    bool canExponentiate();
    string toString();

    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;

private:
    Expression* base;
    Rational* exponent;
};
#endif /* defined(__Calculator__Exponential__) */
