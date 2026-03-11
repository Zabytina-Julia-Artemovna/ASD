#pragma once
#include <utility>
#include <iostream>
#include <stdexcept>
#include "../lib_queue_on_list/queue_on_list.h"
template <class TKey, class TValue>
struct TNode {
    TNode(const TKey& key, const TValue& value) : data_(key, value), left_(nullptr), right_(nullptr) {}
    std::pair<TKey, TValue> data_;
    TNode<TKey, TValue>* left_;
    TNode<TKey, TValue>* right_;
};
template <class TKey, class TValue>
class BinaryTree {
private:
    TNode<TKey, TValue>* _root;

    void print_DLCR_recursive(TNode<TKey, TValue>* node) const;
    void print_DLRC_recursive(TNode<TKey, TValue>* node) const;
    void print_DCLR_recursive(TNode<TKey, TValue>* node) const;
    void print_pretty_recursive(
        TNode<TKey, TValue>* node,
        std::string prefix,
        bool is_left) const;
    void clear_recursive(TNode<TKey, TValue>* node) noexcept;

    TNode<TKey, TValue>* find_node(const TKey& key) const noexcept; // для erase
    std::pair<TNode<TKey, TValue>*, TNode<TKey, TValue>*> find_last_with_parent() const noexcept; // для erase
public:
    BinaryTree();
    ~BinaryTree();
    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);

    void print_width() const;
    void print_DLCR() const;
    void print_DLRC() const;
    void print_DCLR() const;
    void print_pretty() const;

    bool is_empty() const noexcept;
    void clear() noexcept;
};
template <class TKey, class TValue>
BinaryTree<TKey, TValue>::BinaryTree() {
    _root = nullptr;
}
template <class TKey, class TValue>
BinaryTree<TKey, TValue>::~BinaryTree() {
    clear();
}
template <class TKey, class TValue>
bool BinaryTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::insert(const TKey& key, const TValue& value) { // O(n) в лучшем O(1)
    TNode<TKey, TValue>* node = new TNode<TKey, TValue>(key, value);
    if (is_empty()) {
        _root = node;
        return;
    }

    TNode<TKey, TValue>* current = nullptr;
    QueueOnList<TNode<TKey, TValue>*> queue;
    queue.push(_root);
    while (1) {
        current = queue.head();
        queue.pop();
        if (!current->left_) {
            current->left_ = node;
            return;
        }
        if (!current->right_) {
            current->right_ = node;
            return;
        }
        queue.push(current->left_);
        queue.push(current->right_);
    }
}
template <class TKey, class TValue>
std::pair<TNode<TKey, TValue>*, TNode<TKey, TValue>*> BinaryTree<TKey, TValue>::find_last_with_parent() const noexcept { // O(n) в любом случае
    if (is_empty()) {
        return { nullptr, nullptr };
    }
    QueueOnList<TNode<TKey, TValue>*> queue;
    queue.push(_root);
    TNode<TKey, TValue>* last_node = nullptr;
    TNode<TKey, TValue>* parent = nullptr;
    while (1) {
        last_node = queue.head();
        queue.pop();
        if (last_node->left_) {
            queue.push(last_node->left_);
            parent = last_node;
        }
        if (last_node->right_) {
            queue.push(last_node->right_);
            parent = last_node;
        }
        if (queue.is_empty()) {
            return { last_node, parent };
        }
    }
    return { last_node, parent };
}
template <class TKey, class TValue>
TNode<TKey, TValue>* BinaryTree<TKey, TValue>::find_node(const TKey& key) const noexcept { // O(n) в лучшем O(1) если корень
    if (is_empty()) {
        return nullptr;
    }
    QueueOnList<TNode<TKey, TValue>*> queue;
    queue.push(_root);
    TNode<TKey, TValue>* node = nullptr;
    while (1) {
        node = queue.head();
        queue.pop();
        if (node->data_.first == key) {
            return node;
        }
        if (node->left_) {
            queue.push(node->left_);
        }
        if (node->right_) {
            queue.push(node->right_);
        }
        if (queue.is_empty()) {
            return nullptr;
        }
    }
}
template <class TKey, class TValue>
TValue* BinaryTree<TKey, TValue>::find(const TKey& key) const noexcept { // O(n) в лучшем случае O(1)
    if (is_empty()) {
        return nullptr;
    }
    TNode<TKey, TValue>* result = find_node(key);
    if (!result) {
        return nullptr;
    }
    return &(result->data_.second);
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) {
        throw std::logic_error("Cannot erase: tree is empty");
    }
    auto [last, parent_of_last] = find_last_with_parent();
    TNode<TKey, TValue>* target = find_node(key);
    if (!target) {
        throw std::invalid_argument("Cannot erase: key not found");
    }
    if (target == last) { // узел последний/последний и единственный
        if (parent_of_last) {
            if (parent_of_last->left_ == last) {
                parent_of_last->left_ = nullptr;
            }
            else {
                parent_of_last->right_ = nullptr;
            }
        }
        else {
            _root = nullptr;
        }
        delete last;
        return;
    }
    target->data_ = last->data_; // удаляем не последний
    if (parent_of_last->left_ == last) {
        parent_of_last->left_ = nullptr;
    }
    else {
        parent_of_last->right_ = nullptr;
    }
    delete last;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_width() const {
    if (is_empty()) {
        return;
    }
    QueueOnList<TNode<TKey, TValue>*> queue;
    TNode<TKey, TValue>* current = nullptr;
    queue.push(_root);
    while (!queue.is_empty()) {
        current = queue.head();
        std::cout << current->data_.second << " ";
        queue.pop();
        if (current->left_) {
            queue.push(current->left_);
        }
        if (current->right_) {
            queue.push(current->right_);
        }
    }
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DCLR_recursive(TNode<TKey, TValue>* node) const {
    if (node == nullptr) {
        return;
    }
    std::cout << node->data_.second << " ";
    print_DCLR_recursive(node->left_);
    print_DCLR_recursive(node->right_);

}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLRC_recursive(TNode<TKey, TValue>* node) const {
    if (node == nullptr) {
        return;
    }
    print_DLRC_recursive(node->left_);
    print_DLRC_recursive(node->right_);
    std::cout << node->data_.second << " ";
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLCR_recursive(TNode<TKey, TValue>* node) const {
    if (node == nullptr) {
        return;
    }
    print_DLCR_recursive(node->left_);
    std::cout << node->data_.second << " ";
    print_DLCR_recursive(node->right_);

}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLCR() const {
    print_DLCR_recursive(_root);
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DLRC() const {
    print_DLRC_recursive(_root);

}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_DCLR() const {
    print_DCLR_recursive(_root);

}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::clear() noexcept {
    clear_recursive(_root);
    _root = nullptr;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::clear_recursive(TNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) {
        return;
    }
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    delete node;
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_pretty() const {
    print_pretty_recursive(_root, "", true);
}
template <class TKey, class TValue>
void BinaryTree<TKey, TValue>::print_pretty_recursive(
    TNode<TKey, TValue>* node,
    std::string prefix,
    bool is_left) const {
    if (!node) {
        return;
    }
    std::cout << prefix;
    std::cout << (is_left ? "├── " : "└── ");
    std::cout << node->data_.first << ":" << node->data_.second << "\n";
    print_pretty_recursive(node->left_, prefix + (is_left ? "│   " : "    "), true);
    print_pretty_recursive(node->right_, prefix + (is_left ? "│   " : "    "), false);
}
