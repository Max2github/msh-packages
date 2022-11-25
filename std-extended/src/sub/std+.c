/* #include "../../../include/alg.h"
#include "../../../dependencies/words.h"
#include "../../../dependencies/std.h"
#include "../../../dependencies/mathe.h"

#include "../../cparts/command_def.h" */

#include "../../../../mshgit/dependencies/std.h"

#include "../../../../mshgit/include/alg.h"

#include "../../../../mshgit/dependencies/extern.h"

void msh_command_sub_array(msh_info * msh) {
    char * wert = get_msh_Wert(msh);

    char ** array;
    int arrTeile = split(wert, "IN", &array);
    if (arrTeile > 0) {
        if(word_compare(array[1], "&/null//") == 0 || word_compare(array[1], "") == 0) {
            set_msh_Wert(msh, "&/null//&/arr//&/null//");
            return;
        };

        set_msh_Wert(msh, array[1]);
        replaceS(wert, array[0], "&/arr//");

        if (find(wert, "&/arr//") == 0) {
            word_add(wert, "&/arr//&/null//");
        } else if (word_compare(wert, "&/arr//") == 0) {
            set_msh_Wert(msh, "&/null//&/arr//&/null//");
        } else {
            replaceS(wert, "&/arr//&/arr//", "&/arr//&/null//&/arr//");
        };
    };
    freeWordArr(array, arrTeile);
};
void msh_command_sub_object(msh_info * msh) {
    char * wert = get_msh_Wert(msh);

    char ** object;
    int objTeile = split(wert, "IN", &object);
    if (objTeile > 0) {
        set_msh_Wert(msh, object[1]);
        replaceS(wert, object[0], "&/obj//");
    }
    freeWordArr(object, objTeile);
};
void msh_command_sub_random(msh_info * msh) {
    char ** zahlen;
    int zahlTeile = split(get_msh_Wert(msh), "&/arr//", &zahlen);
    int MIN = atoi(zahlen[0]);
    int MAX = atoi(zahlen[1]);
    int Komma = atoi(zahlen[2]);
    double r = Random(MIN, MAX, Komma);
    char sr[VAR_MAXCHAR];
    doubleToString(r, atoi(zahlen[2]), sr);

    set_msh_Wert(msh, sr);
    freeWordArr(zahlen, zahlTeile);
};
void msh_command_sub_randomin(msh_info * msh) {
    const char * wert = get_msh_Wert(msh);

    char ** elems;
    int elemTeile = split(wert, "&/arr//", &elems);
    char arr[] = "0&/arr//%d&/arr//0";
    word_copy(arr, "0&/arr//");
    intToString(elemTeile, arr+8); // not very beautifull
    set_msh_Wert(msh, arr);
    msh_command_sub_random(msh);
    set_msh_Wert(msh, elems[atoi(wert)]);
    freeWordArr(elems, elemTeile);
};
void msh_command_sub_row(msh_info * msh) {
    intToString(msh->info.line, get_msh_Wert(msh));
};
void msh_command_sub_ascii(msh_info * msh) {
    intToString((int) msh_Wert[0], get_msh_Wert(msh));
};