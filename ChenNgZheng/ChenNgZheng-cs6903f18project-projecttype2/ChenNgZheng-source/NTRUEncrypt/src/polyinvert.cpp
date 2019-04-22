#include "polyinvert.hpp"

//TODO: implement more efficient inversion functions mod 2/3

#include "util.hpp"

inline long mod(long n, long M) {
    return ((n % M) + M) % M;
}

//TODO: memoize inverses mod prime for performance
NTL::ZZ invMod(NTL::ZZ num, NTL::ZZ modby) {
    num = mod(num, modby);
    if(NTL::GCD(num, modby) != 1) {
        return NTL::ZZ(0);
    }

    return NTL::InvMod(num, modby);
}

NTL::ZZX invertPolynomialPrime(NTL::ZZX a, NTL::ZZ prime, long N) {
    a.SetMaxLength(N);

    NTL::ZZX ringpoly;
    NTL::SetCoeff(ringpoly, N, 1);
    NTL::SetCoeff(ringpoly, 0, -1);

    // Initialization:
    // k=0, b(X) = 1, c(X) = 0, f(X)=a(X), g(X)=X^N-1
    int k = 0;
    NTL::ZZX b;
    b.SetLength(N+1);
    NTL::ZZX c;
    c.SetLength(N+1);
    NTL::ZZX f;
    f.SetLength(N+1);
    NTL::ZZX g;
    g.SetLength(N+1);

    NTL::SetCoeff(b, 0, 1);

    f = a;
    modPolynomial(f, prime, false);

    NTL::SetCoeff(g, N, 1);
    NTL::SetCoeff(g, 0, -1);

    while (true)
    {
        if(NTL::deg(f) < 0)
            return NTL::ZZX();
        // while f[0] = 0 {f/=X, c*=X, k++}
        while (f[0] == 0)
        {
            f = (f >> 1);
            c = (c << 1);
            k++;
        }
        f.normalize();

        if(NTL::deg(f) == 0)
        {
            // Make sure there is a solution.
            // Return null if a is not invertible
            NTL::ZZ f0Inv = invMod(f[0], prime);
            if (f0Inv == 0)
                return NTL::ZZX();

            // b(X) = f[0]inv * b(X) mod p
            // return X^(N-k) * b

            b *= f0Inv;
            modPolynomial(b, prime, false);
            
            int shift = mod(N-k, N);
            return (b << shift) % ringpoly;
        }
        else if(NTL::deg(f) < NTL::deg(g))
        {
            std::swap(f, g);
            std::swap(b, c);
        }

        // u = f[0] * g[0]inv mod p
        NTL::ZZ u = mod(f[0] * invMod(g[0], prime), prime);

        // f(X) -= u*g(X) mod p
        f = f - (u * g);
        modPolynomial(f, prime, false);

        // b(X) -= u*c(X) mod p
        b = b - (u * c);
        modPolynomial(b, prime, false);
    }
}

NTL::ZZX invertPolynomialPrimePower(NTL::ZZX a, NTL::ZZ prime, long power, long N) {
    a.SetMaxLength(N);

    NTL::ZZX ringpoly;
    NTL::SetCoeff(ringpoly, N, 1);
    NTL::SetCoeff(ringpoly, 0, -1);

    NTL::ZZX b = invertPolynomialPrime(a, prime, N);
    if(NTL::deg(b) < 0)
        return b;

    NTL::ZZ q = prime;
    NTL::ZZ pr = NTL::power(prime, power);
    while(q < pr) {
        q *= q;
        b = b * (2 - a * b);
        b %= ringpoly;
        modPolynomial(b, pr, false);
    }
    return b;
}