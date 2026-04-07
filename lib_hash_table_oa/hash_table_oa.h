#pragma once
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include "../lib_itable/itable.h"

#define SIZE 100
#define SHIFT 7

enum Status {
    busy,
    empty,
    deleted
};

template <class TValue>
struct HashData {
    Status state_ = empty;
    std::string key_;
    TValue value_;
    HashData() = default;
    HashData(const std::string& key, const TValue& value, Status state)
        : state_(state), key_(key), value_(value) {}
};

template <class TValue>
class HashTableOA : public ITable<std::string, TValue> {
private:
    std::vector<HashData<TValue>> _rows;
    size_t _size;
    size_t _count;
    size_t _shift;

public:

    size_t size() const noexcept override { 
        return _count;
    }

    HashTableOA(size_t size) : _size(size), _count(0), _shift(SHIFT), _rows(size) {
        for (size_t i = std::max<size_t>(2, _size / 15); i < _size; i++) {
            if (is_simple(i, _size)) {
                _shift = i;
                break;
            }
        }
    }

    bool is_empty() const noexcept {
        return _count == 0;
    }

    bool is_full() const noexcept {
        return _size == _count;
    }

    void insert(const std::string& key, const TValue& value) override;
    void erase(const std::string& key) override;
    TValue& find(const std::string& key) override;
    const TValue& find(const std::string& key) const override;
private:
    size_t h(const std::string& key) const noexcept {
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); i++) {
            hash += key[i];
        }
        hash %= _size;
        return hash;
    }

    size_t hh(size_t hash) const noexcept {
        return (hash + _shift) % _size;
    }

    bool is_simple(size_t a, size_t b) const noexcept {
        while (b != 0) {
            size_t temp = b;
            b = a % b;
            a = temp;
        }
        return a == 1;
    }
};

template <class TValue>
void HashTableOA<TValue>::insert(const std::string& key, const TValue& value) {
    if (is_full()) {
        throw std::logic_error("Hash table is full");
    }
    size_t hash = h(key);
    while (1) {
        if (_rows[hash].state_ != busy) {
            _rows[hash] = HashData<TValue>(key, value, busy);
            _count++;
            return;
        }
        if (_rows[hash].key_ == key) {
            throw std::logic_error("Key already exist");
        }
        hash = hh(hash);
    }
}

template <class TValue>
void HashTableOA<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;
    while (1) {
        if (_rows[hash].state_ == Status::empty) {
            break;
        }
        if (_rows[hash].state_ == Status::busy && _rows[hash].key_ == key) {
            _rows[hash].state_ = Status::deleted;
            _count--;
            return;
        }
        hash = hh(hash);
        if (first_hash == hash) {
            break;
        }
    }
    throw std::logic_error("Key not found");
}

template <class TValue>
TValue& HashTableOA<TValue>::find(const std::string& key) {
    // TODO: реализация
    throw std::logic_error("Not implemented");
}

template <class TValue>
const TValue& HashTableOA<TValue>::find(const std::string& key) const {
    // TODO: реализация
    throw std::logic_error("Not implemented");
}