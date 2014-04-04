//
//  Integer.h
//  Calculator
//
//  Created by Gavin Scheele on 3/28/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Integer__
#define __Calculator__Integer__

#include <iostream>
#include "Expression.h"
class Integer : public Expression{
public:
    Integer(int value);
    ~Integer();
    
    int getValue();
    void setValue(int n);
    
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    ostream& print(std::ostream& output) const;
    
private:
    int value;
};
#endif /* defined(__Calculator__Integer__) */
