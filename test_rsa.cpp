#include <iostream>
#include <cassert>
#include "rsa.h"
using namespace std;




int main() {

    // B0 
    assert(mul_mod(7, 8, 5) == 1);
    assert(mul_mod(0, 99, 7) == 0);
    assert(mul_mod(123456789012ULL, 987654321098ULL, 1000036000099ULL) ==
    813538246183ULL);

    // B1 
    assert(mod_exp(3, 644, 645) == 36);
    assert(mod_exp(1819, 13, 2537) == 2081);
    assert(mod_exp(5, 0, 7) == 1);
    assert(mod_exp(2, 1000000000ULL, 1000000007ULL) == 140625001ULL);
  
    //B2
    assert(gcd(252, 198) == 18);
    assert(gcd(13, 2436) == 1);
    assert(gcd(17, 0) == 17);
    
    // B3 
    long long s, t;
    long long g = extended_gcd(252, 198, s, t);
    assert(g == 18 && s == 4 && t == -5); // 18 = 4*252 - 5*198
    g = extended_gcd(4620, 101, s, t);
    assert(g == 1 && s == -35 && t == 1601);
    
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

    // B6 
    uint64 n, d;
    generate_keys(43, 59, 13, n, d);
    assert(n == 2537 && d == 937);
    // Each of these calls must throw std::invalid_argument:
     threw = false ; 
    try { generate_keys(42, 59, 13, n, d);} // 42 is not prime
    catch (const std ::invalid_argument & ){
        threw = true ; 
    }
    assert(threw);

    threw = false ;
    try {generate_keys(43, 43, 13, n, d); }// p == q
    catch (const std ::invalid_argument & ){
        threw = true ; 
    }
    assert(threw);

    threw = false ; 
    try { generate_keys(43, 59, 2, n, d);} // gcd(2, 2436) = 2
    catch (const std ::invalid_argument & ){
        threw = true ; 
    }
    assert(threw); 
    
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