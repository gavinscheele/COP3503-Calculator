//
//  nthRoot.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__nthRoot__
#define __Calculator__nthRoot__

#include <iostream>
#include "Expression.h"
#include "Solver.h"
#include <math.h>
class nthRoot : public Expression{
public:
    nthRoot(int root, int operand, int coefficient);
    nthRoot(int root, Expression* eoperand, int coefficient);
    ~nthRoot();
    //Expression simplify();
    int* primeFactorization(int n, int div, int k);
    int localExponentiate(int under, int locExponent);
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    bool canAdd(Expression* b);
    bool canSubtract(Expression* b);
    bool canMultiply(Expression* b);
    bool canDivide(Expression* b);

    int getRoot();
    int getOperand();
    int getCoefficient();
    void setRoot(int n);
    void setOperand(int n);
    void setCoefficient(int n);
    ostream& print(std::ostream& output) const;
    Expression* simplify();
    string toString();
    bool isPrime(int n);

private:
    int coefficient;
    int operand;
    int root;
    int factors[50];
    Expression* eoperand;
};
#endif /* defined(__Calculator__nthRoot__) */

