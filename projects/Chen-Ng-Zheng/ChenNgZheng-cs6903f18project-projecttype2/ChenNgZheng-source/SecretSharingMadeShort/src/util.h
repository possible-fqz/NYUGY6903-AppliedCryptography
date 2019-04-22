#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <tuple>


struct Holder {
	std::tuple<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> share;
	std::string piece;
};

std::vector<Holder> makeHolders(int num);

std::string longHex(boost::multiprecision::cpp_int d);


int roundPower2(int x);


void encrypt(std::string plaintext, std::vector<Holder>& holders, int minimum);

void decrypt(std::string& decryptedText, int min, std::vector<Holder> holders);