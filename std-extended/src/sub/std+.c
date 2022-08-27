/* #include "../../../include/alg.h"
#include "../../../dependencies/words.h"
#include "../../../dependencies/std.h"
#include "../../../dependencies/mathe.h"

#include "../../cparts/command_def.h" */

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/words.h"
#include "../../../../mshgit/dependencies/std.h"
#include "../../../../mshgit/dependencies/mathe.h"

void msh_command_sub_array() {
    char ** array;
    int arrTeile = split(msh_Wert, "IN", &array);
    if (arrTeile > 0) {
        if(word_compare(array[1], "&/null//") == 0 || word_compare(array[1], "") == 0) {
            set_msh_Wert("&/null//&/arr//&/null//");
            return;
        };

        set_msh_Wert(array[1]);
        replaceS(msh_Wert, array[0], "&/arr//");

        if (find(msh_Wert, "&/arr//") == 0) {
            word_add(msh_Wert, "&/arr//&/null//");
        } else if (word_compare(msh_Wert, "&/arr//") == 0) {
            set_msh_Wert("&/null//&/arr//&/null//");
        } else {
            replaceS(msh_Wert, "&/arr//&/arr//", "&/arr//&/null//&/arr//");
        };
    };
    freeWordArr(array, arrTeile);
};
void msh_command_sub_object() {
    char ** object;
    int objTeile = split(msh_Wert, "IN", &object);
    if (objTeile > 0) {
        set_msh_Wert(object[1]);
        replaceS(msh_Wert, object[0], "&/obj//");
    }
    freeWordArr(object, objTeile);
};
void msh_command_sub_random() {
    char ** zahlen;
    int zahlTeile = split(msh_Wert, "&/arr//", &zahlen);
    int MIN = atoi(zahlen[0]);
    int MAX = atoi(zahlen[1]);
    int Komma = atoi(zahlen[2]);
    double r = Random(MIN, MAX, Komma);
    char sr[VAR_MAXCHAR];
    doubleToString(r, atoi(zahlen[2]), sr);

    set_msh_Wert(sr);
    freeWordArr(zahlen, zahlTeile);
};
void msh_command_sub_randomin() {
    char ** elems;
    int elemTeile = split(msh_Wert, "&/arr//", &elems);
    char arr[] = "0&/arr//%d&/arr//0";
    word_copy(arr, "0&/arr//");
    intToString(elemTeile, arr+8); // not very beautifull
    set_msh_Wert(arr);
    msh_command_sub_random();
    set_msh_Wert(elems[atoi(msh_Wert)]);
    freeWordArr(elems, elemTeile);
};
void msh_command_sub_row() {
    intToString(msh_Script_it, msh_Wert);
};
void msh_command_sub_ascii() {
    intToString((int) msh_Wert[0], msh_Wert);
};