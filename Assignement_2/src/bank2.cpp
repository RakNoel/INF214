//
// Created by raknoel on 17.10.18.
//
#include <queue>
#include "alang.hpp"
#include "bankaccount.h"

using namespace std;


class myMonitor {
private:
    A<bankAccount> myacc;
    A<int> value;
    A<queue<int>> myqueue;
public:

    int deposit(int amount) {
        ATO value = myacc.read().deposit(amount); MIC;
        return value.read();
    }

    int withdraw(int amount) {
        ATO
                            {
                                AWAIT(myqueue.read().size() < 10)
                                A<int> ticket = rand() % 100000;
                                myqueue.read().push(ticket);
                                AWAIT(value.read() >= amount && myqueue.read().front() == ticket);
                                value = myacc.read().withdraw(amount);
                                myqueue.read().pop();
                            };
        MIC;
        return value.read();
    }
};

int main() {
}