#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <tuple>



class SSSS {
public:
	std::tuple<boost::multiprecision::cpp_int, std::vector<std::tuple<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>>> makeRandomShares(boost::multiprecision::cpp_int minimum, boost::multiprecision::cpp_int shares);
	boost::multiprecision::cpp_int recoverSecret(std::vector<std::tuple<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>> shares);
	
private:
	boost::multiprecision::cpp_int evalAt(std::vector<boost::multiprecision::cpp_int> poly, boost::multiprecision::cpp_int x);
	boost::multiprecision::cpp_int extendedGCD(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b);
	boost::multiprecision::cpp_int divideMod(boost::multiprecision::cpp_int num, boost::multiprecision::cpp_int den);
	boost::multiprecision::cpp_int lagrangeInterpolate(boost::multiprecision::cpp_int x, std::vector<boost::multiprecision::cpp_int> x_s, std::vector<boost::multiprecision::cpp_int> y_s);
	boost::multiprecision::cpp_int newDiv(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b);
	boost::multiprecision::cpp_int newMod(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b);
	boost::multiprecision::cpp_int prime = boost::multiprecision::pow(boost::multiprecision::cpp_int(2),127)-1;
};

void shareSecret(int min, int numShares, boost::multiprecision::cpp_int& secret, std::vector<std::tuple<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>>& shares);
void recoverSecretShell(int min, std::vector<std::tuple<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int>> recoveringShares, boost::multiprecision::cpp_int& recoveredSecret);