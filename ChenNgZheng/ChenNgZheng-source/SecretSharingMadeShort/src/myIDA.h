#pragma once
#define uint8_t byte

#include <string>
#include "ida.h"
#include <iostream>
#include <iomanip>
#include "modes.h"
#include "filters.h"
#include "cryptlib.h"
#include "hex.h"
#include "secblock.h"
#include "osrng.h"
#include "cryptlib.h"
#include "mqueue.h"
#include "filters.h"
#include "channels.h"
#include "secblock.h"
#include "stdcpp.h"
#include "misc.h"
#include <cstring>
#include "files.h"

void InformationDisperseFile(int threshold, int nShares, const char *filename);

void InformationRecoverFile(int threshold, const char *outFilename, const char* *inFilenames);

void disperse(int min, int nShares, std::string message, std::vector<std::string>& pieces);

void recover(const int& min, std::vector<std::string> pieces, std::string& recoveredText);