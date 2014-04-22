//
//  Expression.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//
#include "Expression.h"

Expression::Expression(){
}
Expression::~Expression(){
    
}
ostream& operator<<(ostream &output, Expression &e){
    return e.print(output);
}
