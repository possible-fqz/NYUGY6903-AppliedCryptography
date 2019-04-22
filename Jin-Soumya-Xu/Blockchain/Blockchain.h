#ifndef _BLOCKCHAIN_H
#define _BLOCKCHAIN_H

#include <vector>
#include <ctime>
#include "Block.h"

class Blockchain{
private:
    vector<Block> blockchain;
    int difficulty;
public:
    Blockchain(int difficulty);
    vector<Block> getBlockchain();
    Block getLastBlock();
    bool isBlockchainValid();
    void addBlock(string data, time_t timestamp);
    void displayBlockchain();
    string returnBlockchainAsString();
};

#endif 
