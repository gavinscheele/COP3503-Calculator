//
//  Solver.h
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#ifndef __Calculator__Solver__
#define __Calculator__Solver__

#include <iostream>
#include "Expression.h"
#include "Exponential.h"
#include "Logarithm.h"
#include "Pi.h"
#include "Euler.h"
#include "nthRoot.h"
#include "Rational.h"
class Solver{
public:
    Solver(std::string a);
    ~Solver();
    std::string solve();
private:
    std::string localExpression;
};
#endif /* defined(__Calculator__Solver__) */
