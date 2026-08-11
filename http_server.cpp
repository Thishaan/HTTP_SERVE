#include "http_server.hpp"




http_server::http_server(int port)
    : server_fd(-1), port(port) {}


    // return communicatio sockte
std::optional<int> http_server::setupSocket() {
    // socket()
    server_fd = socket(AF_INET,SOCK_STREAM,0);

    if(server_fd < 0){
        exit(1);
    }
    sockaddr_in server{};
    server.sin_family = AF_INET; //  IPV4  , standard
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port); 
    // bind()

    if(bind(server_fd, (sockaddr*)&server, sizeof(server)) < 0){
        exit(2);
 
    }


    if(listen(server_fd , 5 ) < 0){
        exit(3);
    }
    
    int client_fd = accept(server_fd, nullptr, nullptr);

    if(client_fd < 0)
        return std::nullopt;


    return client_fd;  // success code
  }



http_server::~http_server(){


}


void http_server::handleClient(int client_fd) {

    std::string buffer[3];
    // recv request
    recv(client_fd, &buffer, sizeof(buffer), 0);


    // parse request
    
    // create response
    // send response

    close(server_fd);
    // close client
    close(client_fd);
}


