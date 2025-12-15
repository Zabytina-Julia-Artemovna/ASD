#include "parser.h"
void Parser::handleAbsBracket(char c, List<Lexem>& lexems,
    bool& lastWasOperatorOrBracketOrFunction,
    bool& absOpened) {
   if (!absOpened) {
        // Opened - abs(
        lexems.push_back(Lexem("abs", TypeLexem::Function, DBL_MAX, 4,
            getFunctionByName("abs")));
        lexems.push_back(Lexem("(", TypeLexem::OpenBracket));
        absOpened = true;
        lastWasOperatorOrBracketOrFunction = true;
    }
    else {
        // closed - )
        lexems.push_back(Lexem(")", TypeLexem::CloseBracket));
        absOpened = false;
        lastWasOperatorOrBracketOrFunction = false;
    }
}
List<Lexem> Parser::parse(std::string expression) {
    if (expression.empty()) {
        throw std::logic_error("Expression is empty");
    }
    List<Lexem> lexems;
    bool lastWasOperatorOrBracketOrFunction = true;
    bool absOpened = false;
    size_t i = 0;
    while (i < expression.length()) {
        char c = expression[i];
        if (c == ' ') {
            i++;
            continue;
        }
        if (isDigit(c)) {
            std::string number = "";
            number += c;
            i++;
            while (i < expression.length() &&
                (isDigit(expression[i]) || expression[i] == '.')) {
                number += expression[i];
                i++;
            }
            try {
                double constant = std::stod(number);
                Lexem lexem(constant);
                lexems.push_back(lexem);
                lastWasOperatorOrBracketOrFunction = false;
            }
            catch (std::exception& ex) {
                size_t errorPos = i - number.length();
                std::string errorMsg = formatError(expression, errorPos,
                    "Invalid number format: '" + number + "'");
                throw std::logic_error(errorMsg);
            }
           
        } else if (isOpenBracket(c)) {
            Lexem lexem(std::string(1, c), TypeLexem::OpenBracket);
            lexems.push_back(lexem);
            lastWasOperatorOrBracketOrFunction = true;
            i++;
        } else if (isCloseBracket(c)) {
            Lexem lexem(std::string(1, c), TypeLexem::CloseBracket);
            lexems.push_back(lexem);
            lastWasOperatorOrBracketOrFunction = false;
            i++;
        } else if (isBinaryOperator(c)) {
            bool isUnary = isUnaryOperator(c, lastWasOperatorOrBracketOrFunction);
            if (isUnary && c != '+') {
                Lexem lexem1(0.0);
                Lexem lexem2("-", TypeLexem::Operator, DBL_MAX, 1);
                lexems.push_back(lexem1);
                lexems.push_back(lexem2);
                lastWasOperatorOrBracketOrFunction = true;
            } else {
                int priority = getOperatorPriority(c);
                Lexem lexem(std::string(1, c), TypeLexem::Operator, DBL_MAX, priority);
                lexems.push_back(lexem);
                lastWasOperatorOrBracketOrFunction = true;
            }
            i++;
        } else if (isLetter(c) || c == '_') { //function/variable
            std::string word = "";
            word += c;
            i++;
            while (i < expression.length() && isVariableChar(expression[i]))  {
                word += expression[i]; //sin
                i++;
            } if (isFunction(word)) {
                if ( i >= expression.length() ||!isOpenBracket(expression[i])){
                    size_t errorPos = i - word.length();
                    std::string errorMsg = formatError(expression, errorPos,
                        "Invalid variable/function format: '" + word + "'");
                    throw std::logic_error(errorMsg);
                }
                double (*funcPtr)(double) = getFunctionByName(word);
                if (funcPtr == nullptr) {
                    size_t errorPos = i - word.length();
                    std::string errorMsg = formatError(expression, errorPos,
                        "Invalid variable/function format: '" + word + "'");
                    throw std::logic_error(errorMsg);
                }
                Lexem lexem(word, TypeLexem::Function, DBL_MAX, 4, funcPtr);
                lexems.push_back(lexem);
                lastWasOperatorOrBracketOrFunction = true;
                
            } else if (isValidVariableName(word)) {
                Lexem lexem(word, TypeLexem::Variable);
                lexems.push_back(lexem);
                lastWasOperatorOrBracketOrFunction = false;
            } else {
                size_t errorPos = i - word.length();
                std::string errorMsg = formatError(expression, errorPos,
                    "Invalid variable/function format: '" + word + "'");
                throw std::logic_error(errorMsg);
            }
        }
        else if (c == '|') {
            handleAbsBracket(c, lexems, lastWasOperatorOrBracketOrFunction, absOpened);
            i++;
        }
        else {
            size_t errorPos = i;
            std::string errorMsg = formatError(expression, errorPos,
                "Unknown character: '" + std::string(1, c) + "'");
            throw std::logic_error(errorMsg);
        }
    } // cycle while i < expr. lenght
    if (lastWasOperatorOrBracketOrFunction && !(lexems.get_size() == 0) ) {
        size_t errorPos = expression.length() - 1;
        std::string errorMsg = formatError(expression, errorPos,
            "Expression cannot end with operator or function");
        throw std::logic_error(errorMsg);
    }
    return lexems;
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
    const std::string functions[] = {
        "sin", "cos", "tg", "abs"  
    };
    for (const auto& function : functions) {
        if (name == function) {
            return true;
        }
    }
    return false;
}
bool Parser::isBinaryOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
bool Parser::isUnaryOperator(char c, bool lastWasOperatorOrBracket) {
    if (c != '-') {
        return false;
    }
    return lastWasOperatorOrBracket;
}
int Parser::getOperatorPriority(char c) {
    switch (c) {
    case '^':
        return 3;
        break;
    case '*': case '/':
        return 2;
        break;
    case '+': case '-':
        return 1;
        break;
    default:
        return 0;
    }
}
std::string Parser::formatError(const std::string& expression,
    size_t position,
    const std::string& message) {
    std::stringstream ss;
    ss << "\nВыражение: " << expression << "\n";
    ss << "Позиция " << position + 1 << ": ";
    for (size_t i = 0; i < position && i < expression.length(); i++) {
        if (expression[i] == '\t') {
            ss << "\t";
        }
        else {
            ss << " ";
        }
    }
    ss << "^\n";
    ss << "Ошибка: " << message;
    return ss.str();
}
double (*Parser::getFunctionByName(const std::string& name))(double) {
    if (name == "sin") {
        return Parser::getSin;
    }
    if (name == "cos") {
        return Parser::getCos;
    }
    if (name == "tg") {
        return Parser::getTg;
    }
    if (name == "abs") {
        return Parser::getAbs;
    }
    return nullptr;
}
