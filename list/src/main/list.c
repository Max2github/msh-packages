/* #include "../../../include/alg.h"
#include "../../../dependencies/mathe.h"
#include "../../../dependencies/words.h"
#include "../../../dependencies/std.h"
#include "../../../include/list.h"

#include "../../cparts/command_def.h" */

#include "../../../../mshgit/dependencies/std.h"

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/include/list.h"

#include "../../../../mshgit/dependencies/extern.h"

// #include "../../../../mshgit/src/cparts/command_def.h"

void msh_command_main_delete_list(msh_info * msh);

void msh_command_main_add_list(msh_info * msh) {
    char ** wordArr;
    int Teile = split(msh_Wert, ":", &wordArr);
    if (Teile != 3) {
        freeWordArr(wordArr, Teile);
        return;
    }
    char * name = wordArr[0];
    char * indexP = wordArr[1];
    unsigned int index = *indexP - 48;
    char * type = wordArr[2];
    char * value = wordArr[3];
    list toMod = msh_getListByName(name);
    if (word_compare(indexP, "last") == 0) { index = list_node_len(toMod); }
    if (index < 0) { index = 0; }
    // printf("index: %d\n", index);

    if (toMod == NULL) {
        if (word_compare(type, "Char") == 0) {
            toMod = list_addFirst(toMod, Char, *value, End);
        } else if (word_compare(type, "Integer") == 0) {
            toMod = list_addFirst(toMod, Integer, atoi(value), End);
        } else if (word_compare(type, "Float") == 0) {
            toMod = list_addFirst(toMod, Float, atof(value), End);
        } else if (word_compare(type, "Double") == 0) {
            toMod = list_addFirst(toMod, Double, atof(value), End);
        } else if (word_compare(type, "String") == 0) {
            toMod = list_addFirst(toMod, String, value, End);
        } else if (word_compare(type, "List") == 0) {
            toMod = list_addFirst(toMod, List, msh_getListByName(value), End);
        }

        LIST_SPEICHER = list_addFirst(LIST_SPEICHER, List, toMod, String, name, End);
        list_free(toMod);
    } else if (index == 0) {
        list toModBoss = msh_getListBossByName(name);

        if (word_compare(type, "Char") == 0) {
            toModBoss->el = (unsigned long long) list_addFirst( (list) toModBoss->el, Char, *value, End);
        } else if (word_compare(type, "Integer") == 0) {
            toModBoss->el = (unsigned long long) list_addFirst( (list)toModBoss->el, Integer, atoi(value), End);
        } else if (word_compare(type, "Float") == 0) {
            toModBoss->el = (unsigned long long) list_addFirst( (list)toModBoss->el, Float, atof(value), End);
        } else if (word_compare(type, "Double") == 0) {
            toModBoss->el = (unsigned long long) list_addFirst( (list)toModBoss->el, Double, atof(value), End);
        } else if (word_compare(type, "String") == 0) {
            toModBoss->el = (unsigned long long) list_addFirst( (list)toModBoss->el, String, value, End);
        } else if (word_compare(type, "List") == 0) {
            toModBoss->el = (unsigned long long) list_addFirst( (list) toModBoss->el, List, msh_getListByName(value), End);
        }
    } else {
        if (word_compare(type, "Char") == 0) {
            list_addIndex(toMod, index, Char, *value, End);
        } else if (word_compare(type, "Integer") == 0) {
            list_addIndex(toMod, index, Integer, atoi(value), End);
        } else if (word_compare(type, "Float") == 0) {
            list_addIndex(toMod, index, Float, atof(value), End);
        } else if (word_compare(type, "Double") == 0) {
            list_addIndex(toMod, index, Double, atof(value), End);
        } else if (word_compare(type, "String") == 0) {
            list_addIndex(toMod, index, String, value, End);
        } else if (word_compare(type, "List") == 0) {
            list_addIndex(toMod, index, List, msh_getListByName(value), End);
        }
    }

    freeWordArr(wordArr, Teile);
}
void msh_command_main_remove_list(msh_info * msh) {
    char ** wordArr;
    int Teile = split(msh_Wert, ":", &wordArr);
    if (Teile != 2) {
        freeWordArr(wordArr, Teile);
        return;
    }
    char * name = wordArr[0];
    char * type = wordArr[1];
    char * value = wordArr[2];
    list toMod = msh_getListByName(name);
    if (toMod == NULL) {
        msh_error(msh, "");
        printf("List \"%s\" not found!\n", name);
        freeWordArr(wordArr, Teile);
        return;
    }

    if (word_compare(type, "Index") == 0) {
        int index = 0;
        if (word_compare(value, "last") == 0) { index = list_node_len(toMod)-1; }
        else { index = atoi(value); }
        if (index == 0) {
            if (list_node_len(toMod) == 1) {
                // word_copy(msh_Wert, name);
                set_msh_Wert(msh, name);
                msh_command_main_delete_list(msh);
                freeWordArr(wordArr, Teile);
                return;
            }
            list wholeNode = msh_getNodeByName(name);
            toMod = list_removeFirst(toMod);
            ((list) wholeNode->el)->el = (unsigned long long) toMod;
        } else {
            if (list_node_len(toMod) > index) {
                list_removeIndex(toMod, index);
            }
        }
    } else if (word_compare(type, "Type") == 0) {
        // needs list_select_remove
    } else if (word_compare(type, "Type&Value") == 0) {
        // needs list_select_remove
    } else {
        printf("Error: Option \"%s\" not found! Please only enter \"Index\", \"Type\" or \"Type&Value\".\n", type);
    }
    freeWordArr(wordArr, Teile);
}
void msh_command_main_modify_list() {
    char ** wordArr;
    int Teile = split(msh_Wert, ":", &wordArr);
    if (Teile != 3) {
        freeWordArr(wordArr, Teile);
        return;
    }
    char * name = wordArr[0];
    char * indexP = wordArr[1];
    unsigned int index = *indexP - 48;
    char * type = wordArr[2];
    char * value = wordArr[3];
    list toMod = msh_getListByName(name);
    if (toMod == NULL) {
        printf("Error: List \"%s\" not found!\n", name);
        freeWordArr(wordArr, Teile);
        return;
    }
    if (word_compare(indexP, "last") == 0) { index = list_node_len(toMod)-1; }
    if (index != 0) {
        toMod = list_seek(toMod, index);
    }
    if (word_compare(type, "Same") != 0) {
        if (word_compare(type, "Char") == 0) {
            toMod->type = Char;
        } else if (word_compare(type, "Integer") == 0) {
            toMod->type = Integer;
        } else if (word_compare(type, "Float") == 0) {
            toMod->type = Float;
        } else if (word_compare(type, "Double") == 0) {
            toMod->type = Double;
        } else if (word_compare(type, "String") == 0) {
            toMod->type = String;
        } else if (word_compare(type, "List") == 0) {
            toMod->type = List;
        }
    }
    switch (toMod->type) {
        case String: {
            char newValue[word_len((const char *) toMod->el) + word_len(value)];
            word_copy(newValue, value);
            replaceS(newValue, "Same", (const char *) toMod->el);
            toMod->el = (unsigned long long) realloc((void *) toMod->el, sizeof(char) * (word_len(newValue) + 1));
            word_copy((char *) toMod->el, newValue);
            break;
        }
        case Char: { toMod->el = (unsigned long long) value; break; }
        case Integer: {
            int * val = (int *) toMod->el;
            int len = intLen(*val) + 1;
            char intStr[len];
            intToString(*val, intStr);

            char newValue[len + word_len(value)];
            word_copy(newValue, value);
            replaceS(newValue, "Same", intStr);
            *val = (int) rechnen(newValue);
            break;
        }
        case Float: {
            float * val = (float *) toMod->el;
            int len = intLen((int) *val) + 8;
            char floatStr[len];
            doubleToString(*val, 6, floatStr);

            char newValue[len + word_len(value)];
            word_copy(newValue, value);
            replaceS(newValue, "Same", floatStr);
            *val = (float) rechnen(newValue);
            break;
        }
        case Double: {
            double * val = (double *) toMod->el;
            int len = intLen((int) *val) + 16;
            char doubleStr[len];
            doubleToString(*val, 15, doubleStr);

            char newValue[len + word_len(value)];
            word_copy(newValue, value);
            replaceS(newValue, "Same", doubleStr);
            *val = (double) rechnen(newValue);
            break;
        }
        case List: {

        }
        default: break;
    }
    freeWordArr(wordArr, Teile);
}
void msh_command_main_print_list() {
    list_print(msh_getListByName(msh_Wert), 0);
}
void msh_command_main_delete_list(msh_info * msh) {
    if (LIST_SPEICHER == NULL) {
        msh_error(msh, "Error: There are no lists!\n");
        return;
    }
    if ( word_compare((const char *) ((list) LIST_SPEICHER->el)->next->el , msh_Wert) == 0 ) {
        list after = LIST_SPEICHER->next;
        list_element_free(LIST_SPEICHER);
        LIST_SPEICHER = after;
    } else {
        list before = msh_getBeforeNodeByName(msh_Wert);
        if (before == NULL) {
            printf("Error: List \"%s\" not found!\n", msh_Wert);
            return;
        }
        list toDel = before->next;
        list after = toDel->next;
        list_free(toDel);
        before->next = after;
    }
}
void msh_command_main_print_list_SPEICHER(msh_info * msh) {
    if (LIST_SPEICHER == NULL) {
        msh_error(msh, "There are no lists!\n");
        return;
    }
    while (LIST_SPEICHER != NULL) {
        printf("%s ", (char *) ((list) LIST_SPEICHER->el)->next->el);
        LIST_SPEICHER = LIST_SPEICHER->next;
    }
    putchar('\n');
}