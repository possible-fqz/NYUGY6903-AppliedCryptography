#include "test_poly.hpp"

#include <cassert>
#include <NTL/ZZX.h>
#include "polyinvert.hpp"
#include "NTRU.hpp"
#include "util.hpp"

namespace test
{

void polyinvertPrime() {
    NTL::ZZX answerpoly;
    NTL::SetCoeff(answerpoly, 0, 1);

    NTL::ZZX ringpoly;
    NTL::SetCoeff(ringpoly, 25, 1);
    NTL::SetCoeff(ringpoly, 0, -1);

    int i = 0;
    while(i < 100) {
        NTL::ZZX foo = generateRandomPolynomial(25, NTL::ZZ(-1), NTL::ZZ(1));
        NTL::ZZX res = invertPolynomialPrime(foo, NTL::ZZ(3), 25);

        if(NTL::deg(res) < 0)
            continue;
            
        res = (res * foo) % ringpoly;
        modPolynomial(res, NTL::ZZ(3), true);

        assert(res == answerpoly);
        i++;
    }
}

void polyinvertPrimePower() {
    NTL::ZZX answerpoly;
    NTL::SetCoeff(answerpoly, 0, 1);

    NTL::ZZX ringpoly;
    NTL::SetCoeff(ringpoly, 25, 1);
    NTL::SetCoeff(ringpoly, 0, -1);

    int i = 0;
    while(i < 100) {
        NTL::ZZX foo = generateRandomPolynomial(25, NTL::ZZ(-1), NTL::ZZ(1));
        NTL::ZZX res = invertPolynomialPrimePower(foo, NTL::ZZ(2), 6, 25);

        if(NTL::deg(res) < 0)
            continue;
            
        res = (res * foo) % ringpoly;
        modPolynomial(res, NTL::ZZ(64), true);        

        assert(res == answerpoly);
        i++;
    }
}

}