#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../mshgit/include/alg.h"
#include "../../../mshgit/dependencies/words.h"
#include "../../../mshgit/include/msh.h"
#include "../../../mshgit/dependencies/std.h"
// #include "../../../include/alg.h"
// #include "../../../dependencies/words.h"
// #include "../../../include/msh.h"
// #include "../../../dependencies/std.h"

struct thread_list_el {
    pthread_t thread;
    superstring thread_arg;
    struct thread_list_el * next;
};
typedef struct thread_list_el thread_list_el;
typedef thread_list_el * thread_list_el_pointer;
typedef thread_list_el * thread_list;

thread_list MSH_ASYNC_THREADS = NULL;

int msh_async_addThread() {
    thread_list newHead = (thread_list) malloc(sizeof(thread_list_el));
    newHead->next = MSH_ASYNC_THREADS;
    MSH_ASYNC_THREADS = newHead;
}

thread_list_el_pointer msh_async_getThread(int index) {
    int i = 0;
    thread_list_el_pointer temp = MSH_ASYNC_THREADS;
    while (i < index) { temp = temp->next; i++; }
    return temp;
}

void msh_async_func_call(void * arg) {
    superstring wert = (superstring) arg;
    char wertStr[s_len(wert)+1];
    s_stringify(wert, wertStr);
    s_free(wert);
    msh_func_call(wertStr);
}

// format
// async() <sep> IN <func> <sep> <callback func>
// async() <func>
void msh_command_main_async() {
    if (find(msh_Wert, "IN")) {
        // handle IN
    } else {
        thread_list_el_pointer t = msh_async_getThread(msh_async_addThread());
        t->thread_arg = s_init(msh_Wert);
        /* int rc = */ pthread_create(&t->thread, NULL, (void *) &msh_async_func_call, (void *) &t->thread_arg);
        // word_copy(msh_Wert, "0");
        set_msh_Wert("0");
    }
}