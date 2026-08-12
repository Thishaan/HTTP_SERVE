#include <optional>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <array>

#include <functional>
#ifndef INCLUDED_HTTP_SERVER
#define INCLUDED_HTTP_SERVER


struct http_request {
    std::string method;
    std::string path;
    std::string version;
};

std::string handle_get(int fd);
std::string  handle_post(int fd);
std::string  handle_put(int fd);

using handler_fns = std::string (*)(int fd);

handler_fns handlers[] = {
    handle_get,
    handle_post,
    handle_put
};
class http_server{
    private:
        int server_fd;
        int port;
        

        std::array<std::string,3> commands =  {"get", "post", "put"};
        std::string resource{};
        std::string_view msg;
        std::optional<int> setupSocket(); // returns
        std::unordered_map <std::string, handler_fns> cmd_handler; 
        void handleClient(int client_fd);
    public:
        explicit http_server(int port);
        ~http_server();

};


#endif