#pragma once
#include <iostream>
#include <stdexcept>
#include <utility> 
#include "../lib_binary_search_tree/binary_search_tree.h"
//nullptr (пустое поддерево) - высота - 1
//
//Лист(нет детей) - высота 0 (так как 1 + max(-1, -1) = 0)
//
//Узел с одним листом - высота 1 (так как 1 + max(0, -1) = 1)
//
//И так далее...
template <class TKey, class TValue>
struct AVLNode {
    AVLNode* left_;
    AVLNode* right_;
    AVLNode* parent_;
    int height_;
    std::pair<TKey, TValue> data_;
};
template <class TKey, class TValue>
class AVLTree {
private:
    AVLNode<TKey, TValue>* _root;

    void left_rotate(AVLNode<TKey, TValue>* node);
    void right_rotate(AVLNode<TKey, TValue>* node);
    void RR(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);

    void recover_balance(AVLNode<TKey, TValue>* node);
    void recalc_height(AVLNode<TKey, TValue>* node);
    int calc_balance(AVLNode<TKey, TValue>* node) const noexcept;

    // Вспомогательные методы
    AVLNode<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    AVLNode<TKey, TValue>* bst_insert(const TKey& key, const TValue& value);
    int get_height(AVLNode<TKey, TValue>* node) const noexcept;  

    void clear_recursive(AVLNode<TKey, TValue>* node) noexcept;
public:
    AVLTree() : _root(nullptr) {}
    AVLTree(const AVLTree<TKey, TValue>& other);
    ~AVLTree();

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;
};
template <class TKey, class TValue>
int AVLTree<TKey, TValue>::get_height(AVLNode<TKey, TValue>* node) const noexcept {
    return node ? node->height_ : -1;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) {
    if (!node) return;
    node->height_ = 1 + std::max(get_height(node->left_), get_height(node->right_));
}
template <class TKey, class TValue>
int AVLTree<TKey, TValue>::calc_balance(AVLNode<TKey, TValue>* node) const noexcept {
    if (!node) return 0;
    return get_height(node->left_) - get_height(node->right_);
}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(const AVLTree<TKey, TValue>& other) {
    // TODO: реализовать глубокое копирование
}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {
    clear();
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear_recursive(AVLNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) {
        return;
    }
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    delete node;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear() noexcept {
    clear_recursive(_root);
    _root = nullptr;
}
template <class TKey, class TValue>
bool AVLTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (!_root) return nullptr;

    if (_root->data_.first == key) return _root;

    AVLNode<TKey, TValue>* current = _root;
    while (current) {
        if (key < current->data_.first) {
            if (!current->left_) return current;
            if (current->left_->data_.first == key) return current;
            current = current->left_;
        }
        else if (key > current->data_.first) {
            if (!current->right_) return current;
            if (current->right_->data_.first == key) return current;
            current = current->right_;
        }
        else {
            return current;
        }
    }
    return nullptr;
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::bst_insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        //лист имеет высоту 0
        _root = new AVLNode<TKey, TValue>{ nullptr, nullptr, nullptr, 0, {key, value} };
        return _root;
    }
    // Проверка на дубликаты
    if ((parent->left_ && parent->left_->data_.first == key) ||
        (parent->right_ && parent->right_->data_.first == key)) {
        throw std::invalid_argument("Key already exists");
    }
    //новый лист имеет высоту 0
    AVLNode<TKey, TValue>* new_node = new AVLNode<TKey, TValue>{ nullptr, nullptr, parent, 0, {key, value} };

    if (key > parent->data_.first) {
        parent->right_ = new_node;
    }
    else {
        parent->left_ = new_node;
    }

    return new_node;
}
template <class TKey, class TValue>
TValue* AVLTree<TKey, TValue>::find(const TKey& key) const noexcept {
    AVLNode<TKey, TValue>* parent = find_parent(key);
    if (!parent) return nullptr;

    if (parent == _root && _root->data_.first == key) {
        return &_root->data_.second;
    }
    if (parent->left_ && parent->left_->data_.first == key) {
        return &parent->left_->data_.second;
    }
    if (parent->right_ && parent->right_->data_.first == key) {
        return &parent->right_->data_.second;
    }
    return nullptr;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* new_node = bst_insert(key, value);

    AVLNode<TKey, TValue>* current = new_node;
    while (current) {
        recalc_height(current);

        int balance = calc_balance(current);

        // Левое поддерево тяжелее
        if (balance == 2) {
            // Случай LR: левый-правый
            if (calc_balance(current->left_) == -1) {
                left_rotate(current->left_);
            }
            // Случай LL: левый-левый (и завершение LR)
            right_rotate(current);
        }
        // Правое поддерево тяжелее
        else if (balance == -2) {
            // Случай RL: правый-левый
            if (calc_balance(current->right_) == 1) {
                right_rotate(current->right_);
            }
            // Случай RR: правый-правый (и завершение RL)
            left_rotate(current);
        }
        current = current->parent_;
    }
}
