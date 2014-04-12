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
		Euler * euler1 = new Euler();//creates new Euler
		Exponential* exponential = new Exponential((Expression *)euler1,(Rational *)2);//Creates new Exponential with base euler and exponent 2
		Expression* d = exponential->multiply(product);//multiplies the new e^2 by the multiplied product
		return d;
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "euler"){ // Checks to see if the base is e
            Rational* exponent = b->getExponent();//gets exponent of b
            Euler* euler2 = new Euler();//creates new Euler
            Rational* one = new Rational(1,1);
            Exponential* product = new Exponential((Expression*)euler2,(Rational *)(exponent->add(one)));
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type euler
            Expression* d = Coef->multiply(product);//multiplies the coefficient of e with the new Exponential type
            return d;
            }
        }
    
    return c;   //added this line to silence error of not returning anything

	}


Expression* Euler::divide(Expression* a){
	  Euler* c = this;

	 if(a->type == "euler"){
        Euler *b = (Euler *)a;//Casts a
		Integer* aCoef = b->getCoefficient();//Gets coefficient of the thing that's dividing (x/a)...a
		Integer* thisCoef = c->getCoefficient();//Gets coefficient of this(x/a)..x
		Integer* product = (Integer *)thisCoef->divide(aCoef);//Divides this by a
		return product;//e divided by e is 1, so we just return the product
		}
	else if(a->type == "exponential"){
        Exponential *b = (Exponential *)a;//Casts a
        if(b->getBase()->type == "euler"){ // Checks to see if the base is e
            Rational* exponent = b->getExponent();//gets exponent of b
            Euler* euler2 = new Euler();//creates new Euler
            Rational* one = new Rational(1,1);
            Exponential* product = new Exponential((Expression*)euler2,(Rational *)(one->subtract(exponent)));// creates new Exponential with base e and exponent 1 - previous exponent
            Integer* Coef = c->getCoefficient();//Gets the coefficient of the type euler
            Expression* d = Coef->multiply(product);//multiplies the coefficient of e with the new Exponential type
            return d;
            }
        }
    
    return c;   //added this line to silence error of not returning anything

	}


string Euler:: toString()
{
	stringstream s;
	s<<this->coefficient<<"e";
	return s.str();
}
ostream& Euler::print(std::ostream& output) const{
    output << this->coefficient << "e";  //overload cout of this class so that it makes sense
    return output;
}
