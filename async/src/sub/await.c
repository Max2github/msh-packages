#include <pthread.h>


#include "../../../../mshgit/include/alg.h"
#include "../../../../mshgit/dependencies/std.h"
// #include "../../../include/alg.h"
// #include "../../../dependencies/std.h"

struct thread_list_el {
    pthread_t thread;
    int thread_arg;
    struct thread_list_el * next;
};
typedef struct thread_list_el thread_list_el;
typedef thread_list_el * thread_list_el_pointer;
typedef thread_list_el * thread_list;

extern thread_list MSH_ASYNC_THREADS;

int msh_async_addThread();
thread_list_el_pointer msh_async_getThread(int index);

void msh_command_sub_await() {
    int id = MSH_STRING_TO_INT(msh_Wert);
    thread_list_el_pointer t = msh_async_getThread(id);
    /* int rc = */ pthread_join(t->thread, NULL);
}