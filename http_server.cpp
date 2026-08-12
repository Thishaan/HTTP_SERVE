#include "http_server.hpp"


std::string handle_get() {
    std::string body =
        "<html><body>Hello!</body></html>";

    return
        "HTTP/1.1 200 OK\r\n"
        "Server: MyCppServer\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;
}


std::string handle_post() {
    std::string body = "Resource created";

    return
        "HTTP/1.1 201 Created\r\n"
        "Server: MyCppServer\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;
}


std::string handle_put() {
    std::string body = "Resource updated";

    return
        "HTTP/1.1 200 OK\r\n"
        "Server: MyCppServer\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;
}


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

void http_server::handleClient(int client_fd)
{
    char buffer[4096]{};

    ssize_t bytes_received = recv(
        client_fd,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (bytes_received <= 0) {
        close(client_fd);
        return;
    }

    std::string raw_request(buffer, bytes_received);
    std::istringstream request_stream(raw_request);

    std::string method;
    std::string path;
    std::string version;

    request_stream >> method >> path >> version;
    //std::string body;
    std::transform(method.begin(), method.end(), method.begin(),
    [](unsigned char c){ return std::toupper(c); });

    std::string status, response;
    

    if(cmd_handler[method]){
        response =  cmd_handler[method](client_fd);
    }
    else{
        send(
        client_fd,
        response.data(),
        response.size(),
        0
        );
        
    }
    

    close(client_fd);
}


