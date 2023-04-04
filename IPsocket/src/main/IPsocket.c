#include "../../../../mshgit/dependencies/std.h"

#include "../../../../mshgit/include/alg.h"

#include "../../../../mshgit/dependencies/extern.h"

void msh_command_main_send_IPsocket(msh_info * msh) {
    // parse arguments
    const char * wert = get_msh_Wert(msh);
    if (!find(wert, "TO")) { msh_error(msh, "separator \"TO\" is missing."); return; }
    char ** arguments;
    int argCount = split(wert, "TO", &arguments);
    if (argCount > 2) { return msh_error(msh, "send-IPsocket - write \"TO\" only once!"); }

    int clientSocket = MSH_STRING_TO_INT(arguments[1]);
    char * data = arguments[0];
    int len = 0;
    if (msh_ref_string_is_ref(data)) {
        index32 id = msh_ref_id_from_string(data, word_len(data));
        msh_ref * ref = msh_ref_get(msh, id);
        switch (ref->type) {
            case msh_ref_type_BIN   : msh_error(msh, "IPsocket / msh_ref: Cannot handle binary data yet"); data = NULL; break;
            case msh_ref_type_STRING: {
                word_picker d = msh_ref_get_data_as_string(msh, id);
                data = (char *) d.begin;
                len = word_picker_len(d);
                break;
            }
            case msh_ref_type_FILE  : msh_error(msh, "IPsocket / msh_ref: Cannot handle binary data yet"); data = NULL; break;
        }
    } else {
        replaceS(data, "\\r", "\r");
        replaceS(data, "\\n", "\n");
        word_len(data);
    }

    if (data != NULL) {
        send(clientSocket, data, len, 0);
        freeWordArr(arguments, argCount);
    }
}

void msh_command_main_close_IPsocket(msh_info * msh) {
    int socket = MSH_STRING_TO_INT(get_msh_Wert(msh));

    msh_socket_close(socket);
}