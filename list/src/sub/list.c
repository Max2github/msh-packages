/* #include "../../../include/alg.h"
#include "../../../dependencies/words.h"
#include "../../../dependencies/std.h"
#include "../../../include/list.h"

// optional
#include "../../cparts/command_def.h" */

#include "../../../../mshgit/dependencies/std.h"

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/include/list.h"

#include "../../../../mshgit/dependencies/extern.h"

void msh_command_sub_toString_list(msh_info * msh) {
    char ** wordArr;
    int Teile = split((const char *) msh_Wert, "IN", &wordArr);
    if (Teile == 0) { freeWordArr(wordArr, Teile); }
    else {
        set_msh_Wert(msh, wordArr[Teile]);
    }

    MSH_MUTEX_LOCK(MSH_LIST_MUTEX);
    list List = msh_getListByName(msh_Wert);
    if (Teile == 0) { list_toStr(List, msh_Wert, NULL); }
    else {
        char ** sepArr;
        int sepAnzahl = split(wordArr[0], "&/arr//", &sepArr);
        list sepList = list_addFirst(NULL, String, sepArr[0], End);
        for (int sepCount = 1; sepCount <= sepAnzahl; sepCount++) {
            list_addLast(sepList, String, sepArr[sepCount], End);
        }
        freeWordArr(sepArr, sepAnzahl);
        list_toStr(List, msh_Wert, sepList);
        list_free(sepList);
        freeWordArr(wordArr, Teile);
    }
    MSH_MUTEX_UNLOCK(MSH_LIST_MUTEX);
}
void msh_command_sub_getFirst_list(msh_info * msh) {
    char ** wordArr;
    int Teile = split(msh_Wert, ":", &wordArr);
    if (Teile != 2) {
        freeWordArr(wordArr, Teile);
        return;
    }
    char * name = wordArr[0];
    char * type = wordArr[1];
    char * value = wordArr[2];

    MSH_MUTEX_LOCK(MSH_LIST_MUTEX);
    list toMod = msh_getListByName(name);
    if (toMod == NULL) {
        MSH_MUTEX_UNLOCK(MSH_LIST_MUTEX);
        set_msh_Wert(msh, "NULL");
        freeWordArr(wordArr, Teile);
        return;
    }

    if (word_compare(type, "Index") == 0) {
        int index = atoi(value);
        if (index >= list_node_len(toMod)) {
            MSH_MUTEX_UNLOCK(MSH_LIST_MUTEX);
            set_msh_Wert(msh, "NULL");
            freeWordArr(wordArr, Teile);
            return;
        }
        list_element_pointer el = list_seek(toMod, index);
        list_element_sprint(el, msh_Wert, NULL);
    } else if (word_compare(type, "Type") == 0) {
        
    } else if (word_compare(type, "Type&Value") == 0) {
        
    } else {
        msh_error(msh, "Option \"%s\" not found! Please only enter \"Index\", \"Type\" or \"Type&Value\".\n", type);
    }

    MSH_MUTEX_UNLOCK(MSH_LIST_MUTEX);
    freeWordArr(wordArr, Teile);
}
void msh_command_sub_len_list(msh_info * msh) {
    MSH_MUTEX_LOCK(MSH_LIST_MUTEX);
    intToString(list_node_len(msh_getListByName(msh_Wert)), msh_Wert);
    MSH_MUTEX_UNLOCK(MSH_LIST_MUTEX);
}