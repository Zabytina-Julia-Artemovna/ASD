#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include "../lib_itable/itable.h"
//каждый элемент массива хранит список с элементами, имеющими одинаковый хеш
template <class TValue>
class HashTableChain : public ITable<std::string, TValue> {
private:
    std::vector<std::list <std::pair <std::string,TValue> > > _rows;
    size_t _count;
public:
    size_t size() const noexcept override {
        return _count;
    }
    bool is_empty() const noexcept {
        return _count == 0;
    }
    HashTableChain(size_t size = 100): _rows(size), _count(0) {}
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
        hash %= _rows.size();
        return hash;
    }
};
template <class TValue>
void HashTableChain<TValue>::insert(const std::string& key, const TValue& value) {
    size_t index = h(key);
    auto& chain = _rows[index];
    for (auto it = chain.begin(); it != chain.end(); it++) {
        if (it->first == key) {
            throw std::logic_error("Key already exists");
        }
    }
    chain.push_back(std::make_pair(key, value));
    _count++;
    return;
}
template <class TValue>
void HashTableChain<TValue>::erase(const std::string& key) {
    size_t index = h(key);
    auto& chain = _rows[index];
    for (auto it = chain.begin(); it != chain.end(); it++) {
        if (it->first == key) {
            chain.erase(it);
            _count--;
            return;
        } 
    }
    throw std::logic_error("Key not found");
}
template <class TValue>
TValue& HashTableChain<TValue>::find(const std::string& key) {
    const HashTableChain& const_this = static_cast<const HashTableChain&>(*this);
    const TValue& result = const_this.find(key);
    return const_cast<TValue&>(result);
}
template <class TValue>
const TValue& HashTableChain<TValue>::find(const std::string& key) const {
    size_t index = h(key);
    for (const auto& pair : _rows[index]) { 
        if (pair.first == key) {
            return pair.second;
       }
    }
    throw std::logic_error("Element not found");
}
