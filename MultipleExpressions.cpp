#include "MultipleExpressions.h"

MultipleExpressions::MultipleExpressions(string s){
    this->type = "multiple";
    this->expressions = s;
    this->exp = s;
    this->vectorExpressions = this->parseBySpaces(s);
    if (this->vectorExpressions.size() > 1) {
        if (this->vectorExpressions.at(1) == "+" || this->vectorExpressions.at(1) == "-") {
            this->meType = "as";
        }else if(this->vectorExpressions.at(1) == "*" || this->vectorExpressions.at(1) == "/"){
            this->meType = "md";
        }else{
            throw runtime_error("Error: Multiple Expression does not have a type");
        }
    }
}
MultipleExpressions::~MultipleExpressions(){
    delete this;
}
string MultipleExpressions:: getExpressions()
{
	string s = this->toString();
	return s;
}
Expression* MultipleExpressions::add(Expression* a)
{
    Solver *s = new Solver();
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if (operand1->canAdd(a)) {
                Expression *result = operand1->add(a);
                vectorExpressions.at(i) = result->toString();
            }
        }
    }
    return this;
}

Expression* MultipleExpressions::subtract(Expression* a)
{
    Solver *s = new Solver();
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if (operand1->canSubtract(a)) {
                Expression *result = operand1->subtract(a);
                vectorExpressions.at(i) = result->toString();
            }
        }
    }
    return this;
}

Expression* MultipleExpressions::multiply(Expression* a)
{
    Solver *s = new Solver();
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if (operand1->canMultiply(a)) {
                Expression *result = operand1->multiply(a);
                vectorExpressions.at(i) = result->toString();
            }
        }
    }
    return this;
}

Expression* MultipleExpressions::divide(Expression* a)
{
    Solver *s = new Solver();
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if (operand1->canDivide(a)) {
                Expression *result = operand1->divide(a);
                vectorExpressions.at(i) = result->toString();
            }
        }
    }
    return this;
}
vector<string> MultipleExpressions::parseBySpaces(string expression){
    int count = 0;
    string temp = "";
    vector<string> expressions;
    for(int i = 0; i < expression.size(); i ++){       //creates an array of expressions and operations
        if (expression.at(i) == 'l' && expression.at(i+1) == 'o' && expression.at(i+2) == 'g') {
            for (int j = i; j < expression.size(); j++) {
                temp.push_back(expression.at(j));
                if (expression.at(j) == ')') {
                    i = j+1;
                    expressions.push_back(temp);
                    break;
                }
            }
        }
        else if(expression.at(i) == ' '){
            temp = "";
            for (int j = count; j < i; j++) {
                temp.push_back(expression.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
            
        }else if(i == expression.size()-1){
            temp = "";
            for (int j = count; j <= i; j++) {
                temp.push_back(expression.at(j));
            }
            expressions.push_back(temp);
            count = i+1;
        }
    }
    return expressions;
}
vector<string> MultipleExpressions::getVectorExpressions(){
    return this->vectorExpressions;
}

string MultipleExpressions:: toString(){
    this->expressions = "";
    for (int i = 0; i < vectorExpressions.size(); i++) {
        this->expressions += vectorExpressions.at(i);
        if (i != vectorExpressions.size()-1) {
            this->expressions += " ";
        }
    }
    stringstream s;
	s<<this->expressions;
	return s.str();
}

ostream& MultipleExpressions::print(std::ostream& output) const{
    MultipleExpressions *a = (MultipleExpressions *)this;
    output << a->toString();
    return output;
}

bool MultipleExpressions::canAdd(Expression* b){     //use "this" as comparison. Solver will call someExpression.canAdd(&someOtherExpression)
    
    if (this->type == b->type && this->type != "logarithm") {
        if (this->type == "nthRoot") {
        }
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((this->meType == "as" && m->meType == "as") || (this->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple") return true;
    return false;
}
bool MultipleExpressions::canSubtract(Expression* b){
    if (this->type == b->type) {
        return true;
    }else if((this->type == "integer" && b->type == "rational") || (this->type == "rational" && b->type == "integer")){
        return true;
    }else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((this->meType == "as" && m->meType == "as") || (this->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple") return true;
    return false;
}
bool MultipleExpressions::canMultiply(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if((this->type == "euler" && b->type == "integer") || (this->type == "integer" && b->type == "euler")) return true;
    else if(this->type == "integer" && b->type == "rational") return true;
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((this->meType == "as" && m->meType == "as") || (this->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple") return true;
    return false;
    
}
bool MultipleExpressions::canDivide(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer"){
        if(b->type == "euler" || b->type == "pi" || b->type == "rational") return true;
    }
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((this->meType == "as" && m->meType == "as") || (this->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple") return true;
    return false;
}

