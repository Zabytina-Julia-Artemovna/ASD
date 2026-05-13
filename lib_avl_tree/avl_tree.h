#pragma once
#include <iostream>
#include <stdexcept>
#include <utility> 
//nullptr (пустое поддерево) высота - 1
//Ћист(нет детей) высота 0 (так как 1 + max(-1, -1) = 0)
//”зел с одним листом высота 1 (так как 1 + max(0, -1) = 1)
//» т.д.
template <class TKey, class TValue>
struct AVLNode {
    AVLNode<TKey, TValue>* left_;
    AVLNode<TKey, TValue>* right_;
    AVLNode<TKey, TValue>* parent_;
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

    AVLNode<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    AVLNode<TKey, TValue>* bst_insert(const TKey& key, const TValue& value);
    int get_height(AVLNode<TKey, TValue>* node) const noexcept;  

    void clear_recursive(AVLNode<TKey, TValue>* node) noexcept;
    AVLNode<TKey, TValue>* erase_recursive(AVLNode<TKey, TValue>* node, const TKey& key);
    AVLNode<TKey, TValue>* copy_node(
        AVLNode<TKey, TValue>* node);
    template <class Func>
    void traverse_recursive(AVLNode<TKey, TValue>* node, Func& func) const;
    AVLNode<TKey, TValue>* find_node(const TKey& key) const noexcept; //дл€ insert(), т.к. проверка bst_insert() Ќа дубликат ключа не полна€
public:
    AVLTree() : _root(nullptr) {}
    AVLTree(const AVLTree<TKey, TValue>& other);
    ~AVLTree();

    void insert(const TKey& key, const TValue& value);
    TValue* find(const TKey& key) const noexcept; 
    void erase(const TKey& key);

    bool is_empty() const noexcept;
    void clear() noexcept;
    template <class Func>
    void traverse(Func func) const;
};
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
    AVLNode<TKey, TValue>* current = _root;
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
template <class TKey, class TValue>
template <class Func>
void AVLTree<TKey, TValue>::traverse_recursive(
    AVLNode<TKey, TValue>* node,
    Func& func) const {
    if (!node) return;
    traverse_recursive(node->left_, func);
    func(node->data_);
    traverse_recursive(node->right_, func);
}
template <class TKey, class TValue>
template <class Func>
void AVLTree<TKey, TValue>::traverse(Func func) const {
    traverse_recursive(_root, func); // рекурсивн. ф-ци€ обхода дерева (корень, ф-ци€ котор. примен. к кажд. узлу)
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::copy_node(
    AVLNode<TKey, TValue>* node) {
    if (!node) {
        return nullptr;
    }
    AVLNode<TKey, TValue>* new_node = new AVLNode<TKey, TValue>{
        nullptr,
        nullptr,
        nullptr,
        node->height_,
        node->data_
    };
    new_node->left_ = copy_node(node->left_);
    new_node->right_ = copy_node(node->right_);
    // ќбновл€ем parent у детей
    if (new_node->left_) {
        new_node->left_->parent_ = new_node;
    }
    if (new_node->right_) {
        new_node->right_->parent_ = new_node;
    }
    return new_node;
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) {
    if (!node || !node->right_) {
        return;
    }
    // 1. «апоминаем правого ребенка (он станет новым корнем поддерева)
    AVLNode<TKey, TValue>* child = node->right_;
    AVLNode<TKey, TValue>* parent = node->parent_;
    // 2. ѕравый ребенок node становитс€ левым ребенком child
    node->right_ = child->left_;
    if (child->left_) {
        child->left_->parent_ = node;
    }
    // 3. child поднимаетс€ на место node
    child->left_ = node;
    node->parent_ = child;
    // 4. ќбновл€ем parent у child
    child->parent_ = parent;
    // 5. ≈сли был родитель, обновл€ем его указатель на child
    if (parent) {
        if (parent->left_ == node) {
            parent->left_ = child;
        }
        else {
            parent->right_ = child;
        }
    }
    else {
        // node был корнем
        _root = child;
    }
    // 6. ќбновл€ем высоты
    recalc_height(node);
    recalc_height(child);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) {
    if (!node || !node->left_) {
        return;
    }
    // 1. «апоминаем левого ребенка (он станет новым корнем поддерева)
    AVLNode<TKey, TValue>* child = node->left_;
    AVLNode<TKey, TValue>* parent = node->parent_;
    // 2. Ћевый ребенок node становитс€ правым ребенком child
    node->left_ = child->right_;
    if (child->right_) {
        child->right_->parent_ = node;
    }
    // 3. child поднимаетс€ на место node
    child->right_ = node;
    node->parent_ = child;
    // 4. ќбновл€ем parent у child
    child->parent_ = parent;
    // 5. ≈сли был родитель, обновл€ем его указатель на child
    if (parent) {
        if (parent->left_ == node) {
            parent->left_ = child;
        }
        else {
            parent->right_ = child;
        }
    }
    else {
        // node был корнем
        _root = child;
    }
    // 6. ќбновл€ем высоты
    recalc_height(node);
    recalc_height(child);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) {
    left_rotate(node);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) {
    right_rotate(node);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) {
    right_rotate(node->right_);
    left_rotate(node);
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) {
    left_rotate(node->left_);
    right_rotate(node);
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::get_height(AVLNode<TKey, TValue>* node) const noexcept {
    return node ? node->height_ : -1;
}
//LL = проблема слева - слева - поворачиваем вправо
//
//RR = проблема справа - справа - поворачиваем влево
//
//LR = проблема слева - справа - сначала влево(на ребенке), потом вправо(на узле)
//
//RL = проблема справа - слева - сначала вправо(на ребенке), потом влево(на узле)
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recover_balance(AVLNode<TKey, TValue>* node) {
    if (!node) return;

    recalc_height(node);
    int balance = calc_balance(node);

    if (balance == 2) {  // Ћевое т€желее
        if (calc_balance(node->left_) == -1) {
            LR(node);
        }
        else {
            LL(node); 
        }
    }
    else if (balance == -2) {  // ѕравое т€желее
        if (calc_balance(node->right_) == 1) {
            RL(node);
        }
        else {
            RR(node); 
        }
    }
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) {
    if (!node) {
        return;
    }
    node->height_ = 1 + std::max(get_height(node->left_), get_height(node->right_));
}
template <class TKey, class TValue>
int AVLTree<TKey, TValue>::calc_balance(AVLNode<TKey, TValue>* node) const noexcept {
    if (!node) {
        return 0;
    }
    return get_height(node->left_) - get_height(node->right_);
}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree(const AVLTree<TKey, TValue>& other) {
    _root = copy_node(other._root);
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
    // ѕроверка на дубликаты
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
    if (!parent) {
        return nullptr;
    }
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
    if (find_node(key)) {
        throw std::invalid_argument("Key already exists");
    }
    AVLNode<TKey, TValue>* new_node = bst_insert(key, value);
    AVLNode<TKey, TValue>* current = new_node;
    while (current) {
        recalc_height(current);
        int balance = calc_balance(current);
        // Ћевое т€желее
        if (balance == 2) {
            if (calc_balance(current->left_) == -1) {
                LR(current);
            }
            else {
                LL(current); 
            }
        }
        // ѕравое т€желее
        else if (balance == -2) {
            if (calc_balance(current->right_) == 1) {
                RL(current);
            }
            else {
                RR(current);
            }
        }
        current = current->parent_;
    }
}
template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    _root = erase_recursive(_root, key);
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::erase_recursive(
    AVLNode<TKey, TValue>* node,
    const TKey& key) {
    if (!node) {
        throw std::invalid_argument("Key not found");
    }
    // ищем удал узел
    if (key < node->data_.first) {
        node->left_ = erase_recursive(node->left_, key);
        if (node->left_) node->left_->parent_ = node;
    }
    else if (key > node->data_.first) {
        node->right_ = erase_recursive(node->right_, key);
        if (node->right_) node->right_->parent_ = node;
    }
    else {
        // если найден - удал

        //  0 или 1 реб
        if (!node->left_ || !node->right_) {
            AVLNode<TKey, TValue>* child = node->left_ ? node->left_ : node->right_;
            delete node;
            return child;
        }

        //2 ребенка ищем замену
        AVLNode<TKey, TValue>* replacer = node->left_;
        while (replacer->right_) {
            replacer = replacer->right_;
        }
        node->data_ = replacer->data_;
        // ”дал замену рекурсивно
        node->left_ = erase_recursive(node->left_, replacer->data_.first);
        if (node->left_) node->left_->parent_ = node;
    }
    recalc_height(node);
    recover_balance(node);

    return node;
}
