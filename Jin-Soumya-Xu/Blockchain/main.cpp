#include "Block.h"
#include "Blockchain.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fstream>
#include <unistd.h>
#include <_types.h>
#include <thread>

using namespace std;

const int BUFFSIZE = 1024;
const int MAXLINK = 10;
const int DEFAULT_PORT = 8080;



void broadcastthread(Blockchain* b,  int connect_fd){
    
    while(true){
    sleep(10);
    string temp = b->returnBlockchainAsString();
    int size = temp.length();
    //string temp = "" ;
    const char* s= temp.c_str();
    send(connect_fd, s, size ,0);
    // fill it with your output char * s = b.output();
    }
}

void addingthread(char* buff, int connect_fd, int socket_fd , Blockchain* b){
    
    
    thread broadcast(broadcastthread, b ,connect_fd);
    broadcast.detach();
    memset(buff, '\0', sizeof(buff));
    recv(connect_fd, buff, BUFFSIZE - 1, 0);
    cout<<buff<<endl;
    //
    time_t time1;
    b->addBlock(buff, time(&time1));
    //
    //send(connect_fd, buff, sizeof(buff), 0);
    close(connect_fd);
    //close(socket_fd);
    
}




int main(){

    Blockchain b(5); // pass in difficulty value
    
    cout << "Mining Block 0..." << endl;
    time_t time1;
    b.addBlock("Hello", time(&time1)); // pass in data & timestamp
    cout << "Mining Block 0 complete" << endl;

    cout << "Mining Block 1..." << endl;
    time_t time2;
    b.addBlock("Bye", time(&time2));
    cout << "Mining Block 1 complete" << endl;
    
    //b.displayBlockchain();
    cout << b.returnBlockchainAsString() << endl;
    
    
    // network
    
    
    int socket_fd, connect_fd;
    struct sockaddr_in servaddr;
    char buff[BUFFSIZE];
    
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        cout<<"create socket error"<<endl;
        return -1;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);
    
    if ( ::bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        cout<<"bind error"<<endl;
        return -1;
    }
    bool flag = true;
    while(flag){
        if (listen(socket_fd, MAXLINK) == -1) {
            cout<<"listen error"<<endl;
            flag  = false;
            break;
        }
        
        connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL);
        if (connect_fd == -1) {
            cout<<"accept error"<<endl;
        }
        else {
            cout<<"Connect Success"<<endl;
            thread task(addingthread, buff, connect_fd, socket_fd, &b);
            task.detach();
            
        }
    }
    
    close(connect_fd);
    close(socket_fd);
    
    // network end
    
    
    
    
    
    return 0;
}


//
