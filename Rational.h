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
#include "Solver.h"
#include <sstream>
#include <stdexcept>
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
    string toString();

    Expression* geteDenominator();
    Expression* geteNumerator();
    void setDenominator(Expression* denominator);
    void setNumerator(Expression* numerator);
    int getNumerator();
    int getDenominator();

    bool hasIntegerOperands();
    
    
    bool canAdd(Expression* b);
    bool canSubtract(Expression* b);
    bool canMultiply(Expression* b);
    bool canDivide(Expression* b);

private:
    int findCommonFactor(int n);
    int numerator;
    int denominator;
    Expression *eNumerator;
    Expression *eDenominator;
    Expression* simplify(int num);
    Expression* simplify(Expression* exp);
    Rational* findCommonDenominator(Rational * a);
    void syncIntToExp();
    void syncExpToInt();
};
#endif /* defined(__Calculator__Rational__) */
