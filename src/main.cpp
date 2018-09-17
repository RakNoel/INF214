//
// Created by raknoel on 17.09.18.
//

#include "alang.hpp"
#include <cassert>

using namespace std;

template<typename E>
class queue;    // forward declaration
template<typename E>
class node_iterator;  // forward declaration

template<typename E>
class node {
    E data;
    node<E> *next;

    node(E d, node<E> *n) : data(d), next(n) {}

public:

    friend class queue<E>;         // allow queue<E> to access private members
    friend class node_iterator<E>; // allow node_iterator<E> to access private members
};

template<typename E>
class node_iterator {
    node<E> *it;
public:
    node_iterator(node<E> *n) : it(n) {}

    node_iterator &operator++() {
        assert(it != nullptr);
        it = it->next;
        return *this;
    }

    bool done() const { return it == nullptr; }

    E operator*() const {
        assert(it != nullptr);
        return it->data;
    }
};

template<typename E>
class queue {
    node<E> *head;
    node<E> *rear;
    int _size;
public:
    queue() : head(nullptr), rear(nullptr), _size(0) {}

    bool empty() const { return _size == 0; }
    // alternatively we could test for head or rear being equal to nullptr

    void enqueue(E d) {
        auto newNode = new node<E>(d, nullptr);
        if (rear == nullptr) { // enqueueing the first element
            head = newNode;
        } else {
            rear->next = newNode;
        }
        rear = newNode;
        _size++;
    }

    E dequeue() {
        if (empty()) throw "empty queue";
        node<E> *oldHead = head;
        head = head->next;
        if (head == nullptr) rear = nullptr; // removed the last element
        E e = oldHead->data;
        delete oldHead;
        _size--;
        return e;
    }

    int size() const {
        return _size;
    }

    node_iterator<E> iterator() {
        return head;
    }
};

const int N = 1000;

int main() {
    queue<int> q;

    {
        processes ps;
        ps += [&] {
            for (int i = 0; i < N; ++i) {
                q.enqueue(1);
            }
        };
        ps += [&] {
            for (int i = 0; i < N; ++i) {
                q.enqueue(2);
            }
        };
    }
    alang::logl("Elements enqueued: ", 2 * N);
    alang::logl("Queue size: ", q.size());

    auto it = q.iterator();
    int ctr = 0;
    while (!it.done()) {
        ++ctr;
        ++it;
    }
    alang::logl("Elements in queue: ", ctr);

    alang::logl("---------------");

    int successful_dequeues = 0;
    q = queue<int>(); // a new empty queue
    {
        processes ps;
        ps += [&] {
            for (int i = 0; i < N; ++i) {
                q.enqueue(1);
            }
        };
        ps += [&] {
            int c = 0;
            for (int i = 0; i < N; ++i) {
                try {
                    q.dequeue();
                    ++c;
                } catch (...) {}
            }
            successful_dequeues = c;
        };
    }
    alang::logl("Elements enqueued: ", N);
    alang::logl("Elements dequeued: ", N);
    alang::logl("Successful dequeue count: ", successful_dequeues);

    alang::logl("Queue size: ", q.size());

    it = q.iterator();
    ctr = 0;
    while (!it.done()) {
        ++ctr;
        ++it;
    }
    alang::logl("Elements in queue: ", ctr);
}