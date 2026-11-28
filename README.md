# RSA-Project
## About
This project implements the RSA (Rivest–Shamir–Adleman) public-key cryptosystem in C++17.

It demonstrates RSA key generation, encryption, decryption, modular arithmetic, and basic cryptanalysis through a factorization attack.

## Features

- Modular multiplication (`mul_mod`)
- Modular exponentiation (`mod_exp`)
- Greatest Common Divisor (`gcd`)
- Extended Euclidean Algorithm (`extended_gcd`)
- Modular multiplicative inverse (`mod_inverse`)
- Prime number validation (`is_prime`)
- RSA key generation (`generate_keys`)
- RSA encryption and decryption (`encrypt`, `decrypt`)
- Text encryption and decryption (`encrypt_text`, `decrypt_text`)
- Block-based message encoding
- Basic RSA key-breaking using trial division (`break_key`)

## Files

| File | Description |
|---|---|
| `rsa.h` | Function declarations and type definitions |
| `rsa.cpp` | RSA implementation |
| `demo.cpp` |RSA demonstration |
| `test_rsa.cpp` | Unit tests for RSA functions |
| `break_key.cpp` | Demonstrates breaking an RSA key|

## Compilation and Execution
### 1. Compile and run the test suite
Compile:

```bash
g++ -std=c++17 -O2 rsa.cpp test_rsa.cpp -o test_rsa
```
Run:

```bash
./test_rsa
```

**Expected output:**

```Exceptions raised at assert calls.
```
The test program uses assertions. If all tests pass, it terminates successfully without printing anything. If an assertion fails, the program reports the failed assertion.

### 2. Compile and run the RSA demonstration
Compile:

```bash
g++ -std=c++17 -O2 rsa.cpp demo.cpp -o demo
```

Run:

```bash
./demo
```

The program prompts the user to enter:
- Two prime numbers (`p` and `q`)
- A valid public exponent (`e`)
- A message to encrypt
- It then generates the public and private keys, displays the block size, encrypts the message, and decrypts the resulting ciphertext.

### 3. Compile and run break_key
Compile:

```bash
g++ -std=c++17 -O2 rsa.cpp break_key.cpp -o break_key
```

Run:

```bash
./break_key
```
**Expected output:**
```text
 p=> 1000003    q=> 1000033
Private key: 983264276609
Decrypted text: NUMBERSHEORYISFUNX
```
The `break_key` program demonstrates a basic RSA attack using trial division.

Process:
1. Takes the public modulus `n` and public exponent `e`.
2. Uses trial division to find the prime factors `p` and `q`.
3. Calculates Euler's totient:

   φ(n) = (p - 1)(q - 1)

4. Computes the private key using the modular multiplicative inverse of `e` modulo φ(n).
5. Uses the recovered private key to decrypt the ciphertext.

The decrypted message is `NUMBERSHEORYISFUNX` (final `X` is padding added during text encryption).
