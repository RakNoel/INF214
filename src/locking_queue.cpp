//
// Created by raknoel on 17.09.18.
//

#include "alang.hpp"
#include <cassert>

using namespace std;

template<typename E>
class queue;    // forward declaration
template<typename E>
class node_iterator; //forward declaration

template<typename E>
class node {
    E data;
    A<node<E> *> next;

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
    A<node<E> *> head;
    A<node<E> *> rear;
    A<int> _size;
    mutex myLock;
public:
    queue() : head(nullptr), rear(nullptr), _size(0), myLock() {}

    bool empty() const { return _size == 0; }

    void enqueue(E d) {
        A<node<E> *> newNode = new node<E>(d, nullptr);

        while (true) {
            if (myLock.try_lock()) break;
        }

        if (rear == nullptr) {
            head = newNode;
        } else {
            rear.read()->next = newNode;
        }
        rear = newNode;
        _size = _size + 1;

        myLock.unlock();
    }

    E dequeue() {
        while (true) {
            if (myLock.try_lock()) {
                if (!empty()) break;
                else myLock.unlock();
            }
        }
        node<E> *oldHead = head;
        head = head.read()->next;
        if (head == nullptr) rear = nullptr;
        E e = oldHead->data;
        _size = _size - 1;
        myLock.unlock();
        return e;
    }

    int size() const {
        return _size.read();
    }

    node_iterator<E> iterator() {
        while (true) {
            if (myLock.try_lock()) break;
        }
        auto ret = head.read();
        myLock.unlock();

        return ret;
    }
};

const int N = 10000;

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
    assert(ctr == 2 * N);

    alang::logl("---------------");

    int successful_dequeues = 0;
    queue<int> p;
    {
        processes ps;
        ps += [&] {
            for (int i = 0; i < N; ++i) {
                p.enqueue(1);
            }
        };
        ps += [&] {
            int c = 0;

            for (int i = 0; i < N; ++i) {
                try {
                    p.dequeue();
                    ++c;
                } catch (...) {}
            }

            successful_dequeues = c;
        };
    }
    alang::logl("Elements enqueued: ", N);
    alang::logl("Elements dequeued: ", N);
    alang::logl("Successful dequeue count: ", successful_dequeues);

    alang::logl("Queue size: ", p.size()); //heh p.size()

    it = p.iterator();
    ctr = 0;
    while (!it.done()) {
        ++ctr;
        ++it;
    }
    alang::logl("Elements in queue: ", ctr);

    assert(ctr == 0);
}