#include <iostream>
#include <time.h>
#include <string>

#include <NTL/ZZ.h>
#include <NTL/ZZ_pEX.h>

#include "tests/test_NTRU.hpp"
#include "tests/test_poly.hpp"

#include "NTRU.hpp"
#include "polyinvert.hpp"
#include "util.hpp"
#include "NTRUEncrypter.hpp"
#include "benchmark.hpp"

//https://assets.onboardsecurity.com/static/downloads/NTRU/resources/NTRU-PKCS-Tutorial.pdf
//https://assets.onboardsecurity.com/static/downloads/NTRU/resources/NTRUTech014.pdf
//https://assets.onboardsecurity.com/static/downloads/NTRU/resources/NTRU-Algebra-Tutorial.pdf

int main(int argc, char* argv[]) {
    NTL::SetSeed(NTL::conv<NTL::ZZ>((long) time(0)));

    if(argc != 4) {
        std::cout << "Usage: NTRU [N] [q (base)] [q (power)]" << std::endl;
    }
    else {
        long N = std::stoi(argv[1]);
        long q_prime = std::stoi(argv[2]);
        long q_power = std::stoi(argv[3]);
        long smallpoly = (long) (N * 0.15);

        NTRUParameters params(N, NTL::ZZ(3), NTL::ZZ(q_prime), q_power, smallpoly+1, smallpoly);
        benchmark_keygen(params);
        benchmark_encryption(params);
        benchmark_decryption(params);
    }

    // test::polyinvertPrime();
    // test::polyinvertPrimePower();

    // test::NTRUkeygen();
    // test::NTRUencrypt();
    // test::NTRUdecrypt();
    // int testfails = 0;
    // int realfails = 0;
    // const int loopcount = 100;
    // for(int i = 0; i < loopcount; i++) {
    //     if(!test::NTRUtestAll()) testfails++;
    //     if(!test::NTRUtestRealWorld()) realfails++;
    // }
    // std::cout << ((double) testfails / loopcount) * 100 << "% test fail rate\n";
    // std::cout << ((double) realfails / loopcount) * 100 << "% real fail rate\n";


    return 0;
}