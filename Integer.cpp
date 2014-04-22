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
int Integer::getValue() {
    return value;
}
void Integer::setValue(int n) {
    value = n;
}
Expression* Integer::add(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value+=b->getValue();

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        b->setNumerator(b->geteNumerator()->add(this->multiply(b->geteDenominator())));
        //multiplies Integer by the denominator of the Rational to give it a common denominator then performs addition
        return b;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Integer::subtract(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value-=b->getValue();

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
       // b->setNumerator(b->geteNumerator()->subtract(this->multiply(b->geteDenominator())));
        b->setNumerator(this->multiply(b->geteDenominator())->subtract(b->geteNumerator()));
        //multiplies Integer by the denominator of the Rational to give it a common denominator then performs subtraction
        return b;
        //this = b;

    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Integer::multiply(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        this->value*=b->getValue();

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        Integer *i = new Integer(b->getNumerator()*this->getValue());
        b->setNumerator(i);
        //multiplies the Integer with the numerator of the Rational
        return b;
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
Expression* Integer::divide(Expression* a){
    if(a->type == "euler"){

    }else if(a->type == "exponential"){

    }else if(a->type == "integer"){
        Integer *b = (Integer *)a;
        if(this->value % b->getValue() == 0){
            this->value/=b->getValue();
        }else{
            Rational *c = new Rational(this->value,b->getValue());
            return c;
        }

    }else if(a->type == "logarithm"){

    }else if(a->type == "nthRoot"){

    }else if(a->type == "pi"){

    }else if(a->type == "rational"){
        Rational *b = (Rational *) a;
        Expression * c = b->geteNumerator();
        b->setNumerator(b->geteDenominator()->multiply(this));
        b->setDenominator(c);
        //multiplies the Integer with the denominator of the Rational
        return b;
    }else{
        cout << "type not recognized" << endl;
    }
    return this;
}
ostream& Integer::print(std::ostream& output) const{
    output << this->value;
    return output;
}

string Integer::toString() {
    stringstream ss;
    ss << value;
    return ss.str();
}



bool Integer::canAdd(Expression* b){     //use "this" as comparison. Solver will call someExpression.canAdd(&someOtherExpression)
    
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
    }else if(this->type == "multiple") return true;
    return false;
}
bool Integer::canSubtract(Expression* b){
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
    }else if(this->type == "multiple") return true;
    return false;
}
bool Integer::canMultiply(Expression* b){
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
    }else if(this->type == "multiple") return true;
    return false;
    
}
bool Integer::canDivide(Expression* b){
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
    }else if(this->type == "multiple") return true;
    return false;
}
