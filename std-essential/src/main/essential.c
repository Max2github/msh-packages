#include "../../../../mshgit/dependencies/std.h"

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/include/msh.h"

#include "../../../../mshgit/dependencies/extern.h"

void msh_command_main_display(msh_info* msh) {
    char* wert = get_msh_Wert(msh);

    if (find(msh_Wert, MSH_REF_STRING_SEPARATOR)) {
        MSH_MUTEX_LOCK(MSH_PRINT_MUTEX);
        MSH_PRINTF_NO_FLUSH(msh, ">> ");

        word_picker_array arr = msh_ref_string_split(wert);
        for (int i = 0; i < arr.written; i++) {
            word_picker w = WORD_PICKER_ARRAY_GET(arr, i);
            if (i % 2 /* == 1 */) { // each second is a reference - begins with 0
                index32 ref_id = msh_ref_id_from_string(w.begin, word_picker_len(w));
                word_picker data = msh_ref_get_data_as_string(msh, ref_id);
                MSH_PRINTF_NO_FLUSH(msh, "%.*s", word_picker_len(data), data.begin);
                continue;
            }
            while (w.begin < w.end) {
                MSH_PUTCHAR_NO_FLUSH(msh, *(w.begin));
            }
        }
        MSH_PRINTF_NO_FLUSH(msh, "\n");
        msh_flush(msh);
        MSH_MUTEX_UNLOCK(MSH_PRINT_MUTEX);
        return;
    }

    if (find(wert, "&/arr//") != 0) {
        replaceS(wert, "&/arr//", "\n     ");
        MSH_MUTEX_LOCK(MSH_PRINT_MUTEX);
        MSH_PRINTF(msh, ">> [\n     %s\n   ]\n", wert);
        MSH_MUTEX_UNLOCK(MSH_PRINT_MUTEX);
    }
    else if (find(wert, "&/obj//") != 0) {
        replaceS(wert, "&/obj//", "\n     ");
        MSH_MUTEX_LOCK(MSH_PRINT_MUTEX);
        MSH_PRINTF(msh, ">> {\n     %s\n   }\n", wert);
        MSH_MUTEX_UNLOCK(MSH_PRINT_MUTEX);
    }
    else {
        MSH_MUTEX_LOCK(MSH_PRINT_MUTEX);
        MSH_PRINTF(msh, ">> %s\n", wert);
        MSH_MUTEX_UNLOCK(MSH_PRINT_MUTEX);
    };
};
void msh_command_main_print(msh_info* msh) {
    char* wert = get_msh_Wert(msh);

    if (find(wert, "&/arr//") != 0) {
        msh_error(msh, "Cannot \"print()\" variable of type \"array\"!");
    }
    else if (find(wert, "&/obj//") != 0) {
        msh_error(msh, "Cannot \"print()\" variable of type \"object\"!");
    }
    else {
        replaceS(wert, "\\n", "\n");
        MSH_MUTEX_LOCK(MSH_PRINT_MUTEX);
        MSH_PRINTF(msh, "%s", wert);
        MSH_MUTEX_UNLOCK(MSH_PRINT_MUTEX);
    };
};
void msh_command_main_stop(msh_info* msh) {
    msh->event.stop = true;
};
void msh_command_main_del(msh_info* msh) {
    char* wert = get_msh_Wert(msh);

    // char var[VAR_MAXCHAR];
    // int index = msh_get_Var(wert, var);
    int index = msh_var_getIndexByName(msh, wert);
    if (index == -1) {
        char text[] = "Variable &/var// does not exist!";
        replaceS(text, "&/var//", wert);
        set_msh_Wert(msh, text);
    }
    else {
        for (int i = index; i < VAR_WORTZAELER - 1; i++) {
            // cannot be done with msh_var_update ..., because we need to change the name too..
            word_copy(VAR_NAMES[i], VAR_NAMES[i + 1]);
            word_copy(VAR_SPEICHER[i], VAR_SPEICHER[i + 1]);
        }
        VAR_NAMES[VAR_WORTZAELER - 1][0] = '\0';
        VAR_WORTZAELER--;
    };
};
void msh_command_main_call(msh_info* msh) {
    msh_func_call(msh, get_msh_Wert(msh));
};
void msh_command_main_goto(msh_info* msh) {
    int ln = MSH_STRING_TO_INT(get_msh_Wert(msh));
    msh->info.line = ln;
};