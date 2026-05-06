#pragma once
#include <utility>
#include <iostream>
#include <stdexcept>
template <class TKey, class TValue>
struct NodeBST {
    NodeBST(const TKey& key, const TValue& value) : data_(key, value), left_(nullptr), right_(nullptr) {}
    std::pair<TKey, TValue> data_;
    NodeBST* left_;
    NodeBST* right_;
};
template <class TKey, class TValue>
class BinarySearchTree {
private:
    NodeBST<TKey, TValue>* _root;
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
    template <class Func>
    void traverse(Func func) const;
    void clear() noexcept;
    void print_DLCR() const; 
private:
    void print_DLCR_recursive(NodeBST<TKey, TValue>* node) const;
    NodeBST<TKey, TValue>* copy_node(
        const NodeBST<TKey, TValue>* node) const;
    void clear_recursive(NodeBST<TKey, TValue>* node) noexcept;
    NodeBST<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    template <class Func>
    void traverse_recursive(NodeBST<TKey, TValue>* node, Func& func) const;
    NodeBST<TKey, TValue>* find_max_left(NodeBST<TKey, TValue>* node) const noexcept;
};
template <class TKey, class TValue>
template <class Func>
void BinarySearchTree<TKey, TValue>::traverse_recursive(
    NodeBST<TKey, TValue>* node,
    Func& func) const {
    if (!node) return;
    traverse_recursive(node->left_, func);   
    func(node->data_);                       
    traverse_recursive(node->right_, func); 
}
template <class TKey, class TValue>
template <class Func>
void BinarySearchTree<TKey, TValue>::traverse(Func func) const {
    traverse_recursive(_root, func); // рекурсивн. ф-ция обхода дерева (корень, ф-ция котор. примен. к кажд. узлу)
}
template <class TKey, class TValue>
NodeBST<TKey, TValue>* BinarySearchTree<TKey, TValue>::find_max_left(NodeBST<TKey, TValue>* node) const noexcept {
    // Ищем САМЫЙ ПРАВЫЙ узел в ЛЕВОМ поддереве
    // Это будет максимальный элемент среди всех МЕНЬШИХ, чем удаляемый узел

    if (!node || !node->left_) {
        return nullptr;  // нет левого поддерева нет замены
    }

    NodeBST<TKey, TValue>* current = node->left_;

    // Идём ВПРАВО до упора (к самому большому)
    while (current->right_) {
        current = current->right_;
    }

    return current;  // возвращаем узел-замену
}
template <class TKey, class TValue>
TValue* BinarySearchTree<TKey, TValue>::find(const TKey& key) const noexcept {
    NodeBST<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        return nullptr; // дерево пустое - элемент НЕ найден
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
    return nullptr; // дерево не пустое, но такого ключа нет - элемент НЕ найден
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    NodeBST<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new NodeBST<TKey, TValue>(key, value);
        return;
    }
    if (parent->left_ && parent->left_->data_.first == key) {
        throw std::invalid_argument("Key already exists");
    }
    if (parent->right_ && parent->right_->data_.first == key) {
        throw std::invalid_argument("Key already exists");
    }
    if (!parent->right_ && parent->data_.first < key) {
        parent->right_ = new NodeBST<TKey, TValue>(key, value);
    }
    else { 
        parent->left_ = new NodeBST<TKey, TValue>(key, value);
    }
}
template <class TKey, class TValue>
NodeBST<TKey, TValue>* BinarySearchTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) {
        return nullptr;
    }
    if (_root->data_.first == key) {
        return _root;
    }
    NodeBST<TKey, TValue>* current = _root;
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
NodeBST<TKey, TValue>* BinarySearchTree<TKey, TValue>::copy_node(
    const NodeBST<TKey, TValue>* node) const {
    if (!node) {
        return nullptr;
    }
    NodeBST<TKey, TValue>* new_node = new NodeBST<TKey, TValue>(
        node->data_.first,
        node->data_.second
    );
    new_node->left_ = copy_node(node->left_);
    new_node->right_ = copy_node(node->right_);

    return new_node;
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::clear_recursive(NodeBST<TKey, TValue>* node) noexcept {
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
void BinarySearchTree<TKey, TValue>::erase(const TKey& key) {
    NodeBST<TKey, TValue>* parent = find_parent(key);
    NodeBST<TKey, TValue>* node = nullptr;
    bool is_left_child = false; //поиск
    // ключ в корне
    if (parent == _root && _root->data_.first == key) {
        node = _root;
        parent = nullptr;  // у корня нет родителя
    }
    //ключ в левом ребёнке
    else if (parent->left_ && parent->left_->data_.first == key) {
        node = parent->left_;
        is_left_child = true;
    }
    // ключ в правом ребёнке
    else if (parent->right_ && parent->right_->data_.first == key) {
        node = parent->right_;
        is_left_child = false;
    }
    else {
        return;
    }
    //удаление
    // узел - лист
    if (!node->left_ && !node->right_) {
        if (!parent) {
            _root = nullptr;
        }
        else if (is_left_child) {
            parent->left_ = nullptr;
        }
        else {
            parent->right_ = nullptr;
        }
        delete node;
    }
    //  У узла 1 ребенок
    else if (!node->left_) {
        NodeBST<TKey, TValue>* child = node->right_;
        if (!parent) {
            _root = child;
        }
        else if (is_left_child) {
            parent->left_ = child;
        }
        else {
            parent->right_ = child;
        }
        delete node;
    }
    else if (!node->right_) {
        NodeBST<TKey, TValue>* child = node->left_;

        if (!parent) {
            _root = child;
        }
        else if (is_left_child) {
            parent->left_ = child;
        }
        else {
            parent->right_ = child;
        }
        delete node;
    }

    // у узла 2 ребенка
    else {
        // ищем самый правый узел в левом поддереве
        NodeBST<TKey, TValue>* replacer = find_max_left(node);  

        // родитель 
        NodeBST<TKey, TValue>* replacer_parent = node;
        NodeBST<TKey, TValue>* temp = node->left_;

        // вправо до конца запомин родителя
        while (temp->right_) {
            replacer_parent = temp;
            temp = temp->right_;
        }
        // copy данные из заменяющего узла в удаляемый
        node->data_ = replacer->data_;

        // delete заменяющий узел (у него нет правого ребёнка по определению)
        if (replacer_parent->left_ == replacer) {
            replacer_parent->left_ = replacer->left_;  // может быть левый ребёнок
        }
        else {
            replacer_parent->right_ = replacer->left_;
        }
        delete replacer;
    }
}
template <class TKey, class TValue>
void BinarySearchTree<TKey, TValue>::print_DLCR_recursive(NodeBST<TKey, TValue>* node) const {
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
