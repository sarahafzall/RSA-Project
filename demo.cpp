#include <iostream>
#include <string>
#include "rsa.h"
using namespace std;

void demoEncrypt(const std::string& text, uint64 n, uint64 e) { // B8
	int k = block_size(n);
	string newText = "";
	for (int i = 0;i < text.length();i++) {
		if (isalpha(text[i])) {
			newText += toupper(text[i]);
		}
	}
	while (newText.length() % k != 0) {     //while it is not a multiple of k
		newText.append("X");
	}

	//split into k-groups
	int start = 0;  int end = 0;
	uint64 M = 0;
	uint64 ans;
	string ansSTR;
	for (int i = 0;i < newText.length();i++) {
		M = 0;
		if (end - start == k) {
			for (int j = start;j < end;j++) {
				M = (M * 100) + (newText[j] - 'A');
			}
			cout << M << " ";
			start = end;
		}
		else {
			end++;
		}
	}

}


int main() {
	uint64 p, q, e, n,d;
	while (true) {
		cout << "\nEnter p: ";
		cin >> p;
		cout << "\nEnter q: ";
		cin >> q;
		cout << "\nEnter e: ";
		cin >> e;
		try {
			generate_keys(p, q, e, n, d);
			break;
		}
		catch (const std::invalid_argument& ex) {
			cout << ex.what() << endl;
		}
	}

	cout << "\nPublic Key: n=> " << n << ", e=> " << e;
	cout << "\nPrivate Key: d=> " << d;
	cout << "\nBlock Size: k=> " << block_size(n);


	cout << "\nMessage: ";
	string message;
	cin.ignore();
	getline(cin, message);
	string cleaned = "";
	cout << "\nCleaned: ";
	for (int i = 0;i < message.length();i++) {
		if (isalpha(message[i])) {
			cleaned += toupper(message[i]);
		}
	}
	cout << cleaned;
	cout << "\nPlaintext: ";
	demoEncrypt(cleaned, n, e);
	string cipher = encrypt_text(message, n, e);
	cout << "\nCipher Text: " << cipher;
	cout << "\nDecrypted: " << decrypt_text(cipher, n, d);

	return 0;
}
