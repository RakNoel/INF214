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
    A<int> ticket;
public:

    int deposit(int amount) {
        ATO value = myacc.read().deposit(amount); MIC;
        return value.read();
    }

    int withdraw(int amount) {
        ATO
                            {
                                A<int> myTicket = ticket;
                                ticket = ticket + 1;

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