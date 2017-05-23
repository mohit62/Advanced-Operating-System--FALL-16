#include <xinu.h>
#include<future.h>

uint future_prod(future *fut) 
{
	int i, j;
  j = (int)fut;
  for (i=0; i<1000; i++) {
    j += i;
  }
  int status = future_set(fut, &j);
  if(fut->flag == FUTURE_EXCLUSIVE) {
    resume(fut->pid);
  } else if (fut->flag == FUTURE_SHARED) {
    pid32 p_id;
    do{
      p_id = dequeuepid(fut->get_queue);
      resume(p_id);
    } while(p_id != EMPTY);
    fut->state = FUTURE_EMPTY;
  } else if(fut->flag == FUTURE_QUEUE) {
    pid32 pid = dequeuepid(fut->get_queue);
    if(pid == EMPTY) {
      return SYSERR;
    }
    resume(pid);
  }
return OK;
}
