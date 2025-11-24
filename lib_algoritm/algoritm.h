#pragma once
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/List.h"
#include "../lib_dsu/dsu.h"
#include <random>
#include <utility> 
#include <stdexcept>
#include <string>
#include <cctype>
#include <unordered_set>
template <class T>
std::pair<size_t, size_t> find_min_neighbor_coords(const Matrix<T>& matrix, size_t x, size_t y) {
    T min_val = matrix[x][y];
    size_t min_x = x;
    size_t min_y = y;
    if (x > 0 && matrix[x - 1][y] < min_val) {
        min_val = matrix[x - 1][y];
        min_x = x - 1;
        min_y = y;
    }
    if (x < matrix.getM() - 1 && matrix[x + 1][y] < min_val) {
        min_val = matrix[x + 1][y];
        min_x = x + 1;
        min_y = y;
    }
    if (y > 0 && matrix[x][y - 1] < min_val) {
        min_val = matrix[x][y - 1];
        min_x = x;
        min_y = y - 1;
    }
    if (y < matrix.getN() - 1 && matrix[x][y + 1] < min_val) {
        min_val = matrix[x][y + 1];
        min_x = x;
        min_y = y + 1;
    }
    return { min_x, min_y };
}
size_t getRandomIndex(size_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, max - 1);
    return dist(gen);
}
template <class T>
T find_local_minimum(const Matrix<T>& matrix) {
    size_t x = getRandomIndex(matrix.getM());
    size_t y = getRandomIndex(matrix.getN());

    while (true) {
        std::pair<size_t, size_t> min_coords = find_min_neighbor_coords(matrix, x, y);
        size_t new_x = min_coords.first;
        size_t new_y = min_coords.second;

        if (new_x == x && new_y == y) {
            return matrix[x][y];
        }

        x = new_x;
        y = new_y;
    }
}
bool check_brackets(std::string str) {
    Stack<char> stack(str.length());
    stack.clear();
    for (char c : str) {
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.is_empty()) {
                return false;  
            }
            char top = stack.top();
            stack.pop();

            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false; 
            }
        }
    }
    return stack.is_empty();
}
void read_expression(std::string expression) {
    std::string brackets;
    enum State {
        EXPECT_OPERAND,
        EXPECT_OPERATOR,
        EXPECT_OPERAND_OR_UNARY
    };
    State current_state = EXPECT_OPERAND;
    bool has_operand = false;
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        if (std::isspace(c)) {
            continue;
        }
        // обработка скобок
        if (c == '(' || c == '{' || c == '[' || c == ')' || c == '}' || c == ']') {
            brackets += c;
            if (c == '(' || c == '{' || c == '[') {
                if (current_state != EXPECT_OPERAND && current_state != EXPECT_OPERAND_OR_UNARY) {
                    throw std::invalid_argument("Operand expected before opening bracket");
                }
                current_state = EXPECT_OPERAND;
            }
            else { // закрывающая скобка
                if (current_state == EXPECT_OPERAND) {
                    throw std::invalid_argument("Empty brackets");
                }
                current_state = EXPECT_OPERATOR;
            }
        }
        // обработка операторов
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if ((c == '+' || c == '-') &&
                (current_state == EXPECT_OPERAND || current_state == EXPECT_OPERAND_OR_UNARY)) {
                // унарный оператор - ожидаем операнд
                current_state = EXPECT_OPERAND;
                continue;
            }
            if (current_state != EXPECT_OPERATOR) {
                throw std::invalid_argument("Operator '" + std::string(1, c) + "' in wrong position");
            }
            current_state = EXPECT_OPERAND_OR_UNARY;
        }
        // обработка операндов
        else if (std::isalnum(c)) {
            if (current_state != EXPECT_OPERAND && current_state != EXPECT_OPERAND_OR_UNARY) {
                throw std::invalid_argument("Operator expected before operand");
            }
            has_operand = true;
            // пропускаем операнд
            while (i < expression.length() && std::isalnum(expression[i])) {
                i++;
            }
            i--;
            current_state = EXPECT_OPERATOR;
        }
        else {
            throw std::invalid_argument("Invalid character '" + std::string(1, c) + "' in expression");
        }
    }
    // проверка скобок
    if (!check_brackets(brackets)) {
        throw std::invalid_argument("Unbalanced brackets");
    }
    if (current_state == EXPECT_OPERAND || current_state == EXPECT_OPERAND_OR_UNARY) {
        throw std::invalid_argument("Missing operand at the end of expression");
    }
    if (!has_operand) {
        throw std::invalid_argument("No operands in expression");
    }
}
template <class T> 
bool is_looped1(const List<T>& list) {
    if (list.is_empty()) {
        return false;
    }
    auto it1_fast = list.begin();
    auto it2_slow = list.begin();
    while (it1_fast != list.end()) {
        it2_slow++;
        it1_fast++;
        if (it1_fast != list.end()) {
            it1_fast++;
        }
        if (it1_fast == it2_slow) {
            return true;
        }
    }
    return false; 
}
template <class T>
bool is_looped2(List<T>& list) {
    if (list.is_empty()) {
        return false;
    }
    Node<T>* original_head = list.get_head();
    Node<T>* current = list.get_head();
    Node<T>* prev = nullptr;
    while (current != nullptr) {
        Node<T>* next_temp = current->next;
        current->next = prev;

        prev = current;
        current = next_temp;
    }
    bool has_cycle = (prev == original_head);
    
    current = prev; 
    prev = nullptr;
    while (current != nullptr) {
        Node<T>* next_temp = current->next;
        current->next = prev;
        prev = current;
        current = next_temp;

    }
    return has_cycle;
}
template <class T>
Node<T>* find_loop_start(List<T>& list) {
    if (list.is_empty()) {
        return nullptr;
    }
    Node<T>* it2_slow = list.get_head();
    Node<T>* it1_fast = list.get_head();

    while (it1_fast != nullptr && it1_fast->next != nullptr) {
        it2_slow = it2_slow->next;
        it1_fast = it1_fast->next->next;

        if (it2_slow == it1_fast) {
            break;
        }
    }
    if (it1_fast == nullptr || it1_fast->next == nullptr) {
        return nullptr;
    }
    it2_slow = list.get_head();
    while (it2_slow != it1_fast) {
        it2_slow = it2_slow->next;
        it1_fast = it1_fast->next;
    }
    return it2_slow;
}
size_t get_count_of_islands(Matrix<int>& matrix) {
    if (matrix.is_empty()) {
        return 0;
    }
    size_t N = matrix.getN();
    size_t M = matrix.getM();
    DSU islands(M*N);

    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                if (i == 0 && j == 0) { // верхний левый угол   
                
                }
                else if (i == 0) { //верхняя строка
                    if (matrix[i][j - 1] == 1) {
                        islands.dsu_union(i * N + j, i * N + j - 1);
                    }
                }
                else if (j == 0) { //левый столбец 
                    if (matrix[i - 1][j] == 1) {
                        islands.dsu_union(i * N + j, (i - 1) * N + j);
                    }
                }
                else {
                    if (matrix[i - 1][j] == 1) {
                        islands.dsu_union(i * N + j, (i - 1) * N + j);
                        //соединяем этот элемент с [i][j] union
                    }
                    if (matrix[i][j - 1] == 1) {
                        islands.dsu_union(i * N + j, i * N + j - 1);
                        //соединяем этот элемент с [i][j] union
                    }
                }
            }
        }
    }
    std::unordered_set<int> unique_roots;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                unique_roots.insert(  islands.dsu_find_recursive(i * N + j));
            }
        }
    }
    return unique_roots.size();
}
