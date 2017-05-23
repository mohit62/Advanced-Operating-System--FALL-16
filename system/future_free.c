/* future_free.c */

#include <xinu.h>
#include <future.h>

syscall future_free(future* f)
{

  if(f->flag == FUTURE_SHARED) {
    freemem((char*)f->get_queue, sizeof(Queue));
  } else if(f->flag == FUTURE_QUEUE) {
    freemem((char*)f->get_queue, sizeof(Queue));
    freemem((char*)f->set_queue, sizeof(Queue));
  }
  freemem((char*)f->value, sizeof(int32));
  return freemem((char*)f, sizeof(future));
}
