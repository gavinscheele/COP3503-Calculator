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
    
    if (this->type == b->type) {
        if (this->type == "nthRoot") {
            if (this operand == b.getOperand() && this root == b.getRoot()) {
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }
    return false;
}
bool Expression::canSubtract(Expression* b){
    if (this->type == b->type) {
        if (this->type == "nthRoot") {
            if (this operand == b.getOperand() && this root == b.getRoot()) {
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }
    return false;
}
bool Expression::canMultiply(Expression* b){
    if (this->type == b->type) {
        if (this->type == "nthRoot") {
            if (this root == b.getRoot()) {
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }
    else if(this->type == "int" && b->type == "rational") return true;
    else if(this->type == "rational" && b->type == "int") return true;

    return false;

}
bool Expression::canDivide(Expression* b){
    if (this->type == b->type) {
        if (this->type == "nthRoot") {
            if (this root == b.getRoot() && ((this->operand / b.getOperand()) % 1) == 0 ) {
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }
    else if(this->type == "int"){
        if(b->type == "euler" || b->type == "pi" || b->type == "rational") return true;
    }
    else if(this->type == "rational" && b->type == "int") return true;
    
    return false;
}
ostream& operator<<(ostream &output, Expression &e){
    return e.print(output);
}
