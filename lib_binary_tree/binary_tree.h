#pragma once
#include <utility>
#include <iostream>
#include "../lib_queue_on_list/queue_on_list.h"
template <class TKey, class TValue>
struct TNode {
    TNode(const TKey& key, const TValue& value) : data_(key, value), left_(nullptr), right_(nullptr){}
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
    void clear_recursive(TNode<TKey, TValue>* node) noexcept;
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
void BinaryTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
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

//template <class TKey, class TValue>
//TValue* BinaryTree<TKey, TValue>::find(const TKey& key) const noexcept {
//
//}
//
//template <class TKey, class TValue>
//void BinaryTree<TKey, TValue>::erase(const TKey& key) {
//
//}




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