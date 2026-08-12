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

 std::cout << "destroying objects" << std::endl;
}

void http_server::handleClient(int client_fd) {

    char buffer[4096]{};

    ssize_t bytes = recv(
        client_fd,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (bytes <= 0) {
        close(client_fd);
        return;
    }

    std::string request(buffer, bytes);

    std::istringstream stream(request);

    std::string method;
    std::string path;
    std::string version;

    stream >> method >> path >> version;

    std::cout << "Method: " << method << '\n';
    std::cout << "Path: " << path << '\n';
    std::cout << "Version: " << version << '\n';

    // create response
    std::string resp =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 5\r\n"
        "\r\n"
        "Hello";

    send(client_fd, resp.data(), resp.size(), 0);

    close(client_fd);
}


