//
// Created by raknoel on 17.10.18.
//

#include "alang.hpp"
#include <cassert>
#include <iostream>
#include <chrono>


using namespace std;

int gcd(int n, int m) {
    int x = n, y = m;

    while (x != y) {
        CO(
                [&] { if (x > y) x = x - y; },
                [&] { if (x < y) y = y - x; }
        );
    }

    assert (x == y); //TEST! I LOVE TEEEEEESTS <3 <3 <3
    return x;
}

int main() {
    alang::logl(gcd(2, 3));
    alang::logl(gcd(25235, 2345));
    alang::logl(gcd(310, 150));


    //MOAR TESTS!
    for (int i = 0; i < 100; i++) {
        int x = rand() % 1000000, y = rand() % 1000000;

        int def = gcd(x, y);

        assert(gcd(x, x) == x);
        assert(gcd(y, y) == y);
        assert(def == gcd(y, x));
        if (x > y) assert(def == gcd(x - y, y)); else assert(def == gcd(y - x, x));
        assert(def <= x && def <= y);

    }

    cout << "Tests complete!" << endl;
}