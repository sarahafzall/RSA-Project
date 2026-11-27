#include <iostream>
#include <cassert>
#include "rsa.h"
using namespace std;




int main() {


    //B4
    assert(mod_inverse(3, 7) == 5);
    assert(mod_inverse(101, 4620) == 1601);
    assert(mod_inverse(13, 2436) == 937);
    bool threw = false;
    try { mod_inverse(2, 6); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);

    //B5
    assert(is_prime(2) && is_prime(2539) && is_prime(1000003));
    assert(!is_prime(0) && !is_prime(1) && !is_prime(2537) && !is_prime(561));

    //B7
    assert(encrypt(1819, 2537, 13) == 2081);
    assert(encrypt(1415, 2537, 13) == 2182);
    assert(decrypt(981, 2537, 937) == 704);
    assert(decrypt(461, 2537, 937) == 1115);

    //B8
    assert(encrypt_text("STOP", 2537, 13) == "2081 2182");
    assert(encrypt_text("Stop!", 2537, 13) == "2081 2182");
    assert(encrypt_text("abc", 2537, 13) == "0001 0027"); // padded to ABCX
    assert(decrypt_text("0981 0461", 2537, 937) == "HELP");
    assert(decrypt_text(encrypt_text("DISCRETE", 2537, 13), 2537, 937) == "DISCRETE");



    return 0;
}