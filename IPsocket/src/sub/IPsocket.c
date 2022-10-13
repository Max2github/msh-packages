#include <netinet/in.h>
#include <sys/socket.h>

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/words.h"

void msh_command_sub_listen_IPsocket() {
    unsigned int port = MSH_STRING_TO_INT(msh_Wert);

    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    // htons : convert to "network byte order" (big endian)
    servAddr.sin_port = htons(port); // use some unused port number
    servAddr.sin_addr.s_addr = INADDR_ANY;
    
    // set options
    int opt = 1;
    // reuse addr, should eliminate problems with address already in use
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        return msh_error("internal: listen-IPsocket - serverSocket - setsockopt() - SO_REUSEADDR failed");
    }
    // reuse port, should eliminate problems with port already in use
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        return msh_error("internal: listen-IPsocket - serverSocket - setsockopt() - SO_REUSEPORT failed");
    }

    int bound = bind(serverSocket, (struct sockaddr *) &servAddr, sizeof(servAddr));
    if(bound < 0) { return msh_error("listen-IPsocket, internal: serverSocket - bind() failed"); }
    int listening = listen(serverSocket, 1);
    if(listening < 0) { return msh_error("listen-IPsocket, internal: serverSocket - listen() failed"); }

    // return serverSocket
    char socketIDStr[intLen(serverSocket) + 1]; intToString(serverSocket, socketIDStr);
    set_msh_Wert(socketIDStr);
}

void msh_command_sub_accept_IPsocket() {
    int serverSocket = MSH_STRING_TO_INT(msh_Wert); // get parameter serverSocket

    int clientSocket = accept(serverSocket, NULL, NULL);

    // return clientSocket
    char socketIDStr[intLen(clientSocket) + 1]; intToString(clientSocket, socketIDStr);
    set_msh_Wert(socketIDStr);
}

void msh_command_sub_receive_IPsocket() {
    int clientSocket = MSH_STRING_TO_INT(msh_Wert);  // get parameter clientSocket

    char * buf = malloc(VAR_MAXCHAR);
    recv(clientSocket, buf, VAR_MAXCHAR, 0);
    set_msh_Wert(buf);
    free(buf);
}
