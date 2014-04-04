//
//  Euler.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Euler.h"
Euler::Euler(){
    this->type = "euler";
    this->coefficient = 1;
}
Euler::~Euler(){
    
}
int Euler:: getCoefficient()
{
	return coefficient;
}
void Euler:: setCoefficient(int x)
{
	this->coefficient = x;
}
Expression* Euler::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Euler::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Euler::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Euler::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Euler::print(std::ostream& output) const{
    output << this->coefficient << "e";  //overload cout of this class so that it makes sense
    return output;
}
