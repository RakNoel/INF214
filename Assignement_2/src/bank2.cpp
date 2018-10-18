//
// Created by raknoel on 17.10.18.
//

#include "alang.hpp"

using namespace std;


class bankAccount : monitor {
private:
    int amount = 0;
    int ticket = 0;
    int next = 0;
    cond notBroke;
public:

    int deposit(int i) {
        SYNC;
        amount = amount + i;
        cout << "Deposited: " << i << " balance: " << amount << endl;
        signal_all(notBroke);
        return amount;
    }

    int withdraw(int i) {
        SYNC;
        int thisTicket = ticket++;
        cout << "Waiting with ticket: " << thisTicket << endl;
        while (amount < i || next != thisTicket) { wait(notBroke); }
        amount = amount - i;
        cout << "Withdrew: " << i << " balance: " << amount << " next: " << ++next << endl;
        signal_all(notBroke);
        return amount;
    }
};

int main() {
    bankAccount account;

    {
        processes ps;
        for (int i : range(0, 10)) {

            alang::ignore(i);

            ps += [&] {
                account.withdraw(300);
            };
        }

        for (int i : range(0, 20)) {

            alang::ignore(i);

            ps += [&] {
                account.withdraw(100);
            };
        }
        for (int i : range(0, 50)) {

            alang::ignore(i);

            ps += [&] {

                account.deposit(100);

            };

        }
    }
}