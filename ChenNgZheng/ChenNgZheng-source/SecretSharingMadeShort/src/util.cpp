#define _CRT_SECURE_NO_WARNINGS
#include "boost/algorithm/hex.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "util.h"
#include "shamir.h"
#include "myAES.h"
#include "myIDA.h"

using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;




struct Holder;

vector<Holder> makeHolders(int num) {
	vector<Holder> holders;
	for (size_t i = 0; i < num; i++) {
		Holder newHolder;
		holders.push_back(newHolder);
	}
	return holders;
}

string longHex(boost::multiprecision::cpp_int d) {
	stringstream ss;
	ss << hex << d;
	string s(ss.str());
	return s;
}

int roundPower2(int x) {
	int power = 1;
	while (power < x) {
		power *= 2;
	}
	return power;
}



void encrypt(string plaintext, vector<Holder>& holders, int minimum) {
	//shamir
	cpp_int secret;
	vector<tuple<cpp_int, cpp_int>> shares;
	shareSecret(minimum, holders.size(), secret, shares);
	for (auto& x : shares) {
		
	}
	string secreth = longHex(secret);

	

	//AES
	string ciphertext = aesEncrypt(secreth, plaintext);

	//IDA
	vector<string> pieces;
	disperse(minimum, holders.size(), ciphertext, pieces);

	for (size_t i = 0; i < holders.size(); i++) {
		holders[i].share = shares[i];
		holders[i].piece = pieces[i];
	}
	

}

void decrypt(string& decryptedText, int min, vector<Holder> holders) {
	vector<tuple<cpp_int, cpp_int>> shares;
	vector<string> pieces;
	for (Holder& h : holders) {
		shares.push_back(h.share);
		pieces.push_back(h.piece);
	}

	string recoveredText;
	recover(min, pieces, recoveredText);

	cpp_int recoveredSecret;
	recoverSecretShell(min, shares, recoveredSecret);

	string key = longHex(recoveredSecret);

	decryptedText = aesDecrypt(key, recoveredText);
}