#include "test_NTRU.hpp"

#include <NTL/ZZX.h>
#include <cassert>

#include "polyinvert.hpp"
#include "NTRU.hpp"
#include "NTRUEncrypter.hpp"
#include "util.hpp"

namespace test
{

void NTRUkeygen() {
    NTRUParameters p(11, NTL::ZZ(3), NTL::ZZ(2), 5, 4, 3);
    NTL::ZZX f = constructPolynomial({-1, 1, 1, 0, -1, 0, 1, 0, 0, 1, -1});
    NTL::ZZX g = constructPolynomial({-1, 0, 1, 1, 0, 1, 0, 0, -1, 0, -1});
    NTL::ZZX fp;

    NTL::ZZX publickey = generatePublicKey_internal(p, f, g, fp);

    assert(publickey == constructPolynomial({8, -7, -10, -12, 12, -8, 15, -13, 12, -13, 16}));
}

void NTRUencrypt() {
    NTL::ZZX h = constructPolynomial({8, -7, -10, -12, 12, -8, 15, -13, 12, -13, 16});
    // NTL::ZZX h = constructPolynomial({8, 25, 22, 20, 12, 24, 15, 19, 12, 19, 16});

    NTL::ZZX m = constructPolynomial({-1, 0, 0, 1, -1, 0, 0, 0, -1, 1, 1});

    NTL::ZZX r = constructPolynomial({-1, 0, 1, 1, 1, -1, 0, -1});

    NTRUParameters p(11, NTL::ZZ(3), NTL::ZZ(2), 5, 4, 3);
    NTL::ZZX res = encrypt_internal(p, h, m, r);
    assert(res == constructPolynomial({14, 11, 26, 24, 14, 16, 30, 7, 25, 6, 19}));
}

void NTRUdecrypt() {
    NTRUParameters p(11, NTL::ZZ(3), NTL::ZZ(2), 5, 4, 3);

    NTL::ZZX e = constructPolynomial({14, 11, 26, 24, 14, 16, 30, 7, 25, 6, 19});
    NTL::ZZX fp = constructPolynomial({1, 2, 0, 2, 2, 1, 0, 2, 1, 2});
    NTL::ZZX f = constructPolynomial({-1, 1, 1, 0, -1, 0, 1, 0, 0, 1, -1});

    NTL::ZZX res = decrypt(p, e, fp, f);
    assert(res == constructPolynomial({-1, 0, 0, 1, -1, 0, 0, 0, -1, 1, 1}));
}

bool NTRUtestAll() {
    NTRUParameters params(11, NTL::ZZ(3), NTL::ZZ(2), 5, 4, 3);
    NTL::ZZX m = constructPolynomial({-1, 0, 0, 1, -1, 0, 0, 0, -1, 1, 1});

    NTRUEncrypter encrypter(params);

    NTL::ZZX e = encrypter.encrypt(m);

    NTL::ZZX res = encrypter.decrypt(e);

    return res == m;
}

bool NTRUtestRealWorld() {
    NTRUParameters params(251, NTL::ZZ(3), NTL::ZZ(2), 7, 37, 36);
    NTL::ZZX m = constructPolynomial({-1, 0, 0, 1, -1, 0, 0, 0, -1, 1, 1});

    NTRUEncrypter encrypter(params);

    NTL::ZZX e = encrypter.encrypt(m);

    NTL::ZZX res = encrypter.decrypt(e);

    return res == m;
}

}