//
//  Integer.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/28/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Integer.h"
Integer::Integer(int value){
    this->type = "integer";
    this->value = value;
}
Integer::~Integer(){
    
}
Expression* Integer::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Integer::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Integer::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Integer::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Integer::print(std::ostream& output) const{
    output << this->value;
    return output;
}
