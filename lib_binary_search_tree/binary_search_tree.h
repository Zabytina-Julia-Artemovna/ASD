#pragma once
#include <utility>
#include <iostream>
#include <stdexcept>

template <class T>
struct NodeBST {
    NodeBST(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
    T data_;
    NodeBST<T>* left_;
    NodeBST<T>* right_;
};

template <class T>
class BinarySearchTree {
private:
    NodeBST<T>* _root;

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<T>& other);
    ~BinarySearchTree();

    typename T::second_type* find(const typename T::first_type& key) const noexcept;
    void insert(const T& item);  // item - это пара ключ-значение
    void erase(const typename T::first_type& key);

    bool is_empty() const noexcept {
        return _root == nullptr;
    }

    template <class Func>
    void traverse(Func func) const;
    void clear() noexcept;
    void print_DLCR() const;

private:
    void print_DLCR_recursive(NodeBST<T>* node) const;
    NodeBST<T>* copy_node(NodeBST<T>* node) const;
    void clear_recursive(NodeBST<T>* node) noexcept;
    NodeBST<T>* find_parent(const typename T::first_type& key) const noexcept;
    NodeBST<T>* find_node_by_key(const typename T::first_type& key) const noexcept;

    template <class Func>
    void traverse_recursive(NodeBST<T>* node, Func& func) const;

    NodeBST<T>* find_max_left(NodeBST<T>* node) const noexcept;
};

// ==================== Реализации ====================

template <class T>
template <class Func>
void BinarySearchTree<T>::traverse_recursive(
    NodeBST<T>* node,
    Func& func) const {
    if (!node) return;
    traverse_recursive(node->left_, func);
    func(node->data_);
    traverse_recursive(node->right_, func);
}

template <class T>
template <class Func>
void BinarySearchTree<T>::traverse(Func func) const {
    traverse_recursive(_root, func); // рекурсивн. ф-ция обхода дерева (корень, ф-ция котор. примен. к кажд. узлу)
}

template <class T>
NodeBST<T>* BinarySearchTree<T>::find_max_left(NodeBST<T>* node) const noexcept {
    // макс элемент среди всех меньших, чем удаляемый узел

    if (!node || !node->left_) {
        return nullptr;  // нет левого поддерева нет замены
    }

    NodeBST<T>* current = node->left_;

    // Идём ВПРАВО до конца - к самому большому
    while (current->right_) {
        current = current->right_;
    }

    return current;
}

template <class T>
typename T::second_type* BinarySearchTree<T>::find(const typename T::first_type& key) const noexcept {
    NodeBST<T>* node = find_node_by_key(key);
    if (!node) {
        return nullptr; // дерево пустое - элемент НЕ найден
    }
    return &node->data_.second;
}

template <class T>
void BinarySearchTree<T>::insert(const T& item) {
    // Проверка на дубликаты ДО вставки
    if (find_node_by_key(item.first)) {
        throw std::invalid_argument("Key already exists");
    }

    NodeBST<T>* parent = find_parent(item.first);
    if (!parent) {
        _root = new NodeBST<T>(item);
        return;
    }

    NodeBST<T>* new_node = new NodeBST<T>(item);

    if (item.first > parent->data_.first) {
        parent->right_ = new_node;
    }
    else {
        parent->left_ = new_node;
    }
}

template <class T>
NodeBST<T>* BinarySearchTree<T>::find_parent(const typename T::first_type& key) const noexcept {
    if (is_empty()) {
        return nullptr;
    }

    if (_root->data_.first == key) {
        return _root;
    }

    NodeBST<T>* current = _root;
    while (current) {
        if (key < current->data_.first) {
            if (!current->left_) {
                return current;
            }
            if (current->left_->data_.first == key) {
                return current;
            }
            current = current->left_;
        }
        else if (key > current->data_.first) {
            if (!current->right_) {
                return current;
            }
            if (current->right_->data_.first == key) {
                return current;
            }
            current = current->right_;
        }
        else {
            return current;
        }
    }
    return nullptr;
}

template <class T>
NodeBST<T>* BinarySearchTree<T>::find_node_by_key(const typename T::first_type& key) const noexcept {
    NodeBST<T>* current = _root;
    while (current) {
        if (key < current->data_.first) {
            current = current->left_;
        }
        else if (key > current->data_.first) {
            current = current->right_;
        }
        else {
            return current;
        }
    }
    return nullptr;
}

template <class T>
NodeBST<T>* BinarySearchTree<T>::copy_node(NodeBST<T>* node) const {
    if (!node) {
        return nullptr;
    }
    NodeBST<T>* new_node = new NodeBST<T>(node->data_);
    new_node->left_ = copy_node(node->left_);
    new_node->right_ = copy_node(node->right_);

    return new_node;
}

template <class T>
void BinarySearchTree<T>::clear_recursive(NodeBST<T>* node) noexcept {
    if (node == nullptr) {
        return;
    }
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    delete node;
}

template <class T>
void BinarySearchTree<T>::clear() noexcept {
    clear_recursive(_root);
    _root = nullptr;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree() {
    _root = nullptr;
}

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other) {
    _root = copy_node(other._root);
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
    clear();
}

template <class T>
void BinarySearchTree<T>::erase(const typename T::first_type& key) {
    NodeBST<T>* parent = find_parent(key);
    NodeBST<T>* node = nullptr;
    bool is_left_child = false;

    if (!parent) {
        throw std::invalid_argument("Key not found");
    }

    // ключ в корне
    if (parent == _root && _root->data_.first == key) {
        node = _root;
        parent = nullptr;
    }
    // ключ в левом ребёнке
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
        throw std::invalid_argument("Key not found");
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
        NodeBST<T>* child = node->right_;
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
        NodeBST<T>* child = node->left_;

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
        NodeBST<T>* replacer = find_max_left(node);

        // родитель 
        NodeBST<T>* replacer_parent = node;
        NodeBST<T>* temp = node->left_;

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

template <class T>
void BinarySearchTree<T>::print_DLCR_recursive(NodeBST<T>* node) const {
    if (node == nullptr) {
        return;
    }
    print_DLCR_recursive(node->left_);
    std::cout << node->data_.second << " ";
    print_DLCR_recursive(node->right_);
}

template <class T>
void BinarySearchTree<T>::print_DLCR() const {
    print_DLCR_recursive(_root);
}
