#include "NTRU.hpp"

#include <iostream>
#include <NTL/ZZX.h>
#include <random>
#include <algorithm>

#include "polyinvert.hpp"
#include "util.hpp"

bool verifyNTRUParameters(NTRUParameters params) {
    return params.N >= 0 && params.p >= 0 && params.q >= 0;
}

//lower/upper inclusive
NTL::ZZX generateRandomPolynomial(long polysize, NTL::ZZ lower, NTL::ZZ upper) {
    NTL::ZZX poly;
    poly.SetLength(polysize);

    //Doesn't matter what direction to go in, as long as we generate random coefficients
    for(long i = 0; i < polysize; i++) {
        NTL::ZZ coeff = NTL::RandomBnd(NTL::conv<NTL::ZZ>(upper - lower + 1)) + NTL::ZZ(lower);
        NTL::SetCoeff(poly, i, coeff);
    }

    poly.normalize();
    return poly;
}

NTL::ZZX generateSmallPolynomial(long polysize, long numpos, long numneg) {
    std::vector<long> coeffs(polysize, 0);

    std::fill(coeffs.begin(), coeffs.begin() + numpos, 1);
    std::fill(coeffs.begin() + numpos, coeffs.begin() + numpos + numneg, -1);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(coeffs.begin(), coeffs.end(), mt);

    return constructPolynomial(coeffs);
}

NTL::ZZX generatePublicKey_internal(NTRUParameters params, NTL::ZZX f, NTL::ZZX g, NTL::ZZX& fp) {
    NTL::ZZX ringpoly;
    NTL::SetCoeff(ringpoly, params.N, 1);
    NTL::SetCoeff(ringpoly, 0, -1);

    NTL::ZZX fq;

    fp = invertPolynomialPrime(f, params.p, params.N);
    if(NTL::deg(fp) < 0)
        return NTL::ZZX();

    if(params.q_prime == 0)
        fq = invertPolynomialPrime(f, params.q, params.N);
    else
        fq = invertPolynomialPrimePower(f, params.q_prime, params.q_power, params.N);
    if(NTL::deg(fq) < 0)
        return NTL::ZZX();

    NTL::ZZX h = params.p * NTL::MulMod(fq, g, ringpoly);

    modPolynomial(h, params.q, true);
    return h;
}

NTL::ZZX encrypt_internal(NTRUParameters params, NTL::ZZX publickey, NTL::ZZX message, NTL::ZZX r) {
    NTL::ZZX modpoly;
    NTL::SetCoeff(modpoly, params.N, 1);
    NTL::SetCoeff(modpoly, 0, -1);

    NTL::ZZX e = NTL::MulMod(r, publickey, modpoly) + message;
    modPolynomial(e, params.q, false);

    return e;
}

NTL::ZZX encrypt(NTRUParameters params, NTL::ZZX publickey, NTL::ZZX message) {
    NTL::ZZX r = generateSmallPolynomial(params.N, params.dg, params.dg);

    return encrypt_internal(params, publickey, message, r);
}

NTL::ZZX decrypt(NTRUParameters params, NTL::ZZX encrypted, NTL::ZZX fp, NTL::ZZX f) {
    NTL::ZZX modpoly;
    NTL::SetCoeff(modpoly, params.N, 1);
    NTL::SetCoeff(modpoly, 0, -1);

    NTL::ZZX a = NTL::MulMod(f, encrypted, modpoly);
    modPolynomial(a, params.q, true);
    modPolynomial(a, params.p, true);

    NTL::ZZX c = NTL::MulMod(fp, a, modpoly);
    modPolynomial(c, params.p, true);

    return c;
}