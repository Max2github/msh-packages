#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/words.h"
#include "../../../../mshgit/include/msh.h"
#include "../../../../mshgit/dependencies/std.h"
// #include "../../../include/alg.h"
// #include "../../../dependencies/words.h"
// #include "../../../include/msh.h"
// #include "../../../dependencies/std.h"

struct thread_list_el {
    pthread_t thread;
    superstring thread_arg;
    int id;
    struct thread_list_el * next;
};
typedef struct thread_list_el thread_list_el;
typedef thread_list_el * thread_list_el_pointer;
typedef thread_list_el * thread_list;

thread_list MSH_ASYNC_THREADS = NULL;
int MSH_ASYNC_MAX_ID = -1;

int msh_async_getThreadNum() {
    thread_list temp = MSH_ASYNC_THREADS;
    int i = 0;
    while (temp != NULL) {
        temp = temp->next;
        i++;
    }
    return i;
}

int msh_async_getFreeId() {
    int num = msh_async_getThreadNum();
    if (num == MSH_ASYNC_MAX_ID+1) { // if there are no free IDs
        MSH_ASYNC_MAX_ID++;
        return MSH_ASYNC_MAX_ID;
    }
    // check which IDs are already used
    thread_list temp = MSH_ASYNC_THREADS;
    int allFound[MSH_ASYNC_MAX_ID+1];
    for (int i = 0; i <= MSH_ASYNC_MAX_ID; i++) { allFound[i] = 0; } // init all with "not found"
    while (temp != NULL) {
        allFound[temp->id] = 1; // this ID was found
        temp = temp->next;
    }
    printIntArr(allFound, MSH_ASYNC_MAX_ID+1);
    // return the first ID that was not found
    for (int i = 0; i <= MSH_ASYNC_MAX_ID; i++) {
        if (allFound[i]) { return i; }
    }
    MSH_ASYNC_MAX_ID++;
    return MSH_ASYNC_MAX_ID;
}

int msh_async_addThread() {
    thread_list newHead = (thread_list) MSH_MALLOC(sizeof(thread_list_el));
    newHead->next = MSH_ASYNC_THREADS;
    newHead->id = msh_async_getFreeId();
    MSH_ASYNC_THREADS = newHead;
    return MSH_ASYNC_THREADS->id;
}

thread_list_el_pointer msh_async_getThread(int ID) {
    int i = 0;
    thread_list_el_pointer temp = MSH_ASYNC_THREADS;
    while (temp != NULL) {
        if (temp->id == ID) { return temp; }
        temp = temp->next;
    }
    return NULL;
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
        /* int rc = */ pthread_create(&t->thread, NULL, (void *) &msh_async_func_call, (void *) t->thread_arg);
        // word_copy(msh_Wert, "0");
        char ID[intLen(t->id)+1];
        intToString(t->id, ID);
        set_msh_Wert(ID);
    }
}