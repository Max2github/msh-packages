#include <pthread.h>
#include <stdlib.h>

#include "../../../mshgit/include/alg.h"
// #include "../../../include/alg.h"

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

void msh_command_sub_async() {
    int id = atoi(msh_Wert);
    thread_list_el_pointer t = msh_async_getThread(id);
    /* int rc = */ pthread_join(t->thread, NULL);
}