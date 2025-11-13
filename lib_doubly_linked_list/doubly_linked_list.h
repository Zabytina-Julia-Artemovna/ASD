#pragma once 
#include <stdexcept>
template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node<T>* previous;
    Node(T value_, Node<T>* next_ = nullptr, Node<T>* previous_ = nullptr) : value(value_), next(next_), previous(previous_) {}
};
template <class T>
class DoublyLinkedList {
private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _count_elements;
public:
    class Iterator {
    private:
        Node<T>* _current;
    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* node) : _current(node) {}
        Iterator(const Iterator& other) : _current(other._current) {}
        Iterator& operator=(const Iterator& other) {
            _current = other._current;
            return *this;
        }
        Iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; ++i) {
                _current = _current->next;
            }
            return *this;
        }
        Iterator& operator-=(size_t n) {
            for (size_t i = 0; i < n && _current != nullptr; --i) {
                _current = _current->previous;
            }
            return *this;
        }
        Iterator& operator++() {
            if (_current != nullptr) {
                _current = _current->next;
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator it = *this;
            if (_current != nullptr) {
                _current = _current->next;
            }
            return it;
        }
        Iterator& operator--() {
            if (_current != nullptr) {
                _current = _current->previous;
            }
            return *this;
        }
        Iterator operator--(int) {
            Iterator it = *this;
            if (_current != nullptr) {
                _current = _current->previous;
            }
            return it;
        }
        bool operator==(const Iterator& it) const {
            return this->_current == it._current;
        }
        bool operator!=(const Iterator& it) const {
            return !(*this == it);
        }
        T& operator*() {
            if (_current == nullptr) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return _current->value;
        }
        const T& operator*() const {
            if (_current == nullptr) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return _current->value;
        }
    };
    Iterator begin() {
        return Iterator(_head);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
    Iterator begin() const {
        return Iterator(_head);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>& other_list);
    size_t get_size() const noexcept;
    Node<T>* get_head() const noexcept;
    Node<T>* get_tail() const noexcept;

    bool operator==(const DoublyLinkedList<T>& other) const;
    bool operator!=(const DoublyLinkedList<T>& other) const;
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);

    bool is_empty() const noexcept;
    void push_back(const T& value) noexcept;
    void push_front(const T& value) noexcept;
    void insert(size_t position, const T& value);
    void insert(Node<T>* node, const T& value);
    void pop_front();
    void pop_back();
    void erase(size_t position);
    void erase(Node<T>* node);
};
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(): _head(nullptr), _tail(nullptr), _count_elements(0) {}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other_list): _head(nullptr), _tail(nullptr), _count_elements(nullptr) {
    for (auto it = other_list.begin(); it != other_list.end(); ++it) {
        this->push_back(*it);
    }
}
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (_head != nullptr) {
        Node<T>* temporary = _head;
        _head = _head->next;
        delete temporary;
    }
}
template <class T>
size_t DoublyLinkedList<T>::get_size() const noexcept {
    return _count_elements;
}
template <class T>
Node<T>* DoublyLinkedList<T>::get_head() const noexcept {
    return _head;
}
template <class T>
Node<T>* DoublyLinkedList<T>::get_tail() const noexcept {
    return _tail;
}
