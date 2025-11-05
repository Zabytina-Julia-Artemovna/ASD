#pragma once
#include <stdexcept>
template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};
template <class T>
class List {
private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _count_elements;
public:
    List();
    ~List();
    List(const List<T>& other_list);

    size_t get_size() const noexcept;
    Node<T>* get_head() const noexcept;
    Node<T>* get_tail() const noexcept;

    bool operator==(const List<T>& other) const;
    List<T>& operator=(const List<T>& other);

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
List<T>::List() : _head(nullptr), _tail(nullptr), _count_elements(0) {}
template <class T>
List<T>::~List() {
    while (_head != nullptr) {
        Node<T>* temporary = _head;
        _head = _head->next;
        delete temporary;
    }
}
template <class T>
List<T>::List(const List<T>& other_list) : _head(nullptr), _tail(nullptr), _count_elements(0) {
    Node<T>* current = other_list._head;
    while (current != nullptr) {
        this->push_back(current->value);
        current = current->next;
    }
}
template <class T>
size_t List<T>::get_size() const noexcept { 
    return _count_elements; 
}
template <class T>
Node<T>* List<T>::get_head() const noexcept {
    return _head;
}
template <class T>
Node<T>* List<T>::get_tail() const noexcept {
    return _tail;
}
template <class T>
bool List<T>::is_empty() const noexcept {
    return _head == nullptr && _tail == nullptr;
}
template <class T>
void List<T>::push_front(const T& value) noexcept {
    Node<T>* node = new Node<T>(value);
    if (is_empty()) {
        _head = node;
        _tail = node;
        _count_elements++;
        return;
    }
    node->next = _head;
    _head = node;
    _count_elements++;
}
template <class T>
void List<T>::push_back(const T& value) noexcept{
    Node<T>* node = new Node<T>(value);
    if (is_empty()) {
        _head = node;
        _tail = node;
        _count_elements++;
        return;
    }
    _tail->next = node;
    _tail = node;
    _count_elements++;
}
template <class T>
void List<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("Can't pop the first element at empty list!");
    }
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count_elements--;
        return;
    }
    Node<T>* temporary = _head;
    _head = _head->next;
    delete temporary;
    _count_elements--;
}
template <class T>
void List<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("Can't pop the last element at empty list!");
    }
    if (_head == _tail) {
        delete _head;
        _tail = nullptr;
        _head = nullptr;
        _count_elements--;
        return;
    }
    Node<T>* current = _head;
    while (current->next != _tail) {
        current = current->next;
    }
    Node<T>* temporary = current->next;
    _tail = current; 
    _tail->next = nullptr;
    delete temporary;
    _count_elements--;  
}
