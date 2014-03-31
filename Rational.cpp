//
//  Rational.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Rational.h"
Rational::Rational(int numerator, int denominator){
    this->type = "rational";
    this->numerator = numerator;
    this->denominator = denominator;
    simplify(numerator);
}
Rational::Rational(Expression* numerator, Expression* denominator){
    this->type = "rational";
    this->eNumerator = numerator;
    this->eDenominator = denominator;
    simplify(numerator);
}

Rational::~Rational(){
    
}
Expression Rational::simplify(int num){
    //if numerator and denominator are both type pi or type Euler, then simplify to one.
    Expression* c = this;
    
    if(this->numerator == 1){   //if the numerator is 1, it's already simplified
        return *c;
    }
    
    else if(this->numerator % this->denominator == 0){   //the numerator and denominator are evenly divisible
        this->numerator = this->numerator/this->denominator;
        this->denominator = 1;
    }
    
    else{
        int commonFactor = findCommonFactor(2);
        if(commonFactor == -1){
            return *c;
        }else{
            this->numerator = this->numerator/commonFactor;
            this->denominator = this->denominator/commonFactor;
            findCommonFactor(2);
        }
    }
    return *c;
}
Expression Rational::simplify(Expression* eNumerator){
    if(eNumerator->type == eDenominator->type){
        this->numerator = 1;
        this->denominator = 1;
    }

    return *this;
}
int Rational::findCommonFactor(int n){
    if(n > 9){
        return -1;
    }
    else if(this->numerator % n == 0 && this->denominator % n == 0){
        return n;
    }else{
        return findCommonFactor(n+1);
    }
}
Expression* Rational::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Rational::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Rational::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Rational::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Rational::print(std::ostream& output) const{
    if(this->numerator)
        output << this->numerator << "/" << this->denominator;
    else{
        cout << *eNumerator << "/" << *eDenominator;
    }
    return output;
}
