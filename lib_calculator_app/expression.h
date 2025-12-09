#pragma once
#include "../lib_list/List.h"
#include "lexem.h"
#include "parser.h"
#include <string>
#include <limits>
#include <map>
#include <cmath>
class Expression {
private:
    std::string _expression;
    size_t _expression_id;
    std::map<std::string, double> _variables_map; 
    List<Lexem> _lexems;
    List<Lexem> _polish_record;
    void build_polish_notation();
public:
    Expression(size_t id, std::string expression);
    Expression(size_t id, const List<Lexem>& list); 

    const std::string& get_expression() const { 
        return _expression; 
    }
    size_t get_id() const {
        return _expression_id;
    }
    const std::map<std::string, double>& get_variables() const {
        return _variables_map;
    }
    const List<Lexem>& get_lexems() const { 
        return _lexems; 
    }
    const List<Lexem>& get_polish_record() const { 
        return _polish_record; 
    }
    void set_variable(const std::string& name, double value);
    double get_variable(const std::string& name) const;
    bool has_variable(const std::string& name) const;
    void clear_variables() { 
        _variables_map.clear(); 
    }

    double calculate();
  
    void set_variables();
    void validate_variables() const;
    void print_variables() const;
    void extract_variables();
};
