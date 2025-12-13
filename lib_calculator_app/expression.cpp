#include "expression.h"
Expression::Expression(size_t id, std::string expression) :
    _expression_id(id), _expression(expression) {
    try {
        _lexems = Parser::parse(_expression);
        build_polish_notation();
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
    }
    catch (const std::exception& ex) {
        throw std::logic_error(
            "Expression ID: " + std::to_string(id) + ": " + ex.what()
        );
    }
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
double Expression::calculate() {


    // Алгоритм:
   // 1. Проверить, что все переменные заданы
   // 2. Пройти по _polish_record
   // 3. Использовать стек для вычислений
   // 4. Вернуть результат




}
void Expression::print_variables() const {
    std::vector<std::string> all_vars;
    for (const auto& lexem : _lexems) {
        if (lexem.type == TypeLexem::Variable) {
            if (std::find(all_vars.begin(), all_vars.end(), lexem.name) == all_vars.end()) {
                all_vars.push_back(lexem.name);
            }
        }
    }
    if (all_vars.empty()) {
        std::cout << "Нет переменных\n";
        return;
    }
    for (size_t i = 0; i < all_vars.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        if (has_variable(all_vars[i])) {
            std::cout << all_vars[i] << " = " << _variables_map.at(all_vars[i]);
        } else {
            std::cout << all_vars[i] << " = ?";
        }
    }
}
bool Expression::has_variable(const std::string& name) const {
    return _variables_map.find(name) != _variables_map.end();
}
void Expression::set_variable(const std::string& name, double value) {
        _variables_map[name] = value;
}
void Expression::set_variables() {
    std::string var_name;
    double value;
    // Показываем, какие переменные есть
    std::cout << "Доступные переменные: ";
    print_variables();
    std::cout << std::endl;
    std::cout << "Введите имя переменной (или 'stop' для выхода): ";
    std::cin >> var_name;
    while (var_name != "stop") {
        // Проверяем, есть ли такая переменная
        bool found = false;
        for (const auto& lexem : _lexems) {
            if (lexem.getType() == Variable && lexem.getName() == var_name) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Ошибка: переменная '" << var_name
                << "' не найдена в выражении\n";
        }
        else {
            std::cout << "Введите значение для " << var_name << ": ";
            std::cin >> value;
            set_variable(var_name, value);
        }
        std::cout << "Введите имя переменной (или 'stop' для выхода): ";
        std::cin >> var_name;
    }
}
