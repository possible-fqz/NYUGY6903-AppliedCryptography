#include "benchmark.h"


void benchmark_Shamir(size_t t, size_t n) {
	t = 4;
	//keyGen & split
	float nIters = 100.000000000000000;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 1; i < nIters; i++) {
		SSSS secretShare = SSSS();
		tuple<cpp_int, vector<tuple<cpp_int, cpp_int>>> secret_shares = secretShare.makeRandomShares(4, n);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	SSSS secretShare = SSSS();
	tuple<cpp_int, vector<tuple<cpp_int, cpp_int>>> secret_shares = secretShare.makeRandomShares(4, n);
	cpp_int secret = get<0>(secret_shares);
	cout << "numDigits: " << secret.str().size() << endl;
	cout << "t: " << t << ", n: " << n << endl;
	vector<tuple<cpp_int, cpp_int>> shares = get<1>(secret_shares);

	//key recover
	vector<tuple<cpp_int, cpp_int>> recoveringShares;
	vector<int> sharesInd = { 0, 3, 5, 4 };
	for (int& n : sharesInd) {
		recoveringShares.push_back(shares[n]);
	}
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (int i = 1; i < nIters; i++) {
		cpp_int recoveredSecret = secretShare.recoverSecret(recoveringShares);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	auto durationKey = duration_cast<microseconds>(t2 - t1).count();
	auto durationRecover = duration_cast<microseconds>(t4 - t3).count();
	cout << "keyGen runtime: " << durationKey / nIters << "microsec" << endl;
	cout << "keyRecover runtime: " << durationRecover / nIters << "microsec" << endl;
}


void benchmark_AES(std::string key, std::string plaintext) {
	
	//string plaintext = "We are number one, now listen closely, here's a little lesson in trickery";
	//string key = "villain number one";
	float nIters = 100.000000000000000;
	//encryption
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < nIters; i++) {
		string ciphertext = aesEncrypt(key, plaintext);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	string ciphertext = aesEncrypt(key, plaintext);

	//decryption
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (int i = 0; i < nIters; i++) {
		string decryptedText = aesDecrypt(key, ciphertext);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	auto durationEnc = duration_cast<microseconds>(t2 - t1).count();
	auto durationDec = duration_cast<microseconds>(t4 - t3).count();
	cout << "length of key: " << key.length() << ", length of plaintext: " << plaintext.length() << endl;
	cout << "durationEnc runtime: " << durationEnc / nIters << "microsec" << endl;
	cout << "durationDec runtime: " << durationDec / nIters << "microsec" << endl;
};


void benchmark_IDA(int threshold, int nShares, std::string ciphertext) {
	vector<string> pieces;
	//int min = 3;
	//int nShares = 6;
	//string message = "This is a secret";
	string message = ciphertext;
	int min = threshold;

	//cipherSplit
	int nIters = 100;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int i = 0; i < nIters; i++) {
		disperse(min, nShares, message, pieces);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	//cipherRecover
	string recoveredText;
	vector<string> joinedPieces = { pieces[0], pieces[3], pieces[4] };
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	for (int i = 0; i < nIters; i++) {
		recover(min, joinedPieces, recoveredText);
	}
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	int lengthCipher = ciphertext.length();
	auto durationCipherSplit = duration_cast<microseconds>(t2 - t1).count();
	auto durationCipherRecover = duration_cast<microseconds>(t4 - t3).count();
	cout << "length of cipher: " << lengthCipher << "threshold: " << threshold << ", number of shares: " << nShares <<  endl;
	cout << "durationCipherSplit runtime: " << durationCipherSplit / nIters << "microsec" << endl;
	cout << "durationCipherRecover runtime: " << durationCipherRecover / nIters << "microsec" << endl;
}