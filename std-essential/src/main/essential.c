/* #include "../../../dependencies/std.h"
#include "../../../include/alg.h"
#include "../../../include/msh.h"
#include "../../../dependencies/words.h" */

#include "../../../../mshgit/dependencies/std.h"
#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/include/msh.h"
#include "../../../../mshgit/dependencies/words.h"

void msh_command_main_display(msh_info * msh) {
    if (find(msh_Wert, "&/ref//")) {
        MSH_PRINTF(">> ");
        char ** withRef;
        int anzahlSpl = split(msh_Wert, "&/ref//", &withRef);
        for (int i = 0; i <= anzahlSpl; i++) {
            if (i % 2 /* == 1 */) { // each second is a reference - begins with 0
                superstring tempS = s_init(withRef[i]);
                MSH_PRINTF("%s", (char *) msh_ref_get(msh, (index64) tempS));
                s_free(tempS);
                continue;
            }
            MSH_PRINTF("%s", withRef[i]);
        }
        MSH_PRINTF("\n");
        freeWordArr(withRef, anzahlSpl);
        return;
    }

    if (find(msh_Wert, "&/arr//") != 0) {
        replaceS(msh_Wert, "&/arr//", "\n     ");
        MSH_PRINTF(">> [\n     %s\n   ]\n", msh_Wert);
    } else if (find(msh_Wert, "&/obj//") != 0) {
        // printf("%s\n", VAR_SPEICHER[0]);
        replaceS(msh_Wert, "&/obj//", "\n     ");
        MSH_PRINTF(">> {\n     %s\n   }\n", msh_Wert);
    } else {
        MSH_PRINTF(">> %s\n", msh_Wert);
    };
};
void msh_command_main_print(msh_info * msh) {
    if (find(msh_Wert, "&/arr//") != 0) {
        MSH_PRINTF("!! ERROR at line %d : Cannot \"print()\" variable of type \"Array\"!", msh_Script_it + 1);
    } else if (find(msh_Wert, "&/obj//") != 0) {
        MSH_PRINTF("!! ERROR at line %d : Cannot \"print()\" variable of type \"object\"!", msh_Script_it + 1);
    } else {
        replaceS(msh_Wert, "\\n", "\n");
        MSH_PRINTF("%s", msh_Wert);
    };
};
void msh_command_main_stop(msh_info * msh) {
    msh_STOP = 1;
};
void msh_command_main_del(msh_info * msh) {
    char var[VAR_MAXCHAR];
    int index = msh_get_Var(msh_Wert, var);
    if (index == -1) {
        char text[] = "Variable &/var// does not exist!";
        replaceS(text, "&/var//", msh_Wert);
        // word_copy(msh_Wert, text);
        set_msh_Wert(text);
    } else {
        for (int i = index; i < VAR_WORTZAELER-1; i++) {
            word_copy(VAR_NAMES[i], VAR_NAMES[i+1]);
            word_copy(VAR_SPEICHER[i], VAR_SPEICHER[i+1]);
        }
        VAR_NAMES[VAR_WORTZAELER-1][0] = '\0';
        VAR_WORTZAELER--;
    };
};
void msh_command_main_call(msh_info * msh) {
    msh_func_call(msh, msh_Wert);
};
void msh_command_main_goto(msh_info * msh) {
    int ln = MSH_STRING_TO_INT(msh_Wert);
    msh_Script_it = ln - 1;
    msh->info.line = ln;
};