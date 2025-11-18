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
    class Iterator {
    private:
        Node<T>* _current;
    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* node): _current(node) {}
        Iterator(const Iterator& other): _current(other._current) {}
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
    List();
    ~List();
    List(const List<T>& other_list);
    size_t get_size() const noexcept {
        return _count_elements;
    }
    Node<T>* get_head() const noexcept {
        return _head;
    }
    Node<T>* get_tail() const noexcept {
        return _tail;
    }
    T& get_last_element() {
        if (_tail == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return _tail->value;
    }
    const T& get_last_element() const {
        if (_tail == nullptr) {
            throw std::runtime_error("List is empty");
        }
        return _tail->value;
    }

    bool operator==(const List<T>& other) const;
    bool operator!=(const List<T>& other) const;
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
List<T>::List(const List<T>& other_list) : _head(nullptr), _tail(nullptr),
_count_elements(0) {
    for (auto it = other_list.begin(); it != other_list.end(); ++it) {
        this->push_back(*it);
    }
}
template <class T>
bool List<T>::is_empty() const noexcept {
    return _head == nullptr && _tail == nullptr;
}
template <class T>
void List<T>::push_front(const T& value) noexcept {
    Node<T>* node = new Node<T>(value);
    if (this->is_empty()) {
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
void List<T>::push_back(const T& value) noexcept {
    Node<T>* node = new Node<T>(value);
    if (this->is_empty()) {
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
    if (this->is_empty()) {
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
    if (this->is_empty()) {
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
template <class T>
bool List<T>::operator==(const List<T>& other) const {
    if (this->get_size() != other.get_size()) {
        return false;
    }
    auto it_this = this->begin();
    auto it_other = other.begin();
    while (it_this != this->end() && it_other != other.end()) {
        if (*it_this != *it_other) {
            return false;
        }
        ++it_this;
        ++it_other;
    }
    return true;
}
template <class T>
bool List<T>::operator!=(const List<T>& other) const {
    return !(*this == other);
}
template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this != &other) {
        while (_head != nullptr) {
            Node<T>* temporary = _head;
            _head = _head->next;
            delete temporary;
        }
        _count_elements = 0;
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->push_back(*it);
        }
    }
    return *this;
}
template <class T>
void List<T>::insert(size_t position, const T& value) {
    if (position == 0) {
        this->push_front(value);
        return;
    }
    if (position == _count_elements - 1) {
        this->push_back(value);
        return;
    }
    Node<T>* current = _head;
    size_t current_position = 0;
    while (current != nullptr && current_position != position - 1) {
        current = current->next;
        current_position++;
    }
    if (current == nullptr) {
        throw std::invalid_argument("Uncorrect position");
    }
    this->insert(current, value);
}
template <class T>
void List<T>::insert(Node<T>* node, const T& value) {
    if (node == nullptr || this->is_empty()) {
        throw std::logic_error("The transmitted node or/and the list can't be empty!");
    }
    Node<T>* new_node = new Node<T>(value);
    new_node->next = node->next;
    node->next = new_node;
    if (node == _tail) {
        _tail = new_node;
    }
    _count_elements++;
}
template <class T>
void List<T>::erase(size_t position) {
    if (position == 0) {
        this->pop_front();
        return;
    }
    if (position == _count_elements - 1) {
        this->pop_back();
        return;
    }
    Node<T>* current = _head;
    size_t current_position = 0;
    while (current != nullptr) {
        if (current_position == position - 1) {
            break;
        }
        current = current->next;
        current_position++;
    }
    if (current == nullptr) {
        throw std::invalid_argument("Uncorrect position");
    }
    Node<T>* temporary = current->next;
    current->next = temporary->next;
    delete temporary;
    _count_elements--;
}
template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || this->is_empty()) {
        throw std::logic_error("The transmitted node or/and the list can't be empty!");
    }
    if (node == _head) {
        this->pop_front();
        return;
    }
    if (node == _tail) {
        this->pop_back();
        return;
    }
    Node<T>* current = _head;
    while (current != nullptr && current->next != node) {
        current = current->next;
    }
    if (current == nullptr) {
        throw std::invalid_argument("Uncorrect position");
    }
    current->next = node->next;
    delete node;
    _count_elements--;
}
