//
// Created by raknoel on 17.10.18.
//

#ifndef INF214_BANKACCOUNT_H
#define INF214_BANKACCOUNT_H


class bankAccount {
private:
    int amount = 0;
public:

    int deposit(int i) {
        this->amount += i;
        return this->amount;
    }

    int withdraw(int i) {
        if (this->amount - i < 0) throw *"Not enough money in account to withdraw " + i;
        else this->amount -= i;
        return this->amount;
    }
};


#endif //INF214_BANKACCOUNT_H
