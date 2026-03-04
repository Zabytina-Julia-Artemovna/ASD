#pragma once
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/List.h"
#include "../lib_dsu/dsu.h"
#include <random>
#include <utility> 
#include <string>
#include <cctype>
#include <unordered_set>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>     // srand
#include <time.h>       // time
#include <Windows.h>
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
    DSU islands(M * N);

    // Все 8 направлений
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // верхние
        {0, -1},           {0, 1},   // левый, правый  
        {1, -1},  {1, 0},  {1, 1}    // нижние
    };

    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                // Проверяем всех 8 соседей
                for (auto& dir : directions) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];

                    if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
                        if (matrix[ni][nj] == 1) {
                            islands.dsu_union(i * N + j, ni * N + nj);
                        }
                    }
                }
            }
        }
    }

    std::unordered_set<int> unique_roots;
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            if (matrix[i][j] == 1) {
                unique_roots.insert(islands.dsu_find_recursive(i * N + j));
            }
        }
    }
    return unique_roots.size();
}

bool** generate(int X, int Y, int N, int M) {
    if ((N < 2) || (M < 2)) { throw std::invalid_argument("Wrong size"); }

    int size_maze = N * M;
    DSU maze(size_maze);

    int new_N = N * 2 + 1, new_M = M + 1, size_walls = new_N * new_M;
    bool** walls = new bool* [new_N];
    for (int i = 0; i < new_N; i++) {
        walls[i] = new bool[new_M];
    }

    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_M; j++) {
            if ((i % 2 == 0) && (j == M)) walls[i][j] = false;
            else walls[i][j] = true;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int random_on_the_right = rand() % 2;
            int random_on_the_bottom = rand() % 2;
            if ((random_on_the_right == 0) && (j != (M - 1)) && (maze.dsu_find_recursive(i * M + j) != maze.dsu_find_recursive(i * M + j + 1))) {   // + проверка на 
                //состояние в dsu, тогда не нужно убирать стену
                maze.dsu_union(i * M + j, i * M + j + 1);
                walls[i * 2 + 1][j + 1] = false;
            }
            if ((random_on_the_bottom == 0) && (i != (N - 1)) && (maze.dsu_find_recursive(i * M + j) != maze.dsu_find_recursive(i * M + j + M))) {   // + проверка на 
                //состояние в dsu, тогда не нужно убирать стену
                maze.dsu_union(i * M + j, i * M + j + M);
                walls[i * 2 + 2][j] = false;
            }
        }
    }

    int i_x = X / M, j_x = X % M, i_y = Y / M, j_y = Y % M;
    if (i_x == 0) walls[0][j_x] = false;
    else if (i_x == N - 1) walls[new_N - 1][j_x] = false;
    else if (j_x == 0) walls[i_x * 2 + 1][0] = false;
    else if (j_x == M - 1) walls[i_x * 2 + 1][new_M - 1] = false;

    if (i_y == 0) walls[0][j_y] = false;
    else if (i_y == N - 1) walls[new_N - 1][j_y] = false;
    else if (j_y == 0) walls[i_y * 2 + 1][0] = false;
    else if (j_y == M - 1) walls[i_y * 2 + 1][new_M - 1] = false;

    if (maze.dsu_find_recursive(X) == maze.dsu_find_recursive(Y)) return walls;
    else {
        for (int i = 0; i < new_N; i++) {
            delete[] walls[i];
        }
        delete[] walls;

        return generate(X, Y, N, M);
    }
}

void print(bool** labirint, int N, int M) {
    int new_N = N * 2 + 1, new_M = M + 1;
    for (int i = 0; i < new_N; i++) {
        for (int j = 0; j < new_M; j++) {
            if (i % 2 == 0) {
                if (labirint[i][j] == true) std::cout << " --";
                else std::cout << "   ";
            }
            else {
                if (labirint[i][j] == true) std::cout << "|  ";
                else std::cout << "   ";
            }
        }
        std::cout << "\n";
    }
