#pragma once

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/ZZ_pEX.h>

struct NTRUParameters {
    NTRUParameters(long aN, NTL::ZZ ap, NTL::ZZ q_pr, long q_po, long adf, long adg)
        : N(aN), p(ap), df(adf), dg(adg), q(NTL::power(q_pr, q_po)), q_prime(q_pr), q_power(q_po)
    {}

    NTRUParameters(long aN, NTL::ZZ ap, NTL::ZZ aq, long adf, long adg)
        : N(aN), p(ap), df(adf), dg(adg), q(aq), q_prime(0), q_power(0)
    {}

    long N;
    NTL::ZZ p;

    long df;
    long dg;

    NTL::ZZ q;
    NTL::ZZ q_prime;
    long q_power;
};

bool verifyNTRUParameters(NTRUParameters params);
NTL::ZZX generateRandomPolynomial(long polysize, NTL::ZZ lower, NTL::ZZ upper);
NTL::ZZX generateSmallPolynomial(long polysize, long numpos, long numneg);

NTL::ZZX generatePublicKey_internal(NTRUParameters params, NTL::ZZX f, NTL::ZZX g, NTL::ZZX& fp);

NTL::ZZX encrypt_internal(NTRUParameters params, NTL::ZZX publickey, NTL::ZZX message, NTL::ZZX r);
NTL::ZZX encrypt(NTRUParameters params, NTL::ZZX publickey, NTL::ZZX message);

NTL::ZZX decrypt(NTRUParameters params, NTL::ZZX encrypted, NTL::ZZX fp, NTL::ZZX f);