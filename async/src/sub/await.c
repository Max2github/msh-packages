#include <pthread.h>


#include "../../../../mshgit/dependencies/std.h"
#include "../../../../mshgit/include/alg.h"
// #include "../../../dependencies/std.h"
// #include "../../../include/alg.h"

struct thread_list_el {
    pthread_t thread;
    superstring thread_arg;
    int id;
    struct thread_list_el * next;
};
typedef struct thread_list_el thread_list_el;
typedef thread_list_el * thread_list_el_pointer;
typedef thread_list_el * thread_list;

extern thread_list MSH_ASYNC_THREADS;

int msh_async_addThread();
thread_list_el_pointer msh_async_getThread(int index);
int msh_async_removeThread(int id);

void msh_command_sub_await() {
    int id = MSH_STRING_TO_INT(msh_Wert);
    thread_list_el_pointer t = msh_async_getThread(id);
    /* int rc = */ pthread_join(t->thread, NULL);
    msh_async_removeThread(id);
}