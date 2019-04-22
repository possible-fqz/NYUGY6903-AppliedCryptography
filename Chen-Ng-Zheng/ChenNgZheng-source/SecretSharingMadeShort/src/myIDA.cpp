#define uint8_t byte

#include "myIDA.h"
#include <string>
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


#include "ida.h"
#include "files.h"

using namespace std;
using namespace CryptoPP;

void InformationDisperseFile(int threshold, int nShares, const char *filename)
{
	CRYPTOPP_ASSERT(threshold >= 1 && threshold <= 1000);
	if (threshold < 1 || threshold > 1000)
		throw InvalidArgument("InformationDisperseFile: " + IntToString(nShares) + " is not in range [1, 1000]");

	ChannelSwitch *channelSwitch = NULLPTR;
	FileSource source(filename, false, new InformationDispersal(threshold, nShares, channelSwitch = new ChannelSwitch));
	//string newfilename = string(filename).substr(0, string(filename).size() - 4);
	// Be careful of the type of Sink used. An ArraySink will stop writing data once the array
	//    is full. Also see http://groups.google.com/forum/#!topic/cryptopp-users/XEKKLCEFH3Y.
	vector_member_ptrs<FileSink> fileSinks(nShares);
	std::string channel;
	for (int i = 0; i < nShares; i++)
	{
		char extension[5] = "000";
		extension[1] = '0' + byte(i / 100);
		extension[2] = '0' + byte((i / 10) % 10);
		extension[3] = '0' + byte(i % 10);
		fileSinks[i].reset(new FileSink((std::string(filename) + extension).c_str()));

		channel = WordToString<word32>(i);
		fileSinks[i]->Put((const byte *)channel.data(), 4);
		channelSwitch->AddRoute(channel, *fileSinks[i], DEFAULT_CHANNEL);
	}

	source.PumpAll();
}

void InformationRecoverFile(int threshold, const char *outFilename, const char* *inFilenames)
{
	CRYPTOPP_ASSERT(threshold <= 1000);
	if (threshold < 1 || threshold > 1000)
		throw InvalidArgument("InformationRecoverFile: " + IntToString(threshold) + " is not in range [1, 1000]");

	InformationRecovery recovery(threshold, new FileSink(outFilename));

	vector_member_ptrs<FileSource> fileSources(threshold);
	SecByteBlock channel(4);
	int i;
	for (i = 0; i < threshold; i++)
	{
		fileSources[i].reset(new FileSource(inFilenames[i], false));
		fileSources[i]->Pump(4);
		fileSources[i]->Get(channel, 4);
		fileSources[i]->Attach(new ChannelSwitch(recovery, std::string((char *)channel.begin(), 4)));
	}

	while (fileSources[0]->Pump(256))
		for (i = 1; i < threshold; i++)
			fileSources[i]->Pump(256);

	for (i = 0; i < threshold; i++)
		fileSources[i]->PumpAll();
}


void disperse(int min, int nShares, string message, vector<string>& pieces) {
	ofstream ofs;
	ofs.open("message", std::ofstream::out | std::ofstream::trunc);
	ofs << message;
	ofs.close();
	InformationDisperseFile(min, nShares, "message");
	for (size_t i = 0; i < nShares; i++) {
		char extension[5] = "000";
		extension[1] = '0' + byte(i / 100);
		extension[2] = '0' + byte((i / 10) % 10);
		extension[3] = '0' + byte(i % 10);
		string newFile = (string("message") + extension).c_str();
		pieces.push_back(newFile);
	}
}

void recover(const int& min, vector<string> pieces, string& recoveredText) {
	const char*  joinedPieces[1000];
	for (size_t i = 0; i < min; i++) {
		joinedPieces[i] = pieces[i].c_str();
	}
	
	InformationRecoverFile(3, "return", joinedPieces);
	ifstream ifs;
	ifs.open("return");
	getline(ifs, recoveredText);
	ifs.close();
}
