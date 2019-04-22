#pragma once

#include <NTL/ZZX.h>

#include "NTRU.hpp"

//Wrapper of NTRU functions that maintains state
class NTRUEncrypter {
public:
    NTRUEncrypter(NTRUParameters p);

    NTL::ZZX getPublicKey();
    NTL::ZZX encrypt(NTL::ZZX message);
    NTL::ZZX decrypt(NTL::ZZX encrypted);
private:
    NTRUParameters params;
    NTL::ZZX f;
    NTL::ZZX fp;
    NTL::ZZX h;
};