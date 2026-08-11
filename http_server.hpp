
#include <string>
//#include <cstring>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

#ifndef INCLUDED_HTTP_SERVER
#define INCLUDED_HTTP_SERVER



class http_server{
    private:
        int server_fd;
        int port;
        std::string_view msg;
        void setupSocket();
        void handleClient(int client_fd);
    public:
        http_server();
        ~http_server();

};