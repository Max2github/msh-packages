#include "../../../../mshgit/dependencies/std.h"

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/extern.h"

// this will include all other commands in this package
#include "../../../../mshgit/src/cparts/command_def.h"

void msh_command_sub_input(msh_info * msh) {
    char * wert = get_msh_Wert(msh);

    msh_command_main_print(msh); // will print msh_Wert
    // scanf(" %s", msh_Wert);
    // fgets(msh_Wert, VAR_MAXCHAR-1, stdin); // this could cause problems
    // char * temp; size_t len = 0;
    // getline(&temp, &len, stdin); word_copy(msh_Wert, temp); free(temp);
    char * wertP = wert;
    char now = 'n';
    while(now != '\n') { *wertP = getchar(); now = *wertP; wertP++; }
    *wertP = '\0';
    replaceS(wert, "\n", "");
    replaceS(wert, "=", "&/equals//");
};
void msh_command_sub_math(msh_info * msh) {
    char * wert = get_msh_Wert(msh);

    double erg = rechnen(wert);
    // Kommastellen mit 0 am Ende entfernen
    char newWert[VAR_MAXCHAR];
    char repl[VAR_MAXCHAR];
    int neg = 0;
    if (erg < 0) {
        erg *= -1;
        neg = 1;
    }
    doubleToString(erg, 6, newWert);
    intToString((int) erg, repl);
    replaceS(newWert, repl, "");
    int last = word_len(newWert)-1;
    while (newWert[last] == '0') {
        newWert[last] = '\0';
        last--;
    };
    if (last == 0) {
        newWert[0] = '\0';
    };
    char * nWertP = wert;
    if (neg) {
        set_msh_Wert(msh, "-");
        nWertP++;
    }
    word_copy(nWertP, repl);
    if (word_len(newWert) > 0) {
        word_add(nWertP, newWert);
    }
};