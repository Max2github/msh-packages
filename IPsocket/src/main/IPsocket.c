#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/words.h"

void msh_command_main_send_IPsocket() {
    // parse arguments
    if (!find(msh_Wert, "TO")) { msh_error("separator \"TO\" is missing."); return; }
    char ** arguments;
    int argCount = split(msh_Wert, "TO", &arguments);
    if (argCount > 2) { return msh_error("send-IPsocket - write \"TO\" only once!"); }

    int clientSocket = MSH_STRING_TO_INT(arguments[1]);
    char * data = arguments[0];
    replaceS(data, "\\r", "\r");
    replaceS(data, "\\n", "\n");

    send(clientSocket, data, word_len(data), 0);
    freeWordArr(arguments, argCount);
}

void msh_command_main_close_IPsocket() {
    int socket = MSH_STRING_TO_INT(msh_Wert);

    close(socket);
    shutdown(socket, SHUT_RDWR);
}