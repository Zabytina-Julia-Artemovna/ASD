#include "expression.h"
Expression::Expression(size_t id, std::string expression) :
    _expression_id(id), _expression(expression) {
    try {
        _lexems = Parser::parse(_expression);
        build_polish_notation();
        extract_variables();
    }
    catch (const std::exception& ex) {
        throw std::logic_error(
            "Expression ID: " + std::to_string(id) + ": " + ex.what()
        );
    }
}
Expression::Expression(size_t id, const List<Lexem>& list) :
    _expression_id(id), _lexems(list),
    _expression("Constructed by lexems") {
    try {
        build_polish_notation();
        extract_variables();
    }
    catch (const std::exception& ex) {
        throw std::logic_error(
            "Expression ID: " + std::to_string(id) + ": " + ex.what()
        );
    }
}
