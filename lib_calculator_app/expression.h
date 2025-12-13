#pragma once
#include "lexem.h"  
#include "../lib_list/List.h"
#include "../lib_stack/stack.h"
#include <string>
#include <map>
#include <cmath>
#include "parser.h"
#include <iostream>
class Expression {
private:
    std::string _expression;
    size_t _expression_id;
    std::map<std::string, double> _variables_map;
    List<Lexem> _lexems;
    List<Lexem> _polish_record;
    bool shouldPopFromStack(const Lexem& stackTop, const Lexem& current);
    bool isOperatorOrFunction(const Lexem& lexem);
    void build_polish_notation();

    bool has_variable(const std::string& name) const;
public:
    Expression(size_t id, std::string expression);
    Expression(size_t id, const List<Lexem>& list);
    const std::string& get_expression() const {
        return _expression;
    }
    size_t get_id() const {
        return _expression_id;
    }
    void clear_variables() {
        _variables_map.clear();
    }
    void set_variable(const std::string& name, double value);
    void set_variables();
    double calculate();
    void print_variables() const;
};
