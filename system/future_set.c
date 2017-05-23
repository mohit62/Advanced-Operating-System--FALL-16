/* future_set */

#include <xinu.h>
#include <future.h>

syscall future_set(future *f, int *value)
{

	 if(f->flag == FUTURE_EXCLUSIVE || f->flag == FUTURE_SHARED) {
    if(f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING) {
      f->value = value;
      f->state = FUTURE_VALID;
      return OK;
    } else {
      return SYSERR;
    }
  } else if(f->flag == FUTURE_QUEUE) {
    if(isQueueEmpty(f->get_queue)) {
      enqueuepid(f->set_queue,getpid());
//printf("sus prod %d\n",getpid());
      suspend(getpid());
      f->value = value;
      return OK;
    } else {
      f->value = value;
      pid32 p_id = dequeuepid(f->get_queue);
//printf("res prod %d\n",p_id);
      resume(p_id);
      return OK;
    }
}
}
