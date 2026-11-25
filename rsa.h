#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

typedef unsigned long long uint64; // 64 bits: 0 to about 1.8 x 10^19

uint64 mul_mod(uint64 a, uint64 b, uint64 m); // B0
uint64 mod_exp(uint64 b, uint64 n, uint64 m); // B1
uint64 gcd(uint64 a, uint64 b); // B2
long long extended_gcd(long long a, long long b,
long long &s, long long &t); // B3
uint64 mod_inverse(uint64 a, uint64 m); // B4
bool is_prime(uint64 n); // B5
void generate_keys(uint64 p, uint64 q, uint64 e,
uint64 &n, uint64 &d); // B6
uint64 encrypt(uint64 M, uint64 n, uint64 e); // B7
uint64 decrypt(uint64 C, uint64 n, uint64 d); // B7
int block_size(uint64 n);
string encrypt_text(const std::string &text, uint64 n, uint64 e); // B8
string decrypt_text(const std::string &blocks, uint64 n, uint64 d); // B8
