
//
//  Rational.cpp
//  Calculator
//
//  Created by Gavin Scheele on 3/27/14.
//  Copyright (c) 2014 Gavin Scheele. All rights reserved.
//

#include "Rational.h"
Rational::Rational(int numerator, int denominator){     //constructor for rational with two integers
    if (denominator == 0) {
        throw runtime_error("Cannot Divide By Zero");
    }
    this->type = "rational";
    this->numerator = numerator;
    this->denominator = denominator;
    if (numerator < 0 && denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
    this->eNumerator = new Integer(numerator);
    this->eDenominator = new Integer(denominator);
    simplify(numerator);

}
Rational::Rational(Expression* numerator, Expression* denominator){     //constructor for rational that has more complicated numerator and/or denominator
    
    if (denominator->type == "integer") {
        Integer *a = (Integer *)denominator;
        if(a->getValue() == 0){
            throw runtime_error("Cannot Divide By Zero");
        }
    }
    
    this->type = "rational";
    if (numerator->type == denominator->type && numerator->type != "integer") {
        this->eNumerator = new Integer(1);
        this->eDenominator = new Integer(1);
    }else{
        this->eNumerator = numerator;
        this->eDenominator = denominator;
        simplify(numerator);
    }
    if (this->eNumerator->type == "integer" && this->eDenominator->type == "integer") {
        Integer *num = (Integer *)eNumerator;
        Integer *den = (Integer *)eDenominator;
        if (num->getValue() < 0 && den->getValue() < 0) {
            num->setValue(num->getValue() * -1);
            den->setValue(den->getValue() * -1);
        }
    }
}

Rational::~Rational(){
    delete this->eNumerator;
    delete this->eDenominator;
    
}
Expression* Rational::geteDenominator(){
    return this->eDenominator;
}
void Rational::setDenominator(Expression* denominator){
    this->eDenominator = denominator;
    syncIntToExp();
}

Expression* Rational::geteNumerator(){
    return this->eNumerator;
}
void Rational::setNumerator(Expression* numerator){
    this->eNumerator = numerator;
    syncIntToExp();
}
int Rational::getNumerator(){
    return this->numerator;
}
int Rational::getDenominator(){
    return this->denominator;
}
bool Rational::hasIntegerOperands(){
    if(this->eNumerator->type == "integer"){
        return true;
    }else return false;
}






Expression* Rational::simplify(int num){
    //if numerator and denominator are both type pi or type Euler, then simplify to one.
    
    if(this->numerator == 1 || this->numerator == -1){   //if the numerator is 1, it's already simplified
        return this;
    }
    
    else if(this->numerator % this->denominator == 0 ){   //the numerator and denominator are evenly divisible
        this->numerator = this->numerator/this->denominator;
        this->denominator = 1;
        syncExpToInt();
    }
    else if(this->denominator % this->numerator == 0){
        if(this->numerator < 0){
            this->denominator = this->denominator/(-this->numerator);
            syncExpToInt();
        }else{
            this->denominator = this->denominator/this->numerator;
            syncExpToInt();
        }
        if(this->numerator < 0){
            this->numerator = -1;
            syncExpToInt();
        }
        else{
            this->numerator = 1;
            syncExpToInt();
        }

    }
    
    else{
        int commonFactor = findCommonFactor(2);
        while (commonFactor != -1) {
            this->numerator = this->numerator/commonFactor;
            this->denominator = this->denominator/commonFactor;
            syncExpToInt();
            commonFactor = findCommonFactor(2);
        }
    }
    if(denominator < 0 && numerator > 0){
        denominator *= -1;
        numerator *= -1;
        syncExpToInt();
    }
    return this;
}
Expression* Rational::simplify(Expression* eNumerator){
    if(this->eNumerator->type == this->eDenominator->type){
        if(this->eNumerator->type == "integer"){
            syncIntToExp();
            this->simplify(1);
            syncExpToInt();
        }
        else if(this->eNumerator->type == "euler"){
            Euler *num = (Euler *)eNumerator;
            Euler *den = (Euler *)eDenominator;
            eNumerator = num->getCoefficient();
            eDenominator = den->getCoefficient();
            simplify(1);
        }else if(this->eNumerator->type == "pi"){
            Pi *num = (Pi *)eNumerator;
            Pi *den = (Pi *)eDenominator;
            eNumerator = num->getCoefficient();
            eDenominator = den->getCoefficient();
            simplify(1);
        }else if(this->eNumerator->type == "nthRoot"){
            nthRoot *num = (nthRoot *)eNumerator;
            nthRoot *den = (nthRoot *)eDenominator;
            numerator = num->getCoefficient();
            denominator = den->getCoefficient();
            simplify(1);
        }
        syncIntToExp();
    }
    return this;
}
Rational* Rational::findCommonDenominator(Rational* a){

    if(a->hasIntegerOperands()){
        int aNum = a->getNumerator();
        int aDen = a->getDenominator();
        aNum *= this->denominator;
        this->numerator *= aDen;
        aDen *= this->denominator;
        this->denominator *= a->getDenominator();
        syncExpToInt();

        a->setNumerator(new Integer(aNum));
        a->setDenominator(new Integer(aDen));
        
        a->syncIntToExp();
    }
    return a;
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
    if(a->type == "integer"){
        
        Integer *b = (Integer *)a;
        if(this->numerator || this->numerator == 0){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            this->add(c);
        }
        
    }else if(a->type == "rational"){

        Rational *b =  (Rational *)a;                                    //cast expression as Rational type
        Rational *commonD = this->findCommonDenominator(b);             //Find a common denominator between "this" and the passed expression. Save that to commonD
        
        if(commonD->hasIntegerOperands()){                              //If it has integer operands
            Integer *in = (Integer *)commonD->eNumerator;               //Make an Integer type for the numerator of the first rational
            Integer *in2 = (Integer *)eNumerator;                       //Make an Integer type for this numerator
            
            this->eNumerator = new Integer(in->getValue() + in2->getValue());     //Set the value of the numerator to the addition of the two numerators. We can do this because
                                                                        //They already share a common denominator
            Integer *num1 = (Integer *)eNumerator;                      //update the value of numerator to match eNumerator
            this->numerator = num1->getValue();
            
            Integer *den1 = (Integer *)eDenominator;                    //update the value of denominator to match eDenominator
            this->denominator = den1->getValue();
            
            this->simplify(1);                                          //call the simplify method for integer only rationals
            
            Integer *num = new Integer(this->numerator);                //update the value of eNumerator to match numerator
            Integer *den = new Integer(this->denominator);              //update the value of eDenominator to match denominator
            if((num->getValue() < 0) && (den->getValue() < 0)){
                Integer *g = new Integer(-1);
                eNumerator->multiply(g);
                
                eDenominator->multiply(g);

            }else{
                eNumerator = num;
                eDenominator = den;
            }
        }else{
            cout << "non integer rational operands not yet implemented. Returning first argument" << endl;
        }
        
        
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Rational::subtract(Expression* a){
    if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->numerator || this->numerator == 0){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            this->subtract(c);
        }
    }else if(a->type == "rational"){
        Rational *b = (Rational *)a;                                    //cast expression as Rational type
        Rational *commonD = (Rational *)this->findCommonDenominator(b); //Find a common denominator between "this" and the passed expression. Save that to commonD
        
        if(commonD->hasIntegerOperands()){                              //If it has integer operands
            Integer *in2 = (Integer *)commonD->eNumerator;               //Make an Integer type for the numerator of the first rational
            Integer *in = (Integer *)eNumerator;                       //Make an Integer type for this numerator
            
           this->eNumerator = new Integer(in->getValue() - in2->getValue());     //Set the value of the numerator to the addition of the two numerators. We can do this because

            //They already share a common denominator
            Integer *num1 = (Integer *)eNumerator;                      //update the value of numerator to match eNumerator
            this->numerator = num1->getValue();
            
            Integer *den1 = (Integer *)eDenominator;                    //update the value of denominator to match eDenominator
            this->denominator = den1->getValue();
            
            this->simplify(1);                                          //call the simplify method for integer only rationals
            
            Integer *num = new Integer(this->numerator);                //update the value of eNumerator to match numerator
            Integer *den = new Integer(this->denominator);              //update the value of eDenominator to match denominator
            if((num->getValue() < 0) && (den->getValue() < 0)){
                Integer *g = new Integer(-1);
                eNumerator->multiply(g);
                
                eDenominator->multiply(g);

            }else{
                eNumerator = num;
                eDenominator = den;
            }
        }else{
            cout << "non integer rational operands not yet implemented. Returning first argument" << endl;
        }
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Rational::multiply(Expression* a){
    if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->numerator || this->numerator == 0){
            Rational *c = new Rational(b->getValue() * denominator, denominator);
            c->syncIntToExp();
            Rational *z = (Rational *)this->multiply(c);
            this->numerator = z->getNumerator();
            this->denominator = z->getDenominator();
            this->eDenominator = z->geteDenominator();
            this->eNumerator = z->geteNumerator();
        }
    }else if(a->type == "rational"){
        Rational *b = (Rational *)a;                                    //cast expression as Rational type
        b->eNumerator->multiply(this->eNumerator);
        b->eDenominator->multiply(this->eDenominator);
        Integer *num = (Integer *)b->eNumerator;
        b->numerator = num->getValue();
        Integer *den = (Integer *)b->eDenominator;
        b->denominator = den->getValue();
        b->simplify(1);
        return b;
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Rational::divide(Expression* a){
    if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->numerator || this->numerator == 0){
            Rational *c = new Rational(numerator ,b->getValue() * denominator);
            return c;
        }
    }else if(a->type == "rational"){
        Rational *b = (Rational *)a;                                    //cast expression as Rational type
        Expression *den1 = b->eNumerator;
        b->eNumerator = b->eDenominator;
        b->eDenominator = den1;
        b->syncIntToExp();
        
        b->eNumerator->multiply(this->eNumerator);
        b->eDenominator->multiply(this->eDenominator);
        Integer *num = (Integer *)b->eNumerator;
        b->numerator = num->getValue();
        Integer *den = (Integer *)b->eDenominator;
        b->denominator = den->getValue();
        b->simplify(1);
        return b;
    }
    else{
        cout << "type not recognized" << endl;
    }
    this->simplify(1);
    return this;
}
void Rational::syncExpToInt(){
    Expression *a = new Integer(this->numerator);
    Expression *b = new Integer(this->denominator);
    this->eNumerator = a;
    this->eDenominator = b;
}
void Rational::syncIntToExp(){
    Integer *a = (Integer *)eNumerator;
    this->numerator = a->getValue();
    
    Integer *b = (Integer *)eDenominator;
    this->denominator = b->getValue();
}
ostream& Rational::print(std::ostream& output) const{
    Rational *a = (Rational *)this;
    output << a->toString();
    return output;
}
string Rational::toString(){
    stringstream s;
    if (dynamic_cast<Integer *>(eDenominator) != 0) {
        Integer *den = (Integer *)eDenominator;
        if (den->getValue() == 1) {
            s << *eNumerator;
        }else{
            s << *eNumerator << " / " << *eDenominator;
        }
    }else{
        s << *eNumerator << " / " << *eDenominator;
    }
    return s.str();
}





bool Rational::canAdd(Expression* b){     //use "this" as comparison. Solver will call someExpression.canAdd(&someOtherExpression)
    
    if (this->type == b->type && this->type != "logarithm") {
        if (this->type == "nthRoot") {
        }
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool Rational::canSubtract(Expression* b){
    if (this->type == b->type) {
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool Rational::canMultiply(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer" && b->type == "rational") return true;
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
    
}
bool Rational::canDivide(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer"){
        if( b->type == "rational") return true;
    }
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *t = (MultipleExpressions *)this;
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((t->meType == "as" && m->meType == "as") || (t->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
