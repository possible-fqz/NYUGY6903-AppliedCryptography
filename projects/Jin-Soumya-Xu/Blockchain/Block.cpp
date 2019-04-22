#include "Block.h"
#include "sha256.h"



Block::Block(int index, string data, string prevHash, time_t timestamp){
    this->index = index;
    this->data = data;
    this->prevHash = prevHash;
    this->timestamp = timestamp;
    this->hash = genHash();
    this->nonce = 0;
}

int Block::getIndex(){ return index; }

string Block::getData(){ return data; }

string Block::getHash(){ return hash; }

string Block::getPrevHash(){ return prevHash; }

time_t Block::getTimestamp(){ return timestamp; }

string Block::genHash(){
    string toHash = to_string(index) + data + to_string(timestamp) + prevHash + to_string(nonce);
    return sha256(toHash);
}

void Block::mine(int difficulty) { 
    string zeros = "";
    for (int i = 0; i < difficulty; ++i){
        zeros += "0";
    }
    while(hash.substr(0, difficulty) != zeros){
          nonce++;
          hash = genHash();
    }
}