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
class Exponential : public Expression{
public:
    Exponential(Expression base, Expression exponent);
    ~Exponential();
    Expression exponentiate();
    
    Expression* add(Expression* a, Expression* b);
    Expression* subtract(Expression* a, Expression* b);
    Expression* multiply(Expression* a, Expression* b);
    Expression* divide(Expression* a, Expression* b);
    
private:
    Expression* base;
    Expression* exponent;
};
#endif /* defined(__Calculator__Exponential__) */
