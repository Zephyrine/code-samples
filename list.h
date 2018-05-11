#pragma once

#include <iostream> // to delete once done

template <typename T>
class List {

    class ListNode;
    class ValueListNode;

public:

    class Iterator:
            public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        Iterator(ListNode* current): current_(current) {}

        Iterator() {}

        // pre++
        Iterator& operator++() {
            current_ = current_->next;
            return *this;
        };

        //post++
        Iterator operator++(int) {
            Iterator cpy(*this);
            current_ = current_->next;
            return cpy;
        };

        // pre--
        Iterator& operator--() {
            current_ = current_->prev;
            return *this;
        };

        // post--
        Iterator operator--(int) {
            Iterator cpy(*this);
            current_ = current_->prev;
            return cpy;
        };

        T& operator*() const {
            return (static_cast<ValueListNode*>(current_))->value_;
        };

        T* operator->() const {
            return &(static_cast<ValueListNode*>(current_))->value_;
        };

        bool operator==(const Iterator& rhs) const {
            return current_ == rhs.current_;
        };

        bool operator!=(const Iterator& rhs) const {
            return current_ != rhs.current_;
        };

    private:
        ListNode* current_;
    };

    List() {
        sentinel = new ListNode();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        size_ = 0;
    };

    List(const List& rhs) {
        sentinel = new ListNode();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        size_ = 0;
        if (rhs.IsEmpty()) {
            return;
        }
        for (auto x = rhs.Begin(); x != rhs.End(); ++x) {
            PushBack(*x);
        }
        size_ = rhs.size_;
    };

    List(List&& rhs) {
        sentinel = rhs.sentinel;
        size_ = rhs.size_;
        rhs.sentinel = new ListNode();
        rhs.sentinel->next = rhs.sentinel;
        rhs.sentinel->prev = rhs.sentinel;
        rhs.size_ = 0;
    }

    ~List() {
        if (sentinel != nullptr) {
            while (sentinel->prev != sentinel) {
                PopBack();
            }
            delete sentinel;
        }
    };

    void Swap(List &rhs) {
        std::swap(sentinel, rhs.sentinel);
        std::swap(size_, rhs.size_);
    }

    List& operator=(List rhs) {
        Swap(rhs);
        return *this;
    }

    // the above is used instead of these two
//    List& operator=(const List& rhs);
//    List& operator=(List&& rhs);

    bool IsEmpty() const {
        return (size_ == 0);
    };

    size_t Size() const {
        return size_;
    };

    void Unlink(ListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete static_cast<ValueListNode*>(node);
        --size_;
    };

    void LinkAfter(ListNode* target, ListNode* after) {
        after->next->prev = target;
        target->next = after->next;
        after->next = target;
        target->prev = after;
        ++size_;
    };

    void PushBack(const T& elem) {
        LinkAfter(new ValueListNode(elem), sentinel->prev);
    };

    void PushBack(T&& elem) {
        LinkAfter(new ValueListNode(std::move(elem)), sentinel->prev);
    };

    void PushFront(const T& elem) {
        LinkAfter(new ValueListNode(elem), sentinel);
    };

    void PushFront(T&& elem) {
        LinkAfter(new ValueListNode(std::move(elem)), sentinel);
    };

    T& Front() {
        if (sentinel->next != sentinel) {
            return (static_cast<ValueListNode*>(sentinel->next))->value_;
        }
    };

    const T& Front() const {
        if (sentinel->next != sentinel) {
            return (static_cast<ValueListNode*>(sentinel->next))->value_;
        }
    };

    T& Back() {
        if (sentinel->prev != sentinel) {
            return (static_cast<ValueListNode*>(sentinel->prev))->value_;
        }
    };

    const T& Back() const {
        if (sentinel->prev != sentinel) {
            return (static_cast<ValueListNode*>(sentinel->prev))->value_;
        }
    };

    void PopBack() {
        Unlink(sentinel->prev);
    };

    void PopFront() {
        Unlink(sentinel->next);
    };


    Iterator Begin() const {
        return Iterator(sentinel->next);
    }

    Iterator End() const {
        return Iterator(sentinel);
    }

    Iterator begin() {
        return Begin();
    }

    Iterator end() {
        return End();
    }


private:
    class ListNode {
    public:
        ListNode() {}
        //if ref to parent type, parent type destructor gets called.
        // use virtual destructor or cast to child type to use that of child type
        // forum post re: why destructors http://www.cplusplus.com/forum/general/8767/
        ~ListNode() {}

        ListNode* prev;
        ListNode* next;
    };

    class ValueListNode: public ListNode {
    public:
        ValueListNode(const T& value) : value_(value) {}
        ValueListNode(T&& value) : value_(std::move(value)) {}
        ~ValueListNode() {}
        T value_;
    };

    ListNode* sentinel;
    size_t size_;
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list);

template <typename T>
typename List<T>::Iterator end(List<T>& list);
