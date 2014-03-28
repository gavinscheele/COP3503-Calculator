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
bool Expression::canAdd(Expression* b){     //use "this" as comparison. Solver will call someExpression.canAdd(&someOtherExpression)
    
    /*if(typeid(this) == typeid(b)){
        they are the same type
    }*/
    
    return false;
}
bool Expression::canSubtract(Expression* b){
    return false;

}
bool Expression::canMultiply(Expression* b){
    return false;

}
bool Expression::canDivide(Expression* b){
    return false;

}
