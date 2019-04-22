#include "util.hpp"

inline NTL::ZZ mod(NTL::ZZ n, NTL::ZZ M) {
    return ((n % M) + M) % M;
}

NTL::ZZX constructPolynomial(const std::vector<long>& terms) {
    NTL::ZZX poly;
    for(int i = 0; i < terms.size(); i++) {
        NTL::SetCoeff(poly, i, terms[i]);
    }
    return poly;
}

void modPolynomial(NTL::ZZX& poly, NTL::ZZ num, bool center) {
    for(int i = 0; i < NTL::deg(poly)+1; i++) {
        poly[i] = mod(poly[i], num);
        //TODO: micro-optimize
        if(center && poly[i] > num/2)
            poly[i] -= num;
    }
    poly.normalize();
}