#include <iostream>
#include "rsa.h"
using namespace std;


void trivialDiv(uint64 n, uint64& p, uint64& q) {
	while (n % p != 0) {
		p++;
	}
	q = n / p;
}

int main() {
	uint64 n = 1000036000099;
	uint64 e = 65537;
	string ciphertext = "0614157364221 0502078796304 0031583460315";

	uint64 p, q;
	p = 2;
	trivialDiv(n,p, q);

	uint64 phi = (p - 1) * (q - 1);
	uint64 privateKey = mod_inverse(e, phi);
	string final = decrypt_text(ciphertext, n, privateKey);
	cout << "\n p=> " << p << "\tq=> " << q;
	cout << "\nPrivate key: " << privateKey;
	cout << "\nDecrypted text: " << final;
	return 0;
}