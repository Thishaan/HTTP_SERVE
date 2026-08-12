#include <optional>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unordered_map>
#include <sstream>

#include <functional>
#ifndef INCLUDED_HTTP_SERVER
#define INCLUDED_HTTP_SERVER


struct http_request {
    std::string method;
    std::string path;
    std::string version;
};

void handle_get(int fd);
void handle_post(int fd);
void handle_head(int fd);
void handle_put(int fd);

class http_server{
    private:
        int server_fd;
        int port;
        std::string_view msg;
        std::optional<int> setupSocket(); // returns
        std::unordered_map <std::string, std::string (int)> cmd_handler; 
        void handleClient(int client_fd);
    public:
        explicit http_server(int port);
        ~http_server();

};


#endif