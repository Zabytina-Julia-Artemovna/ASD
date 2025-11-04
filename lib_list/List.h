#pragma once
template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node(T value_, Node<T>* next_ = nullptr) {
        value = value_;
        next = next_;
    }
};
template <class T>
class List {
private:
    Node<T>* _head;
    Node<T>* _tail;
public:

};
