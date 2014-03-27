//
//  Expression.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Expression__
#define __Calculator__Expression__

#include <iostream>

class Expression {
public:
    Expression();
    bool canAdd(Expression a, Expression b);
    bool canSubtract(Expression a, Expression b);
    bool canMultiply(Expression a, Expression b);
    bool canDivide(Expression a, Expression b);
    virtual Expression add(Expression a, Expression b);
    virtual Expression subtract(Expression a, Expression b);
    virtual Expression multiply(Expression a, Expression b);
    virtual Expression divide(Expression a, Expression b);

};
#endif /* defined(__Calculator__Expression__) */
