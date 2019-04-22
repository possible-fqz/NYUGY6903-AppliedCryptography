#pragma once

#include <NTL/ZZX.h>
#include <vector>

NTL::ZZ mod(NTL::ZZ n, NTL::ZZ M);
NTL::ZZX constructPolynomial(const std::vector<long>& terms);
void modPolynomial(NTL::ZZX& poly, NTL::ZZ num, bool center);