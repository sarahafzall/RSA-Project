#include <string>
#include <iostream>
#include <stdexcept>
#include "rsa.h"
using namespace std;

typedef unsigned long long uint64; // 64 bits: 0 to about 1.8 x 10^19

uint64 mul_mod(uint64 a, uint64 b, uint64 m); // B0
uint64 mod_exp(uint64 b, uint64 n, uint64 m); // B1
uint64 gcd(uint64 a, uint64 b); // B2
long long extended_gcd(long long a, long long b, long long& s, long long& t); // B3



uint64 mod_inverse(uint64 a, uint64 m) { // B4
    long long s, t;
    if (extended_gcd(a, m, s, t) != 1) {
        throw std::invalid_argument("no inverse");
    }
    //Otherwise s·a ≡ 1 (mod m)
    long long r = s % (long long)m;
    if (r < 0) {
        r += m;
    }
    return r;
}
bool is_prime(uint64 n) { // B5
    if (n < 2) {
        return false;
    }
    for (int d = 2; d * d <= n;d++) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;

}


void generate_keys(uint64 p, uint64 q, uint64 e, uint64& n, uint64& d); // B6


uint64 encrypt(uint64 M, uint64 n, uint64 e) { // B7
    if (M >= n) {
        throw invalid_argument("Invalid parameters");
    }
    return mod_exp(M, e,n);
}
uint64 decrypt(uint64 C, uint64 n, uint64 d) { // B7
    if (C >= n) {
        throw invalid_argument("Invalid parameters");
    }
    return mod_exp(C, d, n);
}


int block_size(uint64 n) {
    if (n <= 25) {
        throw invalid_argument("ERROR: you crazy?");
    }
    uint64 z = 25;     //z = z·100 + 25
    int k = 0;
    while (z < n) {
        k++;
        z = (z * 100) + 25;
    }
    return k;
}
string encrypt_text(const std::string& text, uint64 n, uint64 e) { // B8
    int k = block_size(n);
    string newText = "";
    for (int i = 0;i < text.length();i++) {
        if (isalpha(text[i])) {
            newText+=toupper(text[i]);
        }
    }
    while (newText.length() % k != 0) {     //while it is not a multiple of k
        newText.append("X");
    }

    //split into k-groups
    int start = 0;  int end = 0;
    uint64 M = 0;
    string ciphertext = "";
    uint64 ans;
    string ansSTR;
    for (int i = 0;i < newText.length();i++) {
        M = 0;
        if (end-start == k) {
            for (int j = start;j < end;j++) {
                M = (M * 100) + (newText[j] - 'A');
            }
            ans = encrypt(M, n, e);
            ansSTR = to_string(ans);
            if (ansSTR.length() < to_string(n).length()) {   //do we need to add any zeroes?
                ansSTR.insert(0, to_string(n).length() - ansSTR.length(), '0');
            }
            ciphertext += ansSTR;
            if (ciphertext.length() > 0) {
                ciphertext += " ";
            }
            start = end;
        }
        else {
            end++;
        }
    }
    return ciphertext;
}
string decrypt_text(const std::string& blocks, uint64 n, uint64 d) { // B8
    uint64 num = 0;
    int k = block_size(n);
    string newtext = "";
    uint64 M;
    for (int i = 0; i < blocks.length(); i++) {
        if (blocks[i] == ' ') { // number complete
            M = decrypt(num, n, d);
            string block_chars(k, 'A');
            for (int j = k - 1; j >= 0; j--) {
                uint64 val = M % 100;
                if (val > 25) {
                    throw invalid_argument("the key is wrong");
                }
                block_chars[j] = static_cast<char>('A' + val);
                M = M / 100;
            }
            if (M != 0) {
                throw invalid_argument("the key is wrong");
            }
            newtext += block_chars;
            num = 0;
        }
        else {
            num = (num * 10) + (blocks[i] - '0');
        }
    }
    // processing last block
    if (!blocks.empty() && blocks.back() != ' ') {
        M = decrypt(num, n, d);
        string block_chars(k, 'A');
        for (int j = k - 1; j >= 0; j--) {
            uint64 val = M % 100;
            if (val > 25) {
                throw invalid_argument("the key is wrong");
            }
            block_chars[j] = static_cast<char>('A' + val);
            M = M / 100;
        }
        newtext += block_chars;
    }
    return newtext;
}