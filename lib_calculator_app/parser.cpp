#include "parser.h"
List<Lexem> Parser::parse(std::string expression) {

}
double Parser::getSin(double value) {
    return sin(value);
}
double Parser::getCos(double value) {
    return cos(value);
}
double Parser::getTg(double value) {
    return tan(value);
}
double Parser::getAbs(double value) {
    return fabs(value);
}
bool Parser::isOpenBracket(char c) {
    return c == '(' || c == '{' || c == '[';
}
bool Parser::isCloseBracket(char c) {
    return c == ')' || c == '}' || c == ']';
}
bool Parser::isDigit(char c) {
    return c >= '0' && c <= '9';
}
bool Parser::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool Parser::isVariableChar(char c) {
    return isDigit(c) || isLetter(c) || c == '_';
}
bool Parser::isValidVariableName(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    if (!isLetter(name[0]) && name[0] != '_') {
        return false;
    }
    for (char c : name) {
        if (!isVariableChar(c)) {
            return false;
        }
    }
    if (isFunction(name)) {
        return false;
    }
    return true;
}
bool Parser::isFunction(const std::string& name) {

}
bool Parser::isBinaryOperator(char c) {

}
bool Parser::isUnaryOperator(char c, const Lexem* prevLexem) {

}