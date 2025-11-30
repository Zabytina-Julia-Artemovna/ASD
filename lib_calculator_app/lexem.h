#include "../lib_list/List.h"
enum TypeLexem { 
    Constant, 
    Variable, 
    OpenBrecket, 
    ClosedBrecket, 
    Function, 
    Operator, 
    UnOperator, 
    OpenedAbs, 
    ClosedAbs };
struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);
    Lexem(std::string _name, TypeLexem _type, double _value = DBL_MAX, int _priority = -1, double(*_function)(double) = nullptr);
    Lexem(const Lexem& other);

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
    
};
