#pragma once
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
public:
    List();
    ~List();
    List(const List<T>& other_list);

    bool operator==(const List<T>& other) const;
    List<T>& operator=(const List<T>& other);

    bool is_empty() const noexcept;
    void push_back(const T& value) noexcept;
    void push_front(const T& value) noexcept;
    void insert(size_t position, const T& value);
    void insert(Node<T>* node, const T& value);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void erase(size_t position);
    void erase(Node<T>* node);
};
