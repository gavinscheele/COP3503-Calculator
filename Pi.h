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
public:
    Pi();
    ~Pi();
    
    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
	int getCoefficient();
	void setCoefficient(int x);
    ostream& print(std::ostream& output) const;
private:
    int coefficient;
};
#endif /* defined(__Calculator__Pi__) */
