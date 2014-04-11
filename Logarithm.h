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
class Logarithm : public Expression{
public:
    Logarithm(int base, int operand);
    Logarithm::Logarithm(int base, Expression* eOperand);
    Logarithm::Logarithm(Expression* eBase, int operand){
    Logarithm::Logarithm(Expression* eBase, Expression* eOperand)
    ~Logarithm();
<<<<<<< HEAD
    Expression* simplify();

=======
    Expression simplify();
>>>>>>> 1ad63953519a972b908370cd7401ffca05cc861c
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;
private:
    int base;
    int operand;
    Expression* eBase;
    Expression* eOperand;
};
#endif /* defined(__Calculator__Logarithm__) */
