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
Expression::Expression(const Expression& other)
    : _expression(other._expression),
    _expression_id(other._expression_id),
    _variables_map(other._variables_map),
    _lexems(other._lexems),
    _polish_record(other._polish_record) {
}
bool Expression::isOperatorOrFunction(const Lexem& lexem) {
    return lexem.getType() == Operator || lexem.getType() == Function;
}
bool Expression::shouldPopFromStack(const Lexem& stackTop, const Lexem& current) {
    return stackTop.getType() != OpenBracket &&
        isOperatorOrFunction(stackTop) &&
        stackTop.getPriority() >= current.getPriority();
}
void Expression::build_polish_notation() {
    List<Lexem> output;
    Stack<Lexem> stack(_lexems.get_size());
    for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
        Lexem current = *it;
        switch (current.getType()) {
        case Constant:
        case Variable:
            output.push_back(current);
            break;
        case Function:
        case OpenBracket:
            stack.push(current);
            break;
        case Operator: {
            while (!stack.is_empty() && shouldPopFromStack(stack.top(), current)) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(current);
            break;
        }
        case CloseBracket: {
            while (!stack.is_empty() && stack.top().getType() != OpenBracket) {
                output.push_back(stack.top());
                stack.pop();
            }
            if (stack.is_empty()) {
                throw std::logic_error("Unmatched ')'");
            }
            stack.pop(); 
            if (!stack.is_empty() && stack.top().getType() == Function) {
                output.push_back(stack.top());
                stack.pop();
            }
            break;
        }
        default:
            throw std::logic_error("Unknown token type");
        }
    }
    while (!stack.is_empty()) {
        if (stack.top().getType() == OpenBracket) {
            throw std::logic_error("Unmatched '('");
        }
        output.push_back(stack.top());
        stack.pop();
    }
    _polish_record = output;
}
