//
// Logarithm.h
// Calculator
//
// Created by Gavin Scheele on 3/27/14.
// Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Logarithm__
#define __Calculator__Logarithm__

#include <iostream>
#include "Expression.h"
#include "Integer.h"
#include <vector>
#include <math.h>
#include "Solver.h"

class Logarithm : public Expression{
public:
    Logarithm(int base, int operand);
    Logarithm(int base, Expression* eOperand);
    Logarithm(Expression* eBase, int operand);
    Logarithm(Expression* eBase, Expression* eOperand);
    ~Logarithm();
    int getBase();
    int getOperand();
    Expression* getEBase();
    Expression* getEOperand();

    void setBase(Expression* x);
    void setOperand(Expression* x);
    

    Expression* simplify();
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;
    string toString();
private:
    int base;
    int operand;
    Expression* eBase;
    Expression* eOperand;
    int* primeFactorization(int n);
    int factors[50];

};
#endif /* defined(__Calculator__Logarithm__) */
