//
//  Euler.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//
//

#include "Euler.h"

Euler::Euler(){
    this->type = "euler";
    this->coefficient = new Integer(1);
}
Euler::~Euler(){
    delete this;
}
Integer* Euler:: getCoefficient()
{
	return coefficient;
}
void Euler:: setCoefficient(Integer* x)
{
	this->coefficient = x;
}

Expression* Euler::add(Expression* a){
   Euler* c = this;

	if(a->type == "euler"){
        Euler *b = (Euler *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = (Integer *)thisCoef->add(aCoef);
		c->setCoefficient(sum);

	}
    return c;

}
Expression* Euler::subtract(Expression* a){

  Euler* c = this;

	if(a->type == "euler"){
        Euler *b = (Euler *)a;
		Integer* aCoef = b->getCoefficient();
		Integer* thisCoef = c->getCoefficient();
		Integer* sum = (Integer *)thisCoef->subtract(aCoef);
		c->setCoefficient(sum);
		Integer* zero = new Integer(0);
		if((c->coefficient->getValue()) == 0)
        {
            return zero;
        }
	}
    return c;


}
Expression* Euler::multiply(Expression* a){
    Euler* c = this;

	 if(a->type == "euler"){
        Euler *b = (Euler *)a;//Casts a

		Integer* aCoef = b->getCoefficient();//Gets coefficient of the thing that's being multiplied
		Integer* thisCoef = c->getCoefficient();//Gets coefficient of this
		Integer* product = (Integer *)thisCoef->multiply(aCoef);//Multiplies two coefficients together
		Euler* euler1 = new Euler();//creates new Euler
		euler1->setCoefficient(product);
		Rational* two = new Rational(2,1);
		Exponential* exponential = new Exponential((Expression*)euler1,two);//Creates new Exponential with base euler and exponent 2
		return exponential;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "euler"){ // Checks to see if the base is euler
            Rational* exponent = b->getExponent();//gets exponent of b
            Euler* euler2 = new Euler();//creates new Euler
            Rational* one = new Rational(1,1);
            Rational* exponSum =(Rational *)exponent->add(one);
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type euler
            euler2->setCoefficient(Coef);
            Exponential* product = new Exponential((Expression*)euler2,exponSum);
            return product;
            }
        }
        //need to return something if its not these two cases. Added return c.
        return c;
	}


Expression* Euler::divide(Expression* a){
	  Euler* c = this;

	 if(a->type == "euler"){//This doesn't work because of the integer divide method.
        Euler *b = (Euler *)a;//Casts a
		Integer* aCoef = b->getCoefficient();//Gets coefficient of the thing that's dividing (x/a)...a
		Integer* thisCoef = c->getCoefficient();//Gets coefficient of this(x/a)..x
		Expression* product = thisCoef->divide(aCoef);//Divides this by a
		return product;//e divided by e is 1, so we just return the product
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "euler"){ // Checks to see if the base is e
            Rational* exponent = b->getExponent();//gets exponent of b
            Euler* euler2 = new Euler();//creates new Euler
            Rational* one = new Rational(1,1);
            Rational* exponSum =(Rational*)one->subtract(exponent);
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type e
            euler2->setCoefficient(Coef);
            Exponential* product = new Exponential((Expression*)euler2,exponSum);// creates new Exponential with base e and exponent 1 - previous exponent
            return product;
            }
        }
    //need to return something if neither of these cases are met. added return c.
    return c;

	}


string Euler:: toString(){
    stringstream s;
	s<<this->coefficient<<"e";
	return s.str();
}

ostream& Euler::print(std::ostream& output) const{
    output << *coefficient << "e";
    return output;
}

