#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <functional>
#include <utility>

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
> class avl {
    using Value = std::pair<const Key, T>;
    using value_ptr = std::shared_ptr<Value>;

    struct Node {
        value_ptr value;
        int32_t h;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

    using node_ptr = std::shared_ptr<Node>;
    using weak_node_ptr = std::weak_ptr<Node>;

private:
    node_ptr defaultNode = nullptr;
    node_ptr root = nullptr;
    int32_t size_ = 0;
    Compare compare;
    Allocator allocator;
    Value defaultValue;

    node_ptr rightRotate(node_ptr rootNode) {
        node_ptr a = rootNode;
        node_ptr b = rootNode->left;
        node_ptr additNode = b->right;

        if (additNode) {
            additNode->parent = a;
        }

        b->parent = a->parent;
        b->right = a;

        a->left = additNode;
        a->parent = b;

        rootNode->h = 1 + std::max(
            getHeight(rootNode->left), getHeight(rootNode->right));
        b->h = 1 + std::max(
            getHeight(b->left), getHeight(b->right));

        return b;
    }

    node_ptr leftRotate(node_ptr rootNode) {
        node_ptr a = rootNode;
        node_ptr b = rootNode->right;
        node_ptr additNode = b->left;

        if (additNode) {
            additNode->parent = a;
        }

        b->parent = a->parent;
        b->left = a;

        a->right = additNode;
        a->parent = b;

        rootNode->h = 1 + std::max(
            getHeight(rootNode->left), getHeight(rootNode->right));
        b->h = 1 + std::max(
            getHeight(b->left), getHeight(b->right));

        return b;
    }

    node_ptr search(node_ptr curNode, Key key) const {
        if (curNode == nullptr || (
            !compare(key, curNode->value->first) &&
            !compare(curNode->value->first, key))
            ) {
            return curNode;
        }
        if (compare(key, curNode->value->first)) {
            return search(curNode->left, key);
        }
        return search(curNode->right, key);
    }

    int getHeight(node_ptr node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->h;
    }

    int getBalance(node_ptr node) const {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    node_ptr insert(
        node_ptr curNode,
        Value elem
    ) {
        if (curNode == nullptr) {
            value_ptr val = std::make_shared<Value>(elem);
            return std::make_shared<Node>(
                Node{val, 1, defaultNode, nullptr, nullptr});
        }
        if (compare(elem.first, curNode->value->first)) {
            curNode->left = insert(curNode->left, elem);
            curNode->left->parent = curNode;
        } else if (compare(curNode->value->first, elem.first)) {
            curNode->right = insert(curNode->right, elem);
            curNode->right->parent = curNode;
        } else {
            return curNode;
        }

        curNode->h = 1 + std::max(
            getHeight(curNode->left), getHeight(curNode->right));

        int balance = getBalance(curNode);

        if (balance > 1 && compare(elem.first, curNode->left->value->first)) {
            return rightRotate(curNode);
        }

        if (balance < -1 && compare(curNode->right->value->first, elem.first)) {
            return leftRotate(curNode);
        }

        if (balance > 1 && compare(curNode->left->value->first, elem.first)) {
            curNode->left = leftRotate(curNode->left);
            return rightRotate(curNode);
        }

        if (balance < -1 && compare(elem.first, curNode->right->value->first)) {
            curNode->right = rightRotate(curNode->right);
            return leftRotate(curNode);
        }

        return curNode;
    }

    node_ptr erase(
        node_ptr rootNode, Key key
    ) {
        if (rootNode == nullptr) {
            return rootNode;
        }
        if (compare(key, rootNode->value->first)) {
            rootNode->left = erase(rootNode->left, key);
        } else if (compare(rootNode->value->first, key)) {
            rootNode->right = erase(rootNode->right, key);
        } else {
            if (rootNode->left && rootNode->right) {
                node_ptr nextNode = minNode(rootNode->right);
                rootNode->value = nextNode->value;
                rootNode->right = erase(rootNode->right,
                rootNode->value->first);
            } else if (rootNode->left) {
                rootNode->left->parent = rootNode->parent;
                rootNode = rootNode->left;
            } else if (rootNode->right) {
                rootNode->right->parent = rootNode->parent;
                rootNode = rootNode->right;
            } else {
                return nullptr;
            }
        }

        rootNode->h = 1 + std::max(
            getHeight(rootNode->left), getHeight(rootNode->right));

        int balance = getBalance(rootNode);

        if (balance > 1 && getBalance(rootNode->left) >= 0) {
            return rightRotate(rootNode);
        }
        if (balance > 1 && getBalance(rootNode->left) < 0) {
            rootNode->left = leftRotate(rootNode->left);
            return rightRotate(rootNode);
        }
        if (balance < -1 && getBalance(rootNode->right) <= 0) {
            return leftRotate(rootNode);
        }
        if (balance < -1 && getBalance(rootNode->right) > 0) {
            rootNode->right = rightRotate(rootNode->right);
            return leftRotate(rootNode);
        }

        return rootNode;
    }

    node_ptr minNode(node_ptr curNode) const {
        if (curNode->left == nullptr) {
            return curNode;
        }
        return minNode(curNode->left);
    }

    node_ptr maxNode(node_ptr curNode) const {
        if (curNode->right == nullptr) {
            return curNode;
        }
        return maxNode(curNode->right);
    }

    node_ptr getNext(node_ptr curNode) const {
        if (curNode->right != nullptr) {
            return minNode(curNode->right);
        }
        node_ptr parentNode = curNode->parent.lock();
        while (parentNode && parentNode->right == curNode) {
            curNode = parentNode;
            parentNode = parentNode->parent.lock();
        }
        return parentNode;
    }

    node_ptr getPrev(node_ptr curNode) const {
        if (curNode->left) {
            return maxNode(curNode->left);
        }
        node_ptr parentNode = curNode->parent.lock();
        while (parentNode && parentNode->left == curNode) {
            curNode = parentNode;
            parentNode = parentNode->parent.lock();
        }
        return parentNode;
    }

    bool is_balanced(node_ptr curNode) const {
        if (curNode == nullptr) {
            return true;
        }
        int balance = getBalance(curNode);
        if (abs(balance) < 2 &&
        is_balanced(curNode->left) &&
        is_balanced(curNode->right)) {
            return true;
        }
        return false;
    }

public:
    explicit avl(const std::initializer_list<Value>& elems) {
        for (const auto& elem : elems) {
            insert(elem);
        }
    }

    struct avl_iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = std::pair<const Key, T>;
        using pointer           = std::pair<const Key, T>*;
        using reference         = std::pair<const Key, T>&;

     private:
        const avl& avl_instance;
        std::shared_ptr<Node> m_ptr;
        bool go_forward;

     public:
        avl_iterator(
            std::shared_ptr<Node> ptr, const avl& instance, bool forward):
            avl_instance(instance), m_ptr(ptr), go_forward(forward) {}

        reference operator*() const {
            return *(m_ptr->value.get());
        }

        pointer operator->() const {
            return m_ptr->value.get();
        }

        avl_iterator& operator++() {
            if (go_forward) {
                m_ptr = avl_instance.getNext(m_ptr);
            } else {
                m_ptr = avl_instance.getPrev(m_ptr);
            }
            return *this;
        }

        avl_iterator& operator--() {
            if (go_forward) {
                m_ptr = avl_instance.getPrev(m_ptr);
            } else {
                m_ptr = avl_instance.getNext(m_ptr);
            }
            return *this;
        }

        friend bool operator==(
            const avl_iterator& a,
            const avl_iterator& b) {
            return a.m_ptr == b.m_ptr;
        }

        friend bool operator!=(
            const avl_iterator& a,
            const avl_iterator& b) {
            return a.m_ptr != b.m_ptr;
        }
    };

    avl_iterator begin() {
        node_ptr beginNode = minNode(this->root);
        return avl_iterator(beginNode, *this, true);
    }

    avl_iterator rbegin() {
        node_ptr beginNode = maxNode(this->root);
        return avl_iterator(beginNode, *this, false);
    }

    avl_iterator end() {
        node_ptr endNode = maxNode(this->root);
        return avl_iterator(endNode->right, *this, true);
    }

    avl_iterator rend() {
        node_ptr endNode = minNode(this->root);
        return avl_iterator(endNode->left, *this, false);
    }

    T& operator[](const Key& key) {
        if (!contains(key)) {
            insert(this->defaultValue);
        }
        node_ptr node = search(root, key);
        return node->value->second;
    }

    avl_iterator find(const Key& key) {
        node_ptr node = search(root, key);
        if (node == nullptr) {
            return this->end();
        }
        return avl_iterator{node, *this, true};
    }

    void insert(Value elem) {
        if (!contains(elem.first)) {
            this->root = insert(root, elem);
            this->size_ += 1;
        }
    }

    void erase(const Key& key) {
        if (contains(key)) {
            this->root = erase(this->root, key);
            this->size_ -= 1;
        }
    }

    T at(const Key& key) const {
        node_ptr node = search(root, key);
        if (node == nullptr) {
            throw std::out_of_range("Key is not in the map!");
        }
        return node->value->second;
    }

    bool contains(const Key& key) const {
        node_ptr node = search(root, key);
        if (node == nullptr) {
            return false;
        }
        return true;
    }

    int32_t size() const {
        return this->size_;
    }

    bool empty() const {
        return (this->size_ == 0);
    }

    void clear() {
        this->root = nullptr;
    }

    bool is_balanced() const {
        return is_balanced(this->root);
    }
};
