//
// Created by raknoel on 17.10.18.
//

#include "alang.hpp"
#include "bankaccount.h"

using namespace std;


class myMonitor {
private:
    A<bankAccount> myacc;
    A<int> value;
public:

    int deposit(int amount) {
        ATO value = myacc.read().deposit(amount); MIC;
        return value.read();
    }

    int withdraw(int amount) {
        ATO
                            {
                                AWAIT(value.read() >= amount);
                                value = myacc.read().withdraw(amount);
                            };
        MIC;
        return value.read();
    }
};

int main() {
}