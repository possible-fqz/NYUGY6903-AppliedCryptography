#include "benchmark.hpp"

#include <iostream>
#include <chrono>
#include <ctime>

#include "util.hpp"
#include "NTRUEncrypter.hpp"

void benchmark_keygen(NTRUParameters params) {
    using namespace std::chrono;

    NTRUEncrypter en(params);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    clock_t begin = clock();

    for(int i = 0; i < 10; i++)
        en = NTRUEncrypter(params);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    clock_t end = clock();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::cout << double(end - begin) / CLOCKS_PER_SEC << std::endl;
    std::cout << "Keygen run time: " << duration / 10.0 << "us" << std::endl;
    std::cout << "Total run time: " << duration << "us" << std::endl;
}

void benchmark_encryption(NTRUParameters params) {
    using namespace std::chrono;

    NTRUEncrypter en(params);
    NTL::ZZX mes = generateRandomPolynomial(params.N, NTL::ZZ(-1), NTL::ZZ(1));

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for(int i = 0; i < 10; i++)
        en.encrypt(mes);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::cout << "Encryption run time: " << duration / 10.0 << "us" << std::endl;
    std::cout << "Total run time: " << duration << "us" << std::endl;
}

void benchmark_decryption(NTRUParameters params) {
    using namespace std::chrono;

    NTRUEncrypter en(params);
    NTL::ZZX m = generateRandomPolynomial(params.N, NTL::ZZ(-1), NTL::ZZ(1));
    NTL::ZZX e = en.encrypt(m);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    for(int i = 0; i < 10; i++)
        en.decrypt(e);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::cout << "Decryption run time: " << duration / 10.0 << "us" << std::endl;
    std::cout << "Total run time: " << duration << "us" << std::endl;
}