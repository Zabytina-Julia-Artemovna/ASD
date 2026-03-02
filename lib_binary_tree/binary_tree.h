#pragma once
#include <utility>
#include "../lib_queue/queue.h"
template <class TKey, class TValue>
struct Node {
    std::pair<TKey, TValue> data_;
    Node<TKey, TValue>* left_;
    Node<TKey, TValue>* right_;
};
template <class TKey, class TValue>
class BinaryTree {
private:
    Node<TKey, TValue>* _root;

    void print_DLCR_recursive(Node<TKey, TValue>* node) const;
    void print_DLRC_recursive(Node<TKey, TValue>* node) const;
    void print_DCLR_recursive(Node<TKey, TValue>* node) const;
    void clear_recursive(Node<TKey, TValue>* node) noexcept;
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
