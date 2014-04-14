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
<<<<<<< HEAD
#include "Exponential.h"
#include "Logarithm.h"
#include "Integer.h"
#include "Rational.h"
#include <sstream>
=======
#include "Solver.h"
>>>>>>> cc951f9e01e31295873b54a18d2f49cb5d178e68

#include <sstream>
class Integer;
class Pi : public Expression{
public:
    Pi();
    ~Pi();

    Expression* add(Expression* a);
    Expression* subtract(Expression* a);
    Expression* multiply(Expression* a);
    Expression* divide(Expression* a);
    string toString();
	Integer* getCoefficient();
	void setCoefficient(Integer* x);
    ostream& print(std::ostream& output) const;
private:
    Integer* coefficient;
};
#endif /* defined(__Calculator__Pi__) */
