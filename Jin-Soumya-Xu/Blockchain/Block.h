#ifndef _BLOCK_H
#define _BLOCK_H

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Block{
private:
    int index;
    string data; 
    string hash;
    string prevHash;
    time_t timestamp;
    int nonce;
public:
    Block(int index, string data, string prevHash, time_t timestamp);
    int getIndex();
    string getData();
    string getHash();
    string getPrevHash();
    time_t getTimestamp();
    string genHash();
    void mine(int difficulty);
};

#endif 