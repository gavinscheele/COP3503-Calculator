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
    Exponential(Expression* base, Expression* exponent);
    ~Exponential();
    Expression exponentiate();
    Expression exponantiate(Expression expression, int exponent)
    
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;
    
private:
    Expression* base;
    Expression* exponent;
};
#endif /* defined(__Calculator__Exponential__) */
