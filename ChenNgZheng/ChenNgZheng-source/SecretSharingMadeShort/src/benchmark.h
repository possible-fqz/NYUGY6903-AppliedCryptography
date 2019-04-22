#pragma once

#include "myAES.h"
#include "shamir.h"
#include "tests.h"
#include "util.h"

#include <iostream>
#include <chrono>
#include <cstring>

#include "boost/multiprecision/cpp_int.hpp"
#include "cryptlib.h"
#include "ida.h"
#include "hex.h"
#include "filters.h"
#include "channels.h"
#include "files.h"
#include <fstream>
#include <iostream>
#include <filesystem>


using namespace std;
//using namespace cryptoPP;
using namespace boost::multiprecision;
using namespace std::chrono;

void benchmark_Shamir(size_t t, size_t n);

void benchmark_AES(std::string key, std::string plaintext);

void benchmark_IDA(int threshold, int nShares, std::string ciphertext);

/*
//Shamir generates a private key
void benchmark_keygen(size_t t, size_t n); //given threshold t and number of secret keys n

//Shamir splits up the private key into nParts
void benchmark_keySplit();

//AES encrypts using the private key to create a ciphertext
void benchmark_encryption(std::string key, std::string plaintext);

//IDA breaks up ciphertext into fragments
void benchmark_cipherSplit();

//IDA can recover the original ciphertext if provided enough fragments
void benchmark_cipherRecover();

//Shamir can recover the original key given the key parts
void benchmark_keyRecover();

//AES can decrypt when provided the private key and ciphertext
void benchmark_decryption(std::string key, std::string ciphertext);
*/