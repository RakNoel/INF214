//
// Created by raknoel on 22.09.18.
//

#include "alang.hpp"
#include <cassert>

#ifndef INF214_NODE_H
#define INF214_NODE_H

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

#endif //INF214_NODE_H
