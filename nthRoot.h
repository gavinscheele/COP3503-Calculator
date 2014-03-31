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
class nthRoot : public Expression{
public:
    nthRoot(int root, int operand);
    ~nthRoot();
    Expression simplify();
    
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;
private:
    int coefficient;
    int operand;
    int root;
};
#endif /* defined(__Calculator__nthRoot__) */

