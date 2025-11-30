#pragma once
#include "../lib_list/List.h"
#include "lexem.h"
namespace Parser { 
    List<Lexem> parse(std::string expression);
    double getSin(double value);
    double getCos(double value);
    double getTg(double value);
    double getAbs(double value);
    bool isOpenBracket(char c);
    bool isCloseBracket(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    bool isVariableChar(char c);
    bool isValidVariableName(const std::string& name);
    bool isFunction(const std::string& name);
    bool isBinaryOperator(char c);
    bool isUnaryOperator(char c, const Lexem* prevLexem);
}
