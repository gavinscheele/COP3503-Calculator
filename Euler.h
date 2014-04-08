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
public:
    Euler();
    ~Euler();
    
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    string toString();
    Rational* getCoefficient();
    void setCoefficient(Rational* x);
    ostream& print(std::ostream& output) const;
private:
    Rational* coefficient;
};
#endif /* defined(__Calculator__Euler__) */

