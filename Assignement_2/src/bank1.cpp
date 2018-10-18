//
// Created by raknoel on 17.10.18.
//

#include "alang.hpp"

using namespace std;


class bankAccount : monitor {
private:
    int amount = 0;
    cond notBroke;
public:

    int deposit(int i) {
        SYNC;
        this->amount = this->amount + i;
        signal_all(notBroke);
        return this->amount;
    }

    int withdraw(int i) {
        SYNC;
        while (amount < i) { wait(notBroke); }
        this->amount = this->amount - i;
        signal_all(notBroke);
        return this->amount;
    }
};

int main() {
    bankAccount account;
    processes ps;

    for (int i : range(0, 10)) {

        alang::ignore(i);

        ps += [&] {
            account.withdraw(200);
        };
    }
    for (int i : range(0, 20)) {

        alang::ignore(i);

        ps += [&] {

            account.deposit(100);

        };

    }
}