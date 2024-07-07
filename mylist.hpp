#pragma once
#include <memory>

template <typename T>
class ListNode {
 private:
    T data;
    std::weak_ptr<ListNode<T>> def_weak_ptr;
    std::shared_ptr<ListNode<T>> next;
    std::weak_ptr<ListNode<T>> prev;
 public:
    ListNode(const T& data, std::shared_ptr<ListNode<T>> next,
    std::weak_ptr<ListNode<T>> prev);
    ListNode(const T& data, std::shared_ptr<ListNode<T>> next);
    T getData() const;
    void setData(const T& data);
    std::shared_ptr<ListNode<T>> getNext() const;
    std::weak_ptr<ListNode<T>> getPrev() const;
    void setNext(std::shared_ptr<ListNode<T>>);
    void setPrev(std::weak_ptr<ListNode<T>>);
};

template <typename T>
class MyList {
 private:
    int size = 0;
    std::shared_ptr<ListNode<T>> start = nullptr;
    std::shared_ptr<ListNode<T>> end = nullptr;
 public:
    void PushBack(const T& elem);
    void PopBack();
    T Back() const;
    int getSize() const;
    std::shared_ptr<ListNode<T>> getStart() const;
};
