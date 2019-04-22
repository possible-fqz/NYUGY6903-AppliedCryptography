#include "NTRUEncrypter.hpp"

#include "polyinvert.hpp"
#include "NTRU.hpp"
#include "util.hpp"

NTRUEncrypter::NTRUEncrypter(NTRUParameters p) : params(p) {
    if(!verifyNTRUParameters(params)) {
        throw std::runtime_error("Error: invalid params in generatePublicKey");
    }

    NTL::ZZX f, g, res;
    while(NTL::deg(res) < 0) {
        f = generateSmallPolynomial(params.N, params.df, params.df-1);
        g = generateSmallPolynomial(params.N, params.dg, params.dg);

        res = ::generatePublicKey_internal(params, f, g, this->fp);
        //TODO: verify f has ~28% non-zero coefficients
    }

    this->f = f;
    this->h = res;
}

NTL::ZZX NTRUEncrypter::getPublicKey() {
    return h;
}

NTL::ZZX NTRUEncrypter::encrypt(NTL::ZZX message) {
    return ::encrypt(params, this->h, message);
}

NTL::ZZX NTRUEncrypter::decrypt(NTL::ZZX encrypted) {
    return ::decrypt(params, encrypted, this->fp, this->f);
}