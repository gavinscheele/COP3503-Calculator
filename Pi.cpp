//
//  Pi.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Pi.h"
Pi::Pi(){
    this->type = "pi";
    this->coefficient = 1;
}
Pi::~Pi(){
    
}
Expression* Pi::add(Expression* b){
    Expression* c = this;
    return c;
}
Expression* Pi::subtract(Expression* b){
    Expression* c = this;
    return c;
}
Expression* Pi::multiply(Expression* b){
    Expression* c = this;
    return c;
}
Expression* Pi::divide(Expression* b){
    Expression* c = this;
    return c;
}
int Pi:: getCoefficient()
{
	return coefficient;
}
void Pi:: setCoefficient(int x)
{
	this->coefficient = x;
}
ostream& Pi::print(std::ostream& output) const{
    output << this->coefficient << "Pi";
    return output;
}
