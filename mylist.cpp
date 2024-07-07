#include <memory>
#include <stdexcept>
#include "mylist.hpp"

template <typename T>
ListNode<T>::ListNode(
    const T& data, std::shared_ptr<ListNode<T>> next,
    std::weak_ptr<ListNode<T>> prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
    this->def_weak_ptr = std::shared_ptr<ListNode<T>>(nullptr);
}

template <typename T>
ListNode<T>::ListNode(
    const T& data, std::shared_ptr<ListNode<T>> next
) {
    this->data = data;
    this->next = next;
    this->def_weak_ptr = std::shared_ptr<ListNode<T>>(nullptr);
    this->prev = this->def_weak_ptr;
}

template <typename T>
T ListNode<T>::getData() const {
    return this->data;
}

template <typename T>
void ListNode<T>::setData(const T& data) {
    this->data = data;
}

template <typename T>
std::shared_ptr<ListNode<T>> ListNode<T>::getNext() const {
    return this->next;
}

template <typename T>
std::weak_ptr<ListNode<T>> ListNode<T>::getPrev() const {
    return this->prev;
}

template <typename T>
void ListNode<T>::setNext(std::shared_ptr<ListNode<T>> next) {
    this->next = next;
}

template <typename T>
void ListNode<T>::setPrev(std::weak_ptr<ListNode<T>> prev) {
    this->prev = prev;
}

template <typename T>
void MyList<T>::PushBack(const T& elem) {
    if (this->size == 0) {
        std::shared_ptr<ListNode<T>> node = std::make_shared<ListNode<T>>(
            ListNode<T>{elem, nullptr});
        this->start = node;
        this->end = node;
    } else {
        std::shared_ptr<ListNode<T>> node = std::make_shared<ListNode<T>>(
            ListNode<T>{elem, nullptr, this->end});
        this->end->setNext(node);
        this->end = node;
    }
    this->size += 1;
}

template <typename T>
void MyList<T>::PopBack() {
    if (this->size == 0) {
        throw std::out_of_range("Impossible to pop_back from empty list!");
    } else if (this->size == 1) {
        this->start = nullptr;
        this->end = nullptr;
    } else {
        std::shared_ptr<ListNode<T>> end_node = this->end->getPrev().lock();
        end_node->setNext(nullptr);
        this->end->setPrev(
            std::shared_ptr<ListNode<T>>(nullptr));
        this->end = end_node;
    }
    this->size -= 1;
}

template <typename T>
T MyList<T>::Back() const {
    if (this->size == 0) {
        throw std::out_of_range("MyList is empty!");
    } else {
        return this->end->getData();
    }
}

template <typename T>
int MyList<T>::getSize() const {
    return this->size;
}

template <typename T>
std::shared_ptr<ListNode<T>> MyList<T>::getStart() const {
    if (this->size == 0) {
        throw std::out_of_range("MyList is empty!");
    }
    return this->start;
}
