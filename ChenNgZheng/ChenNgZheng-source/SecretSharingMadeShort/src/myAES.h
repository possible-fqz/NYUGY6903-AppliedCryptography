

#include <cstdio>
#include <iostream>
#include <osrng.h>


#include <iostream>


#include <string>


#include <cstdlib>


#include <cryptlib.h>


#include <hex.h>


#include <filters.h>


#include <des.h>


#include <modes.h>


#include <secblock.h>

#include <iostream>
#include <string>
#include <modes.h>
#include <aes.h>
#include <filters.h>

std::string aesEncrypt(std::string key, std::string plaintext);

std::string aesDecrypt(std::string key, std::string ciphertext);