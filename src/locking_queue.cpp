//
// Created by raknoel on 17.09.18.
//

#include "alang.hpp"
#include "node.h"
#include <cassert>

using namespace std;

template<typename E>
class queue {
    A<node<E> *> head;
    A<node<E> *> rear;
    A<int> _size;
    semaphore _s = 1;
public:
    queue() : head(nullptr), rear(nullptr), _size(0) {}

    bool empty() const { return _size == 0; }

    void enqueue(E d) {
        A<node<E> *> newNode = new node<E>(d, nullptr);
        _s.P();

        if (rear == nullptr) {
            head = newNode;
        } else {
            rear.read()->next = newNode;
        }
        rear = newNode;
        _size = _size + 1;

        _s.V();
    }

    E dequeue() {
        while (true) {
            _s.P();
            if (!empty()) break;
            else _s.V();
        }
        node<E> *oldHead = head;
        head = head.read()->next;
        if (head == nullptr) rear = nullptr;
        E e = oldHead->data;
        _size = _size - 1;
        _s.V();
        return e;
    }

    int size() const {
        return _size.read();
    }

    node_iterator<E> iterator() {
        _s.P();
        auto ret = head.read();
        _s.V();
        return ret;
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