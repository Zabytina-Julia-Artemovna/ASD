#pragma once 
#include <iostream>
#include <stdexcept>
#include <utility> 
//Правила баланса: 1 корень черный 2 NULL эл черные 3 дети красного - черные  4 черный путь до листа одинак для всех
enum Color {
    red,
    black
};

template <class T>
struct RBNode {
    T data_;
    RBNode<T>* left_;
    RBNode<T>* right_;
    RBNode<T>* parent_;
    Color color_;
    int height_; //"черн." высота
};

template <class T>
class RBTree {
private:
    RBNode<T>* _root;

    //Для удаления
    Color get_color(RBNode<T>* node) const;
    void fix_erase(RBNode<T>* node); //восстановление после удаления
    RBNode<T>* find_node_by_key(const typename T::first_type& key) const noexcept; //first_type - 
    //чтобы в find передавать не всю пару а только ключ

    void left_rotate(RBNode<T>* node); // используются в recover_balance и fix_erase - восстан. баланса
    void right_rotate(RBNode<T>* node);

    void recalc_height(RBNode<T>* node);
    void recover_balance(RBNode<T>* node); //восстановление после вставки
    void recolor(RBNode<T>* node);

    RBNode<T>* find_parent(const typename T::first_type& key) const noexcept;
    RBNode<T>* copy_node(RBNode<T>* node);
    RBNode<T>* bst_insert(const T& item);

    int get_height(RBNode<T>* node) const noexcept;

    void clear_recursive(RBNode<T>* node) noexcept;
    RBNode<T>* erase_recursive(RBNode<T>* node, const typename T::first_type& key);
    template <class Func>
    void traverse_recursive(RBNode<T>* node, Func& func) const;
public:
    RBTree() : _root(nullptr) {}
    RBTree(const RBTree<T>& other);
    ~RBTree();

    void insert(const T& item);  // item - это пара ключ-значение
    typename T::second_type* find(const typename T::first_type& key) const noexcept;
    void erase(const typename T::first_type& key);

    bool is_empty() const noexcept;
    void clear() noexcept;
    template <class Func>
    void traverse(Func func) const;
};

template <class T>
void RBTree<T>::insert(const T& item) {
    RBNode<T>* node = bst_insert(item); //возвращает родителя
    recover_balance(node);  //логика перекрашивания внутри
    if (_root) {
        _root->color_ = Color::black;
    }
}

template <class T>
typename T::second_type* RBTree<T>::find(const typename T::first_type& key) const noexcept {
    RBNode<T>* node = find_node_by_key(key);
    if (!node) {
        return nullptr;
    }
    return &node->data_.second;
}

template <class T>
void RBTree<T>::erase(const typename T::first_type& key) {
    if (!find_node_by_key(key)) {
        throw std::invalid_argument("Key not found");
    }

    _root = erase_recursive(_root, key);

    if (_root) {
        _root->color_ = Color::black; //независимо 
            // вызван был при вставке или удалении метод восстановления/нет, корень перекраш в черный 
    }
}

template <class T>
RBNode<T>* RBTree<T>::erase_recursive(RBNode<T>* node, const typename T::first_type& key) {
    if (!node) return nullptr;

    // Ищем узел
    if (key < node->data_.first) {
        node->left_ = erase_recursive(node->left_, key);
        if (node->left_) node->left_->parent_ = node;
    }
    else if (key > node->data_.first) {
        node->right_ = erase_recursive(node->right_, key);
        if (node->right_) node->right_->parent_ = node;
    }
    else {
        // если найден, Удаляем

        // 1) нет детей или 1 ребенок
        if (!node->left_ || !node->right_) {
            RBNode<T>* child = node->left_ ? node->left_ : node->right_;

            // Запоминаем цвет перед удалением
            Color deleted_color = node->color_;

            delete node;

            // Если удалили чёрный узел
            if (deleted_color == Color::black && child) {
                fix_erase(child);
            }

            return child;  
        }

        // 2) два ребенка
        // Ищем замену (самый правый в левом поддереве)
        RBNode<T>* replacer = node->left_;
        while (replacer->right_) {
            replacer = replacer->right_;
        }

        // Копируем данные
        node->data_ = replacer->data_;

        // Удаляем замену
        node->left_ = erase_recursive(node->left_, replacer->data_.first);
        if (node->left_) node->left_->parent_ = node;
    }
    recalc_height(node);

    return node; //возвращает указатель на узел, который должен стать новым ребёнком родителя удалённого узла
}

template <class T>
Color RBTree<T>::get_color(RBNode<T>* node) const {
    return node ? node->color_ : Color::black;  
}

//1	Смотрим на брата удалённого узла
//2	Если брат красный -> перекрашиваем и поворачиваем
//3	Если брат чёрный и его дети чёрные -> перекрашиваем брата в красный
//4	Если брат чёрный и один из его детей красный -> повороты и перекрашивание
//Главное : восстанавливаем свойство "чёрн высота" после удаления чёрного узла
template <class T>
void RBTree<T>::fix_erase(RBNode<T>* node) {
    // Пока node не корень и он чёрный
    while (node != _root && get_color(node) == Color::black) {

        if (node == node->parent_->left_) {
            RBNode<T>* brother = node->parent_->right_;

            // 1) Брат красный
            if (get_color(brother) == Color::red) {
                brother->color_ = Color::black;
                node->parent_->color_ = Color::red;
                left_rotate(node->parent_);
                brother = node->parent_->right_;
            }

            // 2) Брат чёрный и его дети чёрные
            if (get_color(brother) == Color::black &&
                get_color(brother->left_) == Color::black &&
                get_color(brother->right_) == Color::black) {
                brother->color_ = Color::red;
                node = node->parent_;
            }
            else {
                // 3) Правый ребёнок брата чёрный
                if (get_color(brother->right_) == Color::black) {
                    if (brother->left_) {
                        brother->left_->color_ = Color::black;
                    }
                    brother->color_ = Color::red;
                    right_rotate(brother);
                    brother = node->parent_->right_;
                }

                // 4) Правый ребёнок брата красный
                brother->color_ = node->parent_->color_;
                node->parent_->color_ = Color::black;
                if (brother->right_) {
                    brother->right_->color_ = Color::black;
                }
                left_rotate(node->parent_);
                node = _root;
            }
        }
        else { // Симметричный случай (node == node->parent_->right_)
            RBNode<T>* brother = node->parent_->left_;

            // 1) Брат красный
            if (get_color(brother) == Color::red) {
                brother->color_ = Color::black;
                node->parent_->color_ = Color::red;
                right_rotate(node->parent_);
                brother = node->parent_->left_;
            }

            // 2) Брат чёрный и его дети чёрные
            if (get_color(brother) == Color::black &&
                get_color(brother->left_) == Color::black &&
                get_color(brother->right_) == Color::black) {
                brother->color_ = Color::red;
                node = node->parent_;
            }
            else {
                // 3) Левый ребёнок брата чёрный
                if (get_color(brother->left_) == Color::black) {
                    if (brother->right_) {
                        brother->right_->color_ = Color::black;
                    }
                    brother->color_ = Color::red;
                    left_rotate(brother);
                    brother = node->parent_->left_;
                }

                // 4) Левый ребёнок брата красный
                brother->color_ = node->parent_->color_;
                node->parent_->color_ = Color::black;
                if (brother->left_) {
                    brother->left_->color_ = Color::black;
                }
                right_rotate(node->parent_);
                node = _root;
            }
        }
    }
    if (node) {
        node->color_ = Color::black;
    }
}
template <class T>
RBNode<T>* RBTree<T>::find_node_by_key(const typename T::first_type& key) const noexcept {
    RBNode<T>* current = _root;
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
void RBTree<T>::recover_balance(RBNode<T>* node) {
    while (node != _root && node->parent_->color_ == Color::red) {

        RBNode<T>* parent = node->parent_;
        RBNode<T>* grandparent = parent->parent_;

        if (parent == grandparent->left_) {
            RBNode<T>* uncle = grandparent->right_; //родитель слева, дядя справа

            if (uncle && uncle->color_ == Color::red) {
                recolor(parent);     
                recolor(uncle);
                recolor(grandparent);
                node = grandparent; //подним на уров выше
            }
            else {
                if (node == parent->right_) {
                    node = parent;
                    left_rotate(node);
                    parent = node->parent_; //подним на уров выше
                }
                recolor(parent);
                recolor(grandparent);
                right_rotate(grandparent);
            }
        }
        else { // родитель справа, дядя слева
            RBNode<T>* uncle = grandparent->left_;

            if (uncle && uncle->color_ == Color::red) {
                recolor(parent);
                recolor(uncle);
                recolor(grandparent);
                node = grandparent; //подним на уров выше
            }
            else {
                if (node == parent->left_) {
                    node = parent;
                    right_rotate(node);
                    parent = node->parent_; //подним на уров выше
                }
                recolor(parent);
                recolor(grandparent);
                left_rotate(grandparent);
            }
        }
    }
}

template <class T>
void RBTree<T>::recalc_height(RBNode<T>* node) {
    if (!node) return;

    int left_h = get_height(node->left_);   // черная высота левого ребенка
    int right_h = get_height(node->right_); // черная высота правого ребенка

    node->height_ = std::max(left_h, right_h) + (node->color_ == Color::black ? 1 : 0);
}

template <class T>
void RBTree<T>::recolor(RBNode<T>* node) {
    if (!node) {
        return;
    }
    if (node->color_ == Color::black) {
        node->color_ = Color::red;
    }
    else {
        node->color_ = Color::black;
    }
}

template <class T>
RBNode<T>* RBTree<T>::copy_node(RBNode<T>* node) {
    if (!node) {
        return nullptr;
    }
    RBNode<T>* new_node = new RBNode<T>{
        node->data_,
        nullptr,
        nullptr,
        nullptr,
        node->color_,
        node->height_
    };
    new_node->left_ = copy_node(node->left_);
    new_node->right_ = copy_node(node->right_);
    // Обновляем parent у детей
    if (new_node->left_) {
        new_node->left_->parent_ = new_node;
    }
    if (new_node->right_) {
        new_node->right_->parent_ = new_node;
    }
    return new_node;
}

template <class T>
RBNode<T>* RBTree<T>::bst_insert(const T& item) {
    // Проверка на дубликаты ДО вставки
    if (find_node_by_key(item.first)) {
        throw std::invalid_argument("Key already exists");
    }

    RBNode<T>* parent = find_parent(item.first);
    if (!parent) {
        _root = new RBNode<T>{
            item,
            nullptr,
            nullptr,
            nullptr,
            Color::black,
            0
        };
        return _root;
    }

    RBNode<T>* new_node = new RBNode<T>{
        item,
        nullptr,
        nullptr,
        parent,
        Color::red,
        0
    };

    if (item.first > parent->data_.first) {
        parent->right_ = new_node;
    }
    else {
        parent->left_ = new_node;
    }

    return new_node;
}

template <class T>
RBNode<T>* RBTree<T>::find_parent(const typename T::first_type& key) const noexcept {
    if (!_root) return nullptr;

    if (_root->data_.first == key) return _root;

    RBNode<T>* current = _root;
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

template <class T>
bool RBTree<T>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class T>
template <class Func>
void RBTree<T>::traverse_recursive(
    RBNode<T>* node,
    Func& func) const {
    if (!node) return;
    traverse_recursive(node->left_, func);
    func(node->data_);
    traverse_recursive(node->right_, func);
}

template <class T>
template <class Func>
void RBTree<T>::traverse(Func func) const {
    traverse_recursive(_root, func);
}

template<class T>
RBTree<T>::RBTree(const RBTree<T>& other) {
    _root = copy_node(other._root);
}

template<class T>
RBTree<T>::~RBTree() {
    clear();
}

template <class T>
void RBTree<T>::clear_recursive(RBNode<T>* node) noexcept {
    if (node == nullptr) {
        return;
    }
    clear_recursive(node->left_);
    clear_recursive(node->right_);
    delete node;
}

template <class T>
void RBTree<T>::clear() noexcept {
    clear_recursive(_root);
    _root = nullptr;
}

template <class T>
void RBTree<T>::left_rotate(RBNode<T>* node) {
    if (!node || !node->right_) {
        return;
    }
    // запоминаем правого ребенка (он станет новым корнем поддерева)
    RBNode<T>* child = node->right_;
    RBNode<T>* parent = node->parent_;
    //правый ребенок node становится левым ребенком child
    node->right_ = child->left_;
    if (child->left_) {
        child->left_->parent_ = node;
    }
    //child поднимается на место node
    child->left_ = node;
    node->parent_ = child;
    // Обновляем parent у child
    child->parent_ = parent;
    // е был родитель, обновляем его указатель на child
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
    recalc_height(node);
    recalc_height(child);
}

template <class T>
void RBTree<T>::right_rotate(RBNode<T>* node) {
    if (!node || !node->left_) {
        return;
    }
    //запоминаем левого ребенка (он - нов корнем поддерева)
    RBNode<T>* child = node->left_;
    RBNode<T>* parent = node->parent_;
    // лев ребенок node становится правым ребенком child
    node->left_ = child->right_;
    if (child->right_) {
        child->right_->parent_ = node;
    }
    //child поднимается на место node
    child->right_ = node;
    node->parent_ = child;
    //обновл parent у child
    child->parent_ = parent;
    // е был родитель, обновляем его указатель на child
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
    recalc_height(node);
    recalc_height(child);
}

template <class T>
int RBTree<T>::get_height(RBNode<T>* node) const noexcept {
    return node ? node->height_ : 0;
}