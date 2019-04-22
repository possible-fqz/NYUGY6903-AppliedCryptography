#define _CRT_SECURE_NO_WARNINGS
#include "shamir.h"
using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;


cpp_int SSSS::newDiv(cpp_int a, cpp_int b) {
	cpp_int res = a / b;
	cpp_int rem = a % b;
	cpp_int corr = (rem != 0 && ((rem < 0) != (b < 0)));
	return res - corr;
}


cpp_int SSSS::newMod(cpp_int a, cpp_int b) {
	cpp_int rem = a % b;
	if (rem != 0 && ((rem < 0) != (b < 0))) { 
		rem += b;
	}
	return rem;
}


cpp_int SSSS::evalAt(vector<cpp_int> poly, cpp_int x) {
	cpp_int accum = 0;
	for (vector<cpp_int>::reverse_iterator iter = poly.rbegin();
		iter != poly.rend(); iter++) {
		accum *= x;
		accum += *iter;
		accum %= prime;
	}
	return accum;
}


tuple<cpp_int, vector<tuple<cpp_int, cpp_int>>> SSSS::makeRandomShares(cpp_int minimum, cpp_int shares) {
	typedef boost::random::independent_bits_engine<boost::random::mt19937, 256, cpp_int> generator_type;
	generator_type gen;

	vector<cpp_int> poly;
	vector<tuple<cpp_int,cpp_int>> points;
	for (size_t i = 0; i < minimum; i++) {
		cpp_int x = gen();
		cpp_int randInt = newMod(x,prime);
		poly.push_back(randInt);

	}
	for (size_t i = 1; i < shares + 1; i++) {
		points.push_back(tuple<cpp_int,cpp_int>(i, evalAt(poly, i)));
	}
	return tuple<cpp_int, vector<tuple<cpp_int,cpp_int>>>(poly[0], points);
}


cpp_int SSSS::extendedGCD(cpp_int a, cpp_int b) {
	cpp_int x = 0;
	cpp_int last_x = 1;
	cpp_int y = 1;
	cpp_int last_y = 0;
	while (b != 0) {
		cpp_int quot = newDiv(a, b);
		cpp_int temp = a;
		a = b;
		b =newMod(temp,b);
		temp = x;
		x = last_x - quot * x;
		last_x = temp;
		temp = y;
		y = last_y - quot * y;
		last_y = temp;
	}
	return last_x;
}


cpp_int SSSS::divideMod(cpp_int num, cpp_int den) {
	
	cpp_int inv = extendedGCD(den, prime);
	return num * inv;
}


cpp_int SSSS::lagrangeInterpolate(cpp_int x, vector<cpp_int> x_s, vector<cpp_int> y_s) {
	vector<cpp_int> nums;
	vector<cpp_int> dens;
	for (size_t i = 0; i < x_s.size(); i++) {
		vector<cpp_int> other = x_s;
		cpp_int curr = other[i];
		other.erase(other.begin() + i);
		cpp_int accumNums = 1;
		cpp_int accumDens = 1;
		for (cpp_int& o : other) {
			accumNums *= (x - o);
			accumDens *= (curr - o);
		}
		nums.push_back(accumNums);
		dens.push_back(accumDens);
	}
	cpp_int den = 1;
	for (cpp_int& d : dens) {
		den *= d;
	}
	cpp_int num = 0;
	for (size_t i = 0; i < x_s.size(); i++) {
		num += divideMod(nums[i] * den * newMod(y_s[i],prime), dens[i]);
	}
	return newMod((divideMod(num, den) + prime), prime);
}


cpp_int SSSS::recoverSecret(vector<tuple<cpp_int,cpp_int>> shares) {
	vector<cpp_int> x_s;
	vector<cpp_int> y_s;
	for (size_t i = 0; i < shares.size(); i++) {
		x_s.push_back(get<0>(shares[i]));
		y_s.push_back(get<1>(shares[i]));
	}
	return lagrangeInterpolate(0, x_s, y_s);
}



void shareSecret(int min, int numShares, cpp_int& secret, vector<tuple<cpp_int, cpp_int>>& shares) {
	SSSS secretShare = SSSS();
	tuple<cpp_int, vector<tuple<cpp_int, cpp_int>>> secret_shares = secretShare.makeRandomShares(min, numShares);
	secret = get<0>(secret_shares);
	shares = get<1>(secret_shares);
}

void recoverSecretShell(int min, vector<tuple<cpp_int, cpp_int>> recoveringShares, cpp_int& recoveredSecret) {
	SSSS secretShare = SSSS();
	recoveredSecret = secretShare.recoverSecret(recoveringShares);
}