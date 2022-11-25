#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../../mshgit/dependencies/std.h"
#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/include/msh.h"
#include "../../../../mshgit/dependencies/extern.h"

struct msh_async_thread_interface {
    superstring msh_arg;
    unsigned int id;
    msh_info * msh;
};
typedef struct msh_async_thread_interface msh_async_thread_interface;
typedef msh_async_thread_interface * msh_async_thread_interface_pointer;

struct thread_list_el {
    pthread_t thread;
    msh_async_thread_interface interface;
    struct thread_list_el * next;
};
typedef struct thread_list_el thread_list_el;
typedef thread_list_el * thread_list_el_pointer;
typedef thread_list_el * thread_list;

thread_list MSH_ASYNC_THREADS = NULL;
int MSH_ASYNC_MAX_ID = -1;

void msh_asysnc_on_exit() {
    while (MSH_ASYNC_THREADS != NULL) {
        pthread_join(MSH_ASYNC_THREADS->thread, NULL);
        thread_list_el_pointer toDel = MSH_ASYNC_THREADS;
        MSH_ASYNC_THREADS = MSH_ASYNC_THREADS->next;
        MSH_FREE(toDel);
    }
}

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
        allFound[temp->interface.id] = 1; // this ID was found
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
    newHead->interface.id = msh_async_getFreeId();
    MSH_ASYNC_THREADS = newHead;
    return MSH_ASYNC_THREADS->interface.id;
}

void msh_async_removeThread(int id) {
    thread_list temp = MSH_ASYNC_THREADS;
    thread_list beforeTemp = NULL;
    while (temp != NULL) {
        if (temp->interface.id == id) {
            if (beforeTemp == NULL) { MSH_ASYNC_THREADS = temp->next; }
            else { beforeTemp->next = temp->next; }
            MSH_FREE(temp);
        }
        beforeTemp = temp;
        temp = temp->next;
    }
}

thread_list_el_pointer msh_async_getThread(int ID) {
    int i = 0;
    thread_list_el_pointer temp = MSH_ASYNC_THREADS;
    while (temp != NULL) {
        if (temp->interface.id == ID) { return temp; }
        temp = temp->next;
    }
    return NULL;
}

void msh_async_func_call(void * arg) {
    msh_async_thread_interface_pointer interface = (msh_async_thread_interface_pointer) arg;

    char wertStr[s_len(interface->msh_arg)+1];
    s_stringify(interface->msh_arg, wertStr);
    s_free(interface->msh_arg);

    msh_info thread_info = MSH_INFO_DEFAULT;

    char name[20] = "thread ";
    intToString(interface->id, name + word_len(name));
    msh_func_deph_add_func(&thread_info, name);

    msh_func_call(&thread_info, wertStr);
}

// format
// async() <sep> IN <func> <sep> <callback func>
// async() <func>
void msh_command_main_async(msh_info * msh) {
    if (MSH_ASYNC_THREADS == NULL) {
        msh_add_on_exit(msh, msh_asysnc_on_exit);
    }
    if (find(msh_Wert, "IN")) {
        // handle IN
    } else {
        thread_list_el_pointer t = msh_async_getThread(msh_async_addThread());
        t->interface.msh_arg = s_init(msh_Wert);
        t->interface.msh = msh;
        /* int rc = */ pthread_create(&t->thread, NULL, (void *) &msh_async_func_call, (void *) &t->interface);
        // word_copy(msh_Wert, "0");
        char ID[intLen(t->interface.id)+1];
        intToString(t->interface.id, ID);
        set_msh_Wert(msh, ID);
    }
}