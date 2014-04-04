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
    if (this->exponent>0) {
        return exponentiate(this->base, this->exponent);
    }
    if (this->exponent==0) {
        return 1;
    }
    if (this->exponent<0) {
        return (1/exponentiate(this->base, this->exponent));
    }
}

Expression Exponential:exponentiate(Expression expression, int exponent) {
    if (n>1) {
    return exponentiate(this*expression, n-1);
    }
    return expression;
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
    if (*a == *c) //might require overriding
    {
        exponent += a->getExponent;
    }
    return c;
}
Expression* Exponential::divide(Expression* a){
    Expression* c = this;
    if (*a == *c) //might require overriding
    {
        c->getExponent -= a->getExponent;
    }
    return c;
}

*Expression Exponential::getExponent() {
    return exponent;
}

*Expression Exponential::getBase() {
    return base;
}

void Exponential::setExponent(*Expression e) {
    exponent = e;
}

void Exponential::setBase(*Expression e) {
    base = e;
}


ostream& Exponential::print(std::ostream& output) const{
    output << this->base << this->exponent; //overload cout so that it makes sense
    return output;
}