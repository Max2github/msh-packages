#include <pthread.h>

#include "../../../../mshgit/dependencies/std.h"
#include "../../../../mshgit/include/alg.h"

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

extern thread_list MSH_ASYNC_THREADS;
extern int MSH_ASYNC_MAX_ID;

int msh_async_addThread();
thread_list_el_pointer msh_async_getThread(int index);
int msh_async_removeThread(int id);

void msh_command_sub_await(msh_info * msh) {
    int id = MSH_STRING_TO_INT(msh_Wert);
    thread_list_el_pointer t = msh_async_getThread(id);
    /* int rc = */ pthread_join(t->thread, NULL);
    msh_async_removeThread(id);
}