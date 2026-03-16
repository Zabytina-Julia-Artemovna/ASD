#pragma once
#include <utility>
#include <iostream>
#include <stdexcept>
template <class TKey, class TValue>
struct Node {
    Node(const TKey& key, const TValue& value) : data_(key, value), left_(nullptr), right_(nullptr) {}
    std::pair<TKey, TValue> data_;
    Node* left_;
    Node* right_;
};
template <class TKey, class TValue>
class BinarySearchTree {
private:
    Node<TKey, TValue>* _root;
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<TKey, TValue>& other);
    ~BinarySearchTree();   
    TValue* find(const TKey& key) const noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey & key);
    bool is_empty() const noexcept{
        return _root == nullptr;
    }
    void clear() noexcept;
    void print_DLCR() const; 
private:
    void print_DLCR_recursive(Node<TKey, TValue>* node) const;
    Node<TKey, TValue>* copy_node(
        const Node<TKey, TValue>* node) const;
    void clear_recursive(Node<TKey, TValue>* node) noexcept;
    Node<TKey, TValue>* find_parent(const TKey& key) const noexcept;
};
template <class TKey, class TValue>
TValue* BinarySearchTree<TKey, TValue>::find(const TKey& key) const noexcept {
    Node<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        return nullptr;
    }
    if (parent->left_ && parent->left_->data_.first == key) {
        return &parent->left_->data_.second;
    }
    else if (parent->right_ && parent->right_->data_.first == key) {
        return &parent->right_->data_.second;
    }
    else if (parent == _root) {
        return &_root->data_.second;
    }
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Node<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new Node<TKey, TValue>(key, value);
        return;
    }
    if (parent->left_ && parent->left_->data_.first == key) {
        throw std::invalid_argument("Key already exists");
    }
    if (parent->right_ && parent->right_->data_.first == key) {
        throw std::invalid_argument("Key already exists");
    }
    if (!parent->right_ && parent->data_.first < key) {
        parent->right_ = new Node<TKey, TValue>(key, value);
    }
    else { 
        parent->left_ = new Node<TKey, TValue>(key, value);
    }
}
template <class TKey, class TValue>
Node<TKey, TValue>* BinarySearchTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) {
        return nullptr;
    }
    if (_root->data_.first == key) {
        return _root;
    }
    Node<TKey, TValue>* current = _root;
    while (1) {
        if (current->data_.first > key) {
            if (!current->left_) {
                return current;
            }
            if (current->left_->data_.first == key) {
                return current;
            }
            else {
                current = current->left_;
            }
        }
        else {
            if (!current->right_) {
                return current;
            }
            if (current->right_->data_.first == key) {
                return current;
            }
            else {
                current = current->right_;
            }
        }
    }
}

template <class TKey, class TValue>
Node<TKey, TValue>* BinarySearchTree<TKey, TValue>::copy_node(
    const Node<TKey, TValue>* node) const {
    if (!node) {
        return nullptr;
    }
    Node<TKey, TValue>* new_node = new Node<TKey, TValue>(
        node->data_.first,
        node->data_.second
    );
    new_node->left_ = copy_node(node->left_);
    new_node->right_ = copy_node(node->right_);

    return new_node;
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::clear_recursive(Node<TKey, TValue>* node) noexcept {
    if (node == nullptr) {
        return;
    }
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    delete node;
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::clear() noexcept {
    clear_recursive(_root);
    _root = nullptr;
}
template <class TKey, class TValue>
BinarySearchTree<TKey, TValue>::BinarySearchTree() {
    _root = nullptr;
}
template <class TKey, class TValue>
BinarySearchTree<TKey, TValue>::BinarySearchTree(const BinarySearchTree<TKey, TValue>& other) {
    _root = copy_node(other._root);
}
template <class TKey, class TValue>
BinarySearchTree<TKey, TValue>::~BinarySearchTree() {
    clear();
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::print_DLCR_recursive(Node<TKey, TValue>* node) const {
    if (node == nullptr) {
        return;
    }
    print_DLCR_recursive(node->left_);
    std::cout << node->data_.second << " ";
    print_DLCR_recursive(node->right_);

}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::print_DLCR() const {
    print_DLCR_recursive(_root);
}
