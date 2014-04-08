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

using namespace std;

class Expression {
public:
    Expression();
    virtual ~Expression();
    bool canAdd(Expression* b);             //these methods are implemented in Expression.cpp. They do not change based on type.
    bool canSubtract(Expression* b);
    bool canMultiply(Expression* b);
    bool canDivide(Expression* b);
    friend ostream& operator<<(ostream &output, Expression &e);
    
    virtual ostream& print(std::ostream& output) const =0;
    virtual string toString() = 0;
    virtual Expression* add(Expression* a) = 0;
    virtual Expression* subtract(Expression* a) = 0;
    virtual Expression* multiply(Expression* a) = 0;
    virtual Expression* divide(Expression* a) = 0;
    

    string type;
    string exp;

};
#endif /* defined(__Calculator__Expression__) */

