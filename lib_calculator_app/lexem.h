#ifndef LEXEM_H     
#define LEXEM_H 
#include "../lib_list/List.h"
#include <string>
#include <cfloat>
enum TypeLexem { 
    Constant, 
    OpenBracket,
    CloseBracket,
    Variable,
    Function, 
    Operator, 
    OpenAbs, 
    CloseAbs };
struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);
    Lexem() : name(""), type(Constant), value(0.0),
        priority(-1), function(nullptr) {}
    Lexem(std::string _name, TypeLexem _type, double _value = DBL_MAX, 
        int _priority = -1, double(*_function)(double) = nullptr):
        name(_name), type(_type), value(_value), 
        priority(_priority), function(_function){};

    Lexem(const Lexem& other): name(other.name), type(other.type),
        value(other.value), priority(other.priority), 
        function(other.function){}

    Lexem(double _value): name(std::to_string(_value)), type(Constant), 
        value(_value), priority(-1), function(nullptr) {}

    std::string getName() const { 
        return name; 
    }
    TypeLexem getType() const { 
        return type; 
    }
    double getValue() const { 
        return value; 
    }
    int getPriority() const { 
        return priority; 
    }
    double (*getFunction() const)(double) {
        return function; 
    }
    char getOp() const {
        if (type != Operator) {
            throw std::logic_error("Лексема не является оператором");
        }
        if (name.empty()) {
            return '\0';
        }
        return name[0]; 
    }
};
#endif
