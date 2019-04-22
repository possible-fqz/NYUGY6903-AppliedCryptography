
#include "shamir.h"
#include "util.h"
#include "boost/multiprecision/cpp_int.hpp"
#include "tests.h"
#include "myAES.h"
#include "myIDA.h"

using namespace boost::multiprecision;
using namespace std;


void testScheme() {
	cout << "Test Scheme" << endl;
	string plaintext = "Here's a little lesson in trickery";
	cout << "plaintext: " << plaintext << endl;
	int numHolders = 6;
	int minHolders = 3;
	vector<Holder> holders;
	for (size_t i = 0; i < 6; i++) {
		Holder h;
		holders.push_back(h);
	}
	encrypt(plaintext, holders, minHolders);
	
	string decryptedText;
	decrypt(decryptedText, minHolders, holders);
	
	vector<Holder> combinedHolders = { holders[0], holders[1], holders[2] };
	decrypt(decryptedText, minHolders, combinedHolders);
	cout << "decryptedtext: " << decryptedText;
	cout << endl << endl << endl;
}


void testShamir() {
	cout << "Test Shamir's" << endl;
	int min = 3;
	int numShares = 6;
	cpp_int secret;
	vector<tuple<cpp_int, cpp_int>> shares;
	shareSecret(min, numShares, secret, shares);
	
	cout << "Secret: " << secret << endl;
	cout << "Shares: " << endl;
	for (auto& x : shares) {
		cout << get<0>(x) << ", " << get<1>(x) << endl;
	}
	vector<tuple<cpp_int, cpp_int>> recoveringShares;
	vector<int> sharesInd = { 0, 3, 5, 4 };
	for (int& n : sharesInd) {
		recoveringShares.push_back(shares[n]);
	}
	cpp_int recoveredSecret;
	recoverSecretShell(min, recoveringShares, recoveredSecret);
	cout << endl << "Recovered: " << recoveredSecret;
	cout << endl << endl << endl;
}

void testIDA() {
	cout << "Test IDA" << endl;
	vector<string> pieces;
	int min = 3;
	int nShares = 6;
	string message = "This is a secret";
	disperse(min, nShares, message, pieces);
	cout << "message: " << message << endl;
	string recoveredText;
	vector<string> joinedPieces = { pieces[0], pieces[3], pieces[4] };
	recover(min, joinedPieces, recoveredText);
	cout << "recoveredText: " << recoveredText << endl << endl << endl;
}

void testAES() {
	cout << "Test AES" << endl;
	string plaintext = "We are number one, now listen closely, here's a little lesson in trickery";
	string key = "villain number one";
	cout << "plaintext: " << plaintext << endl;
	cout << "key: " << key << endl;
	string ciphertext = aesEncrypt(key, plaintext);
	cout << "ciphertext: " << ciphertext << endl;
	string decryptedText = aesDecrypt(key, ciphertext);
	cout << "decryptedtext: " << decryptedText;
	cout << endl << endl << endl;
}