#define _CRT_SECURE_NO_WARNINGS
#include "shamir.h"
#include "tests.h"
#include "myIDA.h"
#include <stdio.h>
#include <stdlib.h>
#include "boost/algorithm/hex.hpp"
using namespace boost::multiprecision;
using namespace boost::random;
using namespace std;




int main() {
	testShamir();
	testAES();
	testIDA();
	testScheme();

	system("pause");

}
