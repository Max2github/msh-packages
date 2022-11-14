#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/words.h"

void msh_command_main_send_IPsocket(msh_info * msh) {
    // parse arguments
    const char * wert = get_msh_Wert(msh);
    if (!find(wert, "TO")) { msh_error(msh, "separator \"TO\" is missing."); return; }
    char ** arguments;
    int argCount = split(wert, "TO", &arguments);
    if (argCount > 2) { return msh_error(msh, "send-IPsocket - write \"TO\" only once!"); }

    int clientSocket = MSH_STRING_TO_INT(arguments[1]);
    char * data = arguments[0];
    replaceS(data, "\\r", "\r");
    replaceS(data, "\\n", "\n");

    send(clientSocket, data, word_len(data), 0);
    freeWordArr(arguments, argCount);
}

void msh_command_main_close_IPsocket(msh_info * msh) {
    int socket = MSH_STRING_TO_INT(get_msh_Wert(msh));

    close(socket);
    shutdown(socket, SHUT_RDWR);
}