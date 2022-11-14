#include <netinet/in.h>
#include <sys/socket.h>
 #include <arpa/inet.h>

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/words.h"

typedef int socket_t;

// I'm not absolutely sure about the names,
// so I'll just leave it for now
#define MSH_IPSOCKET_TCP SOCK_STREAM
#define MSH_IPSOCKET_UDP SOCK_DGRAM
#define MSH_IPSOCKET_IPV4 AF_INET
#define MSH_IPSOCKET_IPV6 AF_INET6

socket_t msh_IPsocket_socket_create() {
    return socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
}

struct sockaddr_in msh_IPsocket_addr_in_create(in_addr_t address, in_port_t port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    // htons : convert to "network byte order" (big endian)
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(address);
    return addr;
}

void msh_IPsocket_addr_in_setAddr(const char * address, struct sockaddr_in * addr) {
    if (inet_pton(AF_INET, address, &addr->sin_addr) <= 0) {
        // msh_error()
    }
}

void msh_command_sub_listen_IPsocket(msh_info * msh) {
    unsigned int port = MSH_STRING_TO_INT(get_msh_Wert(msh));

    /*socket_t serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    // htons : convert to "network byte order" (big endian)
    servAddr.sin_port = htons(port); // use some unused port number
    servAddr.sin_addr.s_addr = INADDR_ANY;*/
    socket_t serverSocket = msh_IPsocket_socket_create();
    struct sockaddr_in servAddr = msh_IPsocket_addr_in_create(INADDR_ANY, port);
    
    // set options
    int opt = 1;
    // reuse addr, should eliminate problems with address already in use
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        return msh_error(msh, "internal: listen-IPsocket - serverSocket - setsockopt() - SO_REUSEADDR failed");
    }
    // reuse port, should eliminate problems with port already in use
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        return msh_error(msh, "internal: listen-IPsocket - serverSocket - setsockopt() - SO_REUSEPORT failed");
    }

    int bound = bind(serverSocket, (struct sockaddr *) &servAddr, sizeof(servAddr));
    if(bound < 0) { return msh_error(msh, "listen-IPsocket, internal: serverSocket - bind() failed"); }
    int listening = listen(serverSocket, 1);
    if(listening < 0) { return msh_error(msh, "listen-IPsocket, internal: serverSocket - listen() failed"); }

    // return serverSocket
    char socketIDStr[intLen(serverSocket) + 1]; intToString(serverSocket, socketIDStr);
    set_msh_Wert(msh, socketIDStr);
}

void msh_command_sub_accept_IPsocket(msh_info * msh) {
    socket_t serverSocket = MSH_STRING_TO_INT(get_msh_Wert(msh)); // get parameter serverSocket

    socket_t clientSocket = accept(serverSocket, NULL, NULL);

    // return clientSocket
    char socketIDStr[intLen(clientSocket) + 1]; intToString(clientSocket, socketIDStr);
    set_msh_Wert(msh, socketIDStr);
}

void msh_command_sub_connect_IPsocket(msh_info * msh) {
    const char * all = get_msh_Wert(msh);
    char address[word_len_until(all, ":") + 1];
    const char * portStr = word_copy_until(address, all, ":");
    unsigned int port = MSH_STRING_TO_INT(portStr);

    socket_t clientSocket = msh_IPsocket_socket_create();
    struct sockaddr_in servAddr = msh_IPsocket_addr_in_create(INADDR_ANY, port);
    msh_IPsocket_addr_in_setAddr(address, &servAddr);

    int err = connect(clientSocket, (struct sockaddr *) &servAddr, sizeof(servAddr));

    // return clientSocket
    char socketIDStr[intLen(clientSocket) + 1]; intToString(clientSocket, socketIDStr);
    set_msh_Wert(msh, socketIDStr);
}

void msh_command_sub_receive_IPsocket(msh_info * msh) {
    socket_t clientSocket = MSH_STRING_TO_INT(get_msh_Wert(msh));  // get parameter clientSocket

    char * buf = malloc(VAR_MAXCHAR);
    recv(clientSocket, buf, VAR_MAXCHAR, 0);
    set_msh_Wert(msh, buf);
    free(buf);
}
