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
Expression* Euler:: getCoefficient()
{
	return coefficient;
}
void Euler:: setCoefficient(Expression* x)
{
	this->coefficient = x;
}
Expression* Euler::add(Expression* a){
   Expression* c = this;
    
	if(a->type == "euler"){
		Rational* aCoef = a->getCoefficient();
		Rational* thisCoef = c->getCoefficient();
		Rational* sum = thisCoef->add(aCoef);
		c->setCoefficient(sum);
		return c;	
	}

}
Expression* Euler::subtract(Expression* a){

  Expression* c = this;
   
	if(a->type == "euler"){
		Rational* aCoef = a->getCoefficient();
		Rational* thisCoef = c->getCoefficient();
		Rational* sum = thisCoef->subtract(aCoef);
		c->setCoefficient(sum);
		return c;	
	}

}
Expression* Euler::multiply(Expression* a){
    Expression* c = this;
	 if(a->type == "integer"){
		Rational* a1 = new Rational(a->getValue(),1);
		Rational* thisCoef = c->getCoefficient();
		Rational* product = thisCoef->multiply(a1);
		c->setCoefficient(product);
		return c;	
	}
	 if(a->type == "euler"){
		Rational* aCoef = a->getCoefficient();
		Rational* thisCoef = c->getCoefficient();
		Rational* product = thisCoef->multiply(aCoef);
		Exponential* e = new (e,2)
		Exponential* e = e->multiply(product)
		return e;	
	}
	
	if(a->type == "rational"){
		Rational* thisCoef = c->getCoefficient();
		Rational* product = thisCoef->multiply(a1);
		c->setCoefficient(product);
		return c;	
	} 
	
	
	
}
Expression* Euler::divide(Expression* a){
    Expression* c = this;

	 if(a->type == "integer"){
		Rational* a1 = new Rational(a->getValue(),1);
		Rational* thisCoef = c->getCoefficient();
		Rational* product = thisCoef->divide(a1);
		c->setCoefficient(product);
		return c;	
	}
	 if(a->type == "euler"){
		Rational* aCoef = a->getCoefficient();
		Rational* thisCoef = c->getCoefficient();
		Rational* product = thisCoef->divide(aCoef);
		Exponential* e = new (e,2)
		Exponential* e = e->multiply(product)
		return e;	
	}
	
	if(a->type == "rational"){
		Rational* thisCoef = c->getCoefficient();
		Rational* product = thisCoef->divide(a);
		c->setCoefficient(product);
		return c;	
	} 
	
   
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
