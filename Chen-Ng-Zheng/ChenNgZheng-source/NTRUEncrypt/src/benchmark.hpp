#pragma once

#include "NTRU.hpp"

// Returns microseconds run
void benchmark_keygen(NTRUParameters params);
void benchmark_encryption(NTRUParameters params);
void benchmark_decryption(NTRUParameters params);