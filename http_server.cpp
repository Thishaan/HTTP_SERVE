#include "http_server.hpp"




http_server::http_server(int port)
    : server_fd(-1), port(port) {}

void HttpServer::setupSocket() {
    // socket()
    socket
    // setsockopt()
    // bind()
    // listen()
}



http_server::~http_server(){


}


void HttpServer::handleClient(int client_fd) {
    // recv request
    // parse request
    // create response
    // send response
    // close client
}


