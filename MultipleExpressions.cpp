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
    size_t aSize = this->vectorExpressions.size();
    bool changed = false;
    Expression *result;
    
    if (a->type == "multiple") {
        MultipleExpressions *b = (MultipleExpressions *)a;
        if (b->vectorExpressions.size() == 3 && this->vectorExpressions.size() == 3
            && b->vectorExpressions.at(1) == "*" && this->vectorExpressions.at(1) == "*") {
            
            Expression *eB0 = s->bindToExpressionType(b->vectorExpressions.at(0));
            Expression *eThis0 = s->bindToExpressionType(this->vectorExpressions.at(0));
            Expression *eB1 = s->bindToExpressionType(b->vectorExpressions.at(2));
            Expression *eThis1 = s->bindToExpressionType(this->vectorExpressions.at(2));
            if (eB0->type == eThis0->type || eB0->canAdd(eThis0)) {
                if (eB0->toString() == eThis0->toString()) {
                    s = new Solver(eB0->toString() + " * " + eB1->add(eThis1)->toString());
                    result = s->bindToExpressionType(s->solve(false));
                    vectorExpressions = this->parseBySpaces(result->toString());
                    return this;
                }else{
                    s = new Solver(eB1->toString() + " * " + eB0->add(eThis0)->toString());
                    result = s->bindToExpressionType(s->solve(false));
                    vectorExpressions = this->parseBySpaces(result->toString());
                    return this;

                }
            }
        }
    }
    
    
    
    for (int i = 0; i < aSize; i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if ((i == aSize-1 && vectorExpressions.at(i-1) != "*" && vectorExpressions.at(i-1) != "/")) {
                changed = true;
                if (vectorExpressions.at(i-1) == "-") {
                    if (a->canSubtract(operand1)) {
                        result = a->subtract(operand1);
                        if (result->toString() == "0") {
                            vectorExpressions.erase(vectorExpressions.begin()+i-1,vectorExpressions.begin()+i+1);
                            break;
                        }
                        vectorExpressions.at(i-1) = "+";
                        vectorExpressions.at(i) = result->toString();
                        break;
                    }else{
                        if (a->toString() == "0") {
                            break;
                        }
                        vectorExpressions.push_back("+");
                        vectorExpressions.push_back(a->toString());
                        break;
                    }
                }else{
                    if (operand1->canAdd(a)) {
                        result = operand1->add(a);
                        if (result->toString() == "0") {
                            break;
                        }
                        vectorExpressions.at(i) = result->toString();
                        break;
                    }
                    else{
                        if (a->toString() == "0") {
                            break;
                        }
                        vectorExpressions.push_back("+");
                        vectorExpressions.push_back(a->toString());
                        break;
                    }
                }
            }
            else if (operand1->canAdd(a) && vectorExpressions.at(i) != "*" && vectorExpressions.at(i) != "/") {
                if (i > 1) {
                    if (vectorExpressions.at(i-1) != "*" && vectorExpressions.at(i-1) != "/") {
                        changed = true;
                        Expression *result;
                        if (vectorExpressions.at(i) == "-") {
                            result = a->subtract(operand1);
                        }else{
                            result = operand1->add(a);
                        }
                        vectorExpressions.at(i) = result->toString();
                        break;
                    }
                }else{
                changed = true;
                Expression *result;
                if (vectorExpressions.at(i) == "-") {
                    result = a->subtract(operand1);
                }else{
                    result = operand1->add(a);
                }
                vectorExpressions.at(i) = result->toString();
                break;
                }
            }
        }
    }
    if (!changed) {
        this->vectorExpressions.push_back("+");
        this->vectorExpressions.push_back(a->toString());
    }
    return this;
}

Expression* MultipleExpressions::subtract(Expression* a)
{
    Solver *s = new Solver();
    size_t aSize = this->vectorExpressions.size();
    bool changed = false;
    Expression *result;
    if (a->type == "multiple") {
        MultipleExpressions *b = (MultipleExpressions *)a;
        if (b->vectorExpressions.size() == 3 && this->vectorExpressions.size() == 3
            && b->vectorExpressions.at(1) == "*" && this->vectorExpressions.at(1) == "*") {
            
            Expression *eB0 = s->bindToExpressionType(b->vectorExpressions.at(0));
            Expression *eThis0 = s->bindToExpressionType(this->vectorExpressions.at(0));
            Expression *eB1 = s->bindToExpressionType(b->vectorExpressions.at(2));
            Expression *eThis1 = s->bindToExpressionType(this->vectorExpressions.at(2));
            if (eB0->type == eThis0->type || eB0->canAdd(eThis0)) {
                if (eB0->toString() == eThis0->toString()) {
                    s = new Solver(eB0->toString() + " * " + eThis1->subtract(eB1)->toString());
                    result = s->bindToExpressionType(s->solve(false));
                    vectorExpressions = this->parseBySpaces(result->toString());
                    return this;
                }else{
                    s = new Solver(eB1->toString() + " * " + eThis0->subtract(eB0)->toString());
                    result = s->bindToExpressionType(s->solve(false));
                    vectorExpressions = this->parseBySpaces(result->toString());
                    return this;
                    
                }
            }
        }
    }
    
    
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if ((i == aSize-1 && vectorExpressions.at(i-1) != "*" && vectorExpressions.at(i-1) != "/")) {
                changed = true;
                if(operand1->canSubtract(a)){
                    result = operand1->subtract(a);
                    vectorExpressions.at(i) = result->toString();
                    break;
                }else{
                    vectorExpressions.push_back("-");
                    vectorExpressions.push_back(a->toString());
                    break;
                }
            }
            else if (operand1->canSubtract(a) && vectorExpressions.at(i) != "*" && vectorExpressions.at(i) != "/") {
                if (i > 1) {
                    if (vectorExpressions.at(i-1) != "*" && vectorExpressions.at(i-1) != "/") {
                        changed = true;
                        if (operand1->canSubtract(a)) {
                            result = operand1->subtract(a);
                            vectorExpressions.at(i) = result->toString();
                            break;
                        }else{
                            vectorExpressions.push_back("-");
                            vectorExpressions.push_back(a->toString());
                            break;
                        }
                    }
                }else{
                    changed = true;
                    if (operand1->canSubtract(a)) {
                        result = operand1->subtract(a);
                        vectorExpressions.at(i) = result->toString();
                        break;
                    }else{
                        vectorExpressions.push_back("-");
                        vectorExpressions.push_back(a->toString());
                        break;
                    }
                }
            }
        }
    }
    if (!changed) {
        this->vectorExpressions.push_back("-");
        this->vectorExpressions.push_back(a->toString());
    }
    return this;
}

Expression* MultipleExpressions::multiply(Expression* a)
{
    Solver *s = new Solver();
    bool changed = false;
    
    if (a->type == "multiple") {
        MultipleExpressions *b = (MultipleExpressions *)a;
        if (b->meType == "as" && this->meType == "as") {
            Expression *first = s->bindToExpressionType(b->vectorExpressions.at(0));
            string op1 = b->vectorExpressions.at(1);
            Expression *second = s->bindToExpressionType(b->vectorExpressions.at(2));
            
            Expression *third = s->bindToExpressionType(this->vectorExpressions.at(0));
            string op2 = this->vectorExpressions.at(1);
            Expression *fourth = s->bindToExpressionType(this->vectorExpressions.at(2));
            
            this->vectorExpressions = foil(first, op1, second, third, op2, fourth)->vectorExpressions;
            return this;
        }
    }
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if (operand1->canMultiply(a)) {
                changed = true;
                Expression *result = operand1->multiply(a);
                if (result->type == "integer") {
                    Integer *t = (Integer *)result;
                    if (t->getValue() == 1) {
                        vectorExpressions.at(i) = result->toString();
                        vectorExpressions.erase(vectorExpressions.begin() + i-1,vectorExpressions.begin() + i+1);
                    }
                }else{
                    vectorExpressions.at(i) = result->toString();
                }
            }
        }
    }
    if (!changed) {
        this->vectorExpressions.push_back("*");
        this->vectorExpressions.push_back(a->toString());
    }
    return this;
}

Expression* MultipleExpressions::divide(Expression* a)
{
    Solver *s = new Solver();
    bool changed = false;
    for (int i = 0; i < this->vectorExpressions.size(); i++) {
        if ((i % 2 == 0  || i == 0 ) && i != 1) {   //odd numbers only
            Expression *operand1 = s->bindToExpressionType(this->vectorExpressions.at(i));
            if (operand1->canDivide(a)) {
                if (i >1 && vectorExpressions.at(i-1) == "/") {
                    Rational *t = new Rational(new Integer(1),a);
                    this->multiply(t);
                }
                changed = true;
                Expression *result = operand1->divide(a);
                if (result->type == "integer") {
                    Integer *t = (Integer *)result;
                    if (t->getValue() == 1) {
                        vectorExpressions.at(i) = result->toString();
                        vectorExpressions.erase(vectorExpressions.begin() + i-1,vectorExpressions.begin() + i+1);
                    }
                }else if(result->type == "rational"){
                    Rational *t = (Rational *)result;
                    vectorExpressions.at(i) = t->geteNumerator()->toString();
                    Expression *n;
                    size_t j = (size_t)i+2;
                    if(vectorExpressions.size() >= j){
                        s->bindToExpressionType(vectorExpressions.at(i+2));
                    }else{
                        s->bindToExpressionType(vectorExpressions.at(i-2));
                    }
                    if (t->geteDenominator()->canMultiply(n)) {
                        vectorExpressions.at(i+2) = t->geteDenominator()->multiply(n)->toString();
                    }else{
                        vectorExpressions.at(i) = result->toString();
                    }
                }else{
                    vectorExpressions.at(i) = result->toString();
                }
            }
        }
    }
    if (!changed) {
        this->vectorExpressions.push_back("/");
        this->vectorExpressions.push_back(a->toString());
    }
    return this;
}
vector<string> MultipleExpressions::parseBySpaces(string expression){
    int count = 0;
    string temp = "";
    vector<string> expressions = *new vector<string>();
    for(int i = 0; i < expression.size(); i ++){       //creates an array of expressions and operations
        if (expression.at(i) == 'l' && expression.at(i+1) == 'o' && expression.at(i+2) == 'g') {
            temp = "";
            for (int j = i; j < expression.size(); j++) {
                temp.push_back(expression.at(j));
                if (expression.at(j) == ')') {
                    i = j+1;
                    expressions.push_back(temp);
                    count = j + 2;
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
    }
    else if(this->type == "multiple" || b->type == "multiple") return true;
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
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}
bool MultipleExpressions::canMultiply(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer" && b->type == "rational") return true;
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((this->meType == "as" && m->meType == "as") || (this->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
    
}
bool MultipleExpressions::canDivide(Expression* b){
    if (this->type == b->type) {
        return true;
    }
    else if(this->type == "integer"){
        if( b->type == "rational") return true;
    }
    else if(this->type == "rational" && b->type == "integer") return true;
    else if(this->type == "multiple" && b->type == "multiple"){
        MultipleExpressions *m = (MultipleExpressions *)b;
        if ((this->meType == "as" && m->meType == "as") || (this->meType == "md" && m->meType == "md")) {
            return true;
        }
    }else if(this->type == "multiple" || b->type == "multiple") return true;
    return false;
}



MultipleExpressions* MultipleExpressions::foil(Expression *one, string operation1, Expression *two, Expression *three, string operation2, Expression *four){
    MultipleExpressions *result = new MultipleExpressions("");
    Solver *s = new Solver();
    Expression* o = s->bindToExpressionType(one->toString());
    Expression* t = s->bindToExpressionType(two->toString());
    Expression* tr = s->bindToExpressionType(three->toString());
    Expression* f = s->bindToExpressionType(four->toString());
    
    
    if (one->canMultiply(three)) {
        result->vectorExpressions.push_back(one->multiply(three)->toString());
    }else{
        result->vectorExpressions.push_back(one->toString());
        result->vectorExpressions.push_back("*");
        result->vectorExpressions.push_back(three->toString());
    }
    one = o;
    three = tr;
    if (two->canMultiply(three)) {
        if (operation1 == "-") {
            result->vectorExpressions.push_back(one->multiply(three)->multiply(new Integer(-1))->toString());
        }else
            result->vectorExpressions.push_back(one->multiply(three)->toString());
    }else{
        result->vectorExpressions.push_back(operation1);
        result->vectorExpressions.push_back(two->toString());
        result->vectorExpressions.push_back("*");
        result->vectorExpressions.push_back(three->toString());
    }
    two = t;
    three = tr;
    
    if (one->canMultiply(four)) {
        if (operation2 == "-") {
            result->vectorExpressions.push_back(one->multiply(four)->multiply(new Integer(-1))->toString());
        }else
            result->vectorExpressions.push_back(one->multiply(four)->toString());
    }else{
        result->vectorExpressions.push_back(operation2);
        result->vectorExpressions.push_back(one->toString());
        result->vectorExpressions.push_back("*");
        result->vectorExpressions.push_back(four->toString());
    }
    one = o;
    four = f;
    
    if (two->canMultiply(four)) {
        if (operation1 == "-" && operation2 == "-") {
            result->vectorExpressions.push_back("+");
        }else if(operation1 == "-" || operation2 == "-"){
            result->vectorExpressions.push_back("-");
        }else{
            result->vectorExpressions.push_back("+");
        }
        if (operation1 == "-" && operation2 == "-") {
            result->vectorExpressions.push_back(two->multiply(four)->toString());
        }
        else if (operation2 == "-") {
            result->vectorExpressions.push_back(two->multiply(four)->multiply(new Integer(-1))->toString());
        }else
            result->vectorExpressions.push_back(two->multiply(four)->toString());
    }else{
        if (operation1 == "-" && operation2 == "-") {
            result->vectorExpressions.push_back("+");
        }else if(operation1 == "-" || operation2 == "-"){
            result->vectorExpressions.push_back("-");
        }else{
            result->vectorExpressions.push_back("+");
        }
        result->vectorExpressions.push_back(two->toString());
        result->vectorExpressions.push_back("*");
        result->vectorExpressions.push_back(two->toString());
    }
    two = t;
    four = f;
    return result;
}

