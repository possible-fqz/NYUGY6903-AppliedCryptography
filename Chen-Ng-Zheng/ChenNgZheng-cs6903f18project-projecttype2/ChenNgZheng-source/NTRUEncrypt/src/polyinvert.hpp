#pragma once

#include <NTL/ZZX.h>

NTL::ZZX invertPolynomialPrime(NTL::ZZX a, NTL::ZZ prime, long N);
NTL::ZZX invertPolynomialPrimePower(NTL::ZZX a, NTL::ZZ prime, long power, long N);