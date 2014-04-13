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
			return simplified;
		}
		else if(base == (1/operand)){
			Expression* simplified = new Integer(-1);
			return simplified;}
        
		else{
			int x= operand;
			int *primefactors = primeFactorization(x);
			int size = 0;
			size = sizeof (primefactors)/sizeof (int);
			Expression* finalsimp = nullptr;
            
            vector<Logarithm *> seperatedLogs;

			for (int i = 0; i <= size-1; i++) {
			if (size ==1) {
                finalsimp = new Logarithm(base,operand);
            }
            seperatedLogs.push_back(new Logarithm(base, primefactors[i]));
            //Expression* seperatedlogs[size] = new Logarithm(base,primefactors[i]) ;
			if (seperatedLogs.at(size)->simplify()  != seperatedLogs.at(i)){
				Expression* simp = seperatedLogs.at(i)->simplify();
				seperatedLogs.at(i) = (Logarithm *)simp;
			}
            
			for (int i = 0; i<= size-2; i++){
				finalsimp= seperatedLogs.at(size)->add(seperatedLogs.at(i+1));
			}
			}
			return finalsimp;
            }
        }
    
	else if (base && eOperand) {
		// INSERT (call solver) here on eOperand 
		// create new array of eOperand simplified values
		// if array is of size 1, check if that value equals eOperand
		// if so return the original logarithm back b/c cannot be simplified
		// for all other scenarios, run simplify method again for each log in array
    }
	else if (eBase && operand) {
		// ISERT (call solver) here on eBase
		// For the most part will only be able to specifically deal with
		// eBase being Pi or e, but will still need to use solver first
		// in case there is an entry for eBase being something that can first be 
		// simplified. Using the simplified eBase, use conversion formula change of base
		// to set both values as log base (?? i think it should be 2, but not sure whats the
		// best way of determining that. Maybe it would be smart to set base equal to whatever the 		// original operand is in order to automatically change that value to 1.)
		// Implement change of base formula.
		// Call simplify on both the bottom and top logarithms.
		// Return the result of simplify. 
		
    }
	else if (eBase && eOperand){
		if (eBase == eOperand){
			Expression* simplified = new Integer(1);
			return simplified; }
		else if(eBase == (1/eOperand){
			Expression* simplified = new Integer(-1);
			return simplified;}
}	 
		// below, attempting to take nth root of eOperand in order to see if pi
		// is the nth root of this eOperand. If so, n will be returned.
		else if (eBase == pi && nrt(eOperand)== pi){
			// not sure how, but take nth root of eOperand and find its value.
			// use this value as n
			Expression* simplified = new Integer(n);
			return simplified; } 
		else if (eBase == euler && nrt(eOperand) == euler) {
			// again not sure exactly how, but take nth root of eOperand to see if
			// euler is the nth root of the eOperand. If so n will be returned. 
			Expression* simplified = new Integer(n);
			return simplified; }
		else{ 
		// INSERT (call solver) here on eOperand and eBase	
		// Call simplify method again on newly created logarithm after calling solver on the logarithm
		
}
                

int* Logarithm::primeFactorization(int n) {
    int k = 0; 
    while (n%2 == 0) {
        factors[k] = 2;
        k++;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
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
    output << "Log_" << this->base << ":" << this->operand;
    return output;
}
string Logarithm::toString(){
    stringstream ss;
    ss << "Log_" << this->base << "(" << this->operand;
};


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
