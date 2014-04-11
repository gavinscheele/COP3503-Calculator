//
// Logarithm.cpp
// Calculator
//
// Created by Gavin Scheele on 3/27/14.
// Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Logarithm.h"

Logarithm::Logarithm(int base, int operand){
    this->type = "logarithm";
    this->base = base;
    this->operand = operand;
}

Logarithm::Logarithm(int base, Expression* eOperand){
    this->type = "logarithm";
    this->base = base;
    this->eOperand = eOperand;
}

Logarithm::Logarithm(Expression* eBase, int operand){
    this->type = "logarithm";
    this->eBase = eBase;
    this->operand = operand;
}

Logarithm::Logarithm(Expression* eBase, Expression* eOperand){
    this->type = "logarithm";
    this->eBase = eBase;
    this->eOperand = eOperand;
}



Logarithm::~Logarithm(){
    delete this; 
}

Expression* Logarithm::simplify(){
    	if (base && operand) {
		if (base == operand){
			Expression* simplified = new Integer(1);
			return simplified; }
		else if(base == (1/operand){
			Expression* simplified = new Integer(-1);
			return simplified;}
}
		else{
			int primefactors[] = primeFactorization(x);
			int size;
			size = sizeof primefactors/sizeof (int);			
			for (i = 0; i <= size-1; i++) {
			Expression* seperatedlogs[i]= new Logarithm(base, primefactors[i]) ;
			if (seperatedlogs[i]->simplify()  != seperatedlogs[i]){
				Expression* simp = seperatedlogs[i]->simplify()
				seperatedlogs[i]= simp;
			}
			Expression* finalsimp;
			for (i = 0; i<= size-2; i++){
				finalsimp= seperatedlogs[i]->add(seperatedlogs[i+1]
			}	
			return finalsimp;

}
		
		 
			

		
	     
}

int[] Logarithm::primeFactorization(int n) {
    int k = 0; 
    while (n%2 == 0) {
        factors[k] = 2;
        k++;
        n = n/2;
    }
    for (i = 3; i <= sqrt(n); i = i + 2) {
        while (n%1 == 0) {
            factors[k] = 2;
            k++;
            n = n/i;
        }
    }
    if (n > 2) {
        factors[k] = n;
    }
    return factors;
}


Expression* Logarithm::add(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::subtract(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::multiply(Expression* a){
    Expression* c = this;
    return c;
}
Expression* Logarithm::divide(Expression* a){
    Expression* c = this;
    return c;
}
ostream& Logarithm::print(std::ostream& output) const{
    output << "Log" << this->base << "(" << this->operand << ")";
    return output;
}



// might need later had in simplify metthod not sure
/*int i = 1;
		int x = operand;
		int y = base;
	 	if(x % y == 0 &&) {
			while (x>y) {
				x /=y ;
				i++;}
			Expression* simplified = new Integer(i);
			return simplified; } 
*/
