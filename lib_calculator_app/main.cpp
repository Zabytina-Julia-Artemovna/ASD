//#include "expression.h"
//#include "functions.h"
//#include "lexem.h"
//#include "parser.h"
//#include "../lib_vector/vector.h"
//#include <iostream>
//// Â main.cpp
//void printExpressionsTable(const Tvector<Expression>& expressions) {
//    std::cout << "+-----+-----------------------------------------------+-----------------------------+" << std::endl;
//    std::cout << "| ID  | EXPRESSION                                   | VARIABLES VALUES            |" << std::endl;
//    std::cout << "+-----+-----------------------------------------------+-----------------------------+" << std::endl;
//
//    for (int i = 0; i < expressions.size(); ++i) {
//        if (expressions.exists(i)) {
//            const Expression& expr = expressions[i];
//            std::cout << "| " << std::setw(3) << expr.getId() << " | "
//                << std::setw(45) << std::left << expr.getOriginalExpression() << std::right << " | "
//                << std::setw(27) << formatVariables(expr) << " |" << std::endl;
//        }
//    }
//
//    std::cout << "+-----+-----------------------------------------------+-----------------------------+" << std::endl;
//}
//std::string formatVariables(const Expression& expr) {
//    auto vars = expr.getVariables();
//    std::string result;
//    for (const auto& [name, value] : vars) {
//        if (!result.empty()) result += ", ";
//        if (value == DBL_MAX) {
//            result += name + " = ?";
//        }
//        else {
//            result += name + " = " + std::to_string(value);
//        }
//    }
//    return result;
//}
