//
//  Euler.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Euler__
#define __Calculator__Euler__

#include <iostream>
#include "Expression.h"

class Euler : public Expression{
    Euler();
    ~Euler();
    
    Expression* add(Expression* a, Expression* b);
    Expression* subtract(Expression* a, Expression* b);
    Expression* multiply(Expression* a, Expression* b);
    Expression* divide(Expression* a, Expression* b);
private:
    int coefficient;
};
#endif /* defined(__Calculator__Euler__) */
