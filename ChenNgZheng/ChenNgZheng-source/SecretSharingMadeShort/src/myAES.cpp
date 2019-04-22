
#define uint8_t byte
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <osrng.h>
#include "myAES.h"
#include "util.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include <cryptlib.h>
using CryptoPP::Exception;

#include <hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <des.h>
using CryptoPP::DES_EDE2;

#include <modes.h>
using CryptoPP::CBC_Mode;

#include <secblock.h>
using CryptoPP::SecByteBlock;
#include <iostream>
#include <string>
#include <modes.h>
#include <aes.h>
#include <filters.h>



string aesEncrypt(string key, string plaintext) {
	std::string iv = "aaaaaaaaaaaaaaaa";
	std::string ciphertext;
	
	int keyLen = roundPower2(key.size());
	CryptoPP::AES::Encryption aesEncryption((byte *)key.c_str(), 32);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length() + 1);
	stfEncryptor.MessageEnd();
	return ciphertext;
}

string aesDecrypt(string key, string ciphertext) {
	std::string decryptedtext;
	std::string iv = "aaaaaaaaaaaaaaaa";

	CryptoPP::AES::Decryption aesDecryption((byte *)key.c_str(), 32);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size());
	stfDecryptor.MessageEnd();
	return decryptedtext;
}

