#include "MultipleExpressions.h"

MultipleExpressions::MultipleExpressions(string s){
    this->type = "multiple";
    this->expressions = s;
    this->exp = s;
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
    return this;
}

Expression* MultipleExpressions::subtract(Expression* a)
{
    return this;
}

Expression* MultipleExpressions::multiply(Expression* a)
{
    return this;
}

Expression* MultipleExpressions::divide(Expression* a)
{
    return this;
}


string MultipleExpressions:: toString(){
    stringstream s;
	s<<this->expressions;
	return s.str();
}

ostream& MultipleExpressions::print(std::ostream& output) const{
    output << expressions;
    return output;
}

