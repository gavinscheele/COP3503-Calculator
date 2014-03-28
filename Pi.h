//
//  Pi.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Pi__
#define __Calculator__Pi__

#include <iostream>
#include "Expression.h"

class Pi : public Expression{
    Pi();
    ~Pi();
    
    Expression* add(Expression* a, Expression* b);
    Expression* subtract(Expression* a, Expression* b);
    Expression* multiply(Expression* a, Expression* b);
    Expression* divide(Expression* a, Expression* b);
private:
    int coefficient;
};
#endif /* defined(__Calculator__Pi__) */
