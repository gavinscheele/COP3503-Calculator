
//
//  Exponent.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Exponential.h"

Exponential::Exponential(Expression* base, Expression* exponent){
    this->type = "exponential";
    this->base = base;
    this->exponent = exponent;
}
Exponential::~Exponential(){
    
}
Expression Exponential::exponentiate(){
    Expression* c = this;
    return *c;
}



Expression* Exponential::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Exponential::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Exponential::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Exponential::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Exponential::print(std::ostream& output) const{
    output << this->base << this->exponent; //overload cout so that it makes sense
    return output;
}
