#pragma once
#include "../lib_list/List.h"
#include "lexem.h"
#include <cmath>
#include <string>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <algorithm>
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
    bool isUnaryOperator(char c, bool lastWasOperatorOrBracket);
    int getOperatorPriority(char c);
    std::string formatError(const std::string& expression, size_t position, const std::string& message);
    double (*getFunctionByName(const std::string& name))(double);
    void Parser::handleAbsBracket(char c, List<Lexem>& lexems,
        bool& lastWasOperatorOrBracketOrFunction,
        bool& absOpened);
}
