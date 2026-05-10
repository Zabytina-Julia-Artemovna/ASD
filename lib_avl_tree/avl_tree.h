#pragma once
#include <iostream>
#include <stdexcept>
#include <utility>  
template <class TKey, class TValue>
struct AVLNode {
    AVLNode* left_;
    AVLNode* right_;
    AVLNode* parent_;
    size_t height_;
    std::pair<TKey, TValue> data_;
};
template <class TKey, class TValue>
class AVLTree {
private:
    AVLNode<TKey, TValue>* _root;
    void left_rotate(AVLNode<TKey, TValue>* node);
    void right_rotate(AVLNode<TKey, TValue>* node);
    void LL(AVLNode<TKey, TValue>* node);
    void RR(AVLNode<TKey, TValue>* node);
    void RL(AVLNode<TKey, TValue>* node);
    void LR(AVLNode<TKey, TValue>* node);
    void recover_balance(AVLNode<TKey, TValue>* node);
    void recalc_height(AVLNode<TKey, TValue>* node);
    int calc_balance(AVLNode<TKey, TValue>* node) noexcept;
public:
    AVLTree() : _root(nullptr) {}
    AVLTree(const AVLTree<TKey, TValue>& other);
    ~AVLTree();
    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept;
    void erase(const TKey& key);
    size_t size() const noexcept;
    void clear() noexcept;
    bool is_empty() const noexcept {
        return _root == nullptr; 
    }
};
