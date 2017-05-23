/* future_get */

#include <xinu.h>
#include <future.h>

syscall future_get(future *f, int* value)
{

if(f->flag == FUTURE_EXCLUSIVE) {
    if(f->state == FUTURE_VALID) {
      f->state = FUTURE_EMPTY;
      *value = *f->value;
      return OK;
    } else if(f->state==FUTURE_EMPTY){
      f->state = FUTURE_WAITING;
      f->pid = getpid();       
       suspend(getpid());
      *value = *f->value;
     
      return OK;
    } else {
      return SYSERR;
    }
  } else if(f->flag == FUTURE_SHARED) {
    if(f->state == FUTURE_VALID) {
      *value = *f->value;
      return OK;
    } else {
      f->state = FUTURE_WAITING;
      enqueuepid(f->get_queue,getpid());
     suspend(getpid());
     *value = *f->value;
      return OK;
    
  }} else if(f->flag == FUTURE_QUEUE) {
    if(isQueueEmpty(f->set_queue)) {
      enqueuepid(f->get_queue,getpid());
      suspend(getpid());
//printf("sus cons %d\n",getpid());
      *value= *f->value;
      return OK;
    } else {
      pid32 p_id = dequeuepid(f->set_queue);
//printf("res cons %d\n",p_id);
      resume(p_id);
      f->pid=getpid();
      *value = *f->value;
      return OK;
    }
}
}
