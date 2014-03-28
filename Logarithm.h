//
//  Logarithm.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Logarithm__
#define __Calculator__Logarithm__

#include <iostream>
#include "Expression.h"
class Logarithm : public Expression{
public:
    Logarithm(int base, int operand);
    ~Logarithm();
    Expression simplify();
    
    Expression* add(Expression* a, Expression* b);
    Expression* subtract(Expression* a, Expression* b);
    Expression* multiply(Expression* a, Expression* b);
    Expression* divide(Expression* a, Expression* b);
private:
    int base;
    int operand;
};
#endif /* defined(__Calculator__Logarithm__) */
