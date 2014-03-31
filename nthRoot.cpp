//
//  nthRoot.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "nthRoot.h"

nthRoot::nthRoot(int root, int operand){
    this->type = "nthRoot";
    this->operand = operand;
    this->root = root;
    this->coefficient = 1;
}
nthRoot::~nthRoot(){
    
}
Expression nthRoot::simplify(){
    Expression* c = this;
    return *c;
}


Expression* nthRoot::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* nthRoot::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* nthRoot::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* nthRoot::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& nthRoot::print(std::ostream& output) const{
    output << this->coefficient  << "*" << this->root << "rt:" << this->operand;    //overlaod cout so that it makes sense
    return output;
}
