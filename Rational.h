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
#include "Logarithm.h"
#include "Pi.h"
#include "Euler.h"
#include "Integer.h"
#include <sstream>
using namespace std;
class Rational : public Expression {
public:
    Rational(int numerator, int denominator);
    Rational(Expression* numerator, Expression* denominator);

    ~Rational();

    
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;
    Expression* geteDenominator();
    string toString();
    
    void seteDenominator(Expression* denominator);
    Expression* geteNumerator();
    
    
    void seteNumerator(Expression* numerator);
    int getNumerator();
    int getDenominator();
    bool hasIntegerOperands();
    
private:
    int findCommonFactor(int n);
    int numerator;
    int denominator;
    Expression *eNumerator;
    Expression *eDenominator;
    Expression* simplify(int num);
    Expression* simplify(Expression* exp);
    Expression* findCommonDenominator(Rational * a);
};
#endif /* defined(__Calculator__Rational__) */
