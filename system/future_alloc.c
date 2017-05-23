/* future_alloc.c */

#include <xinu.h>
#include <future.h>

typedef struct futent future;

future* future_alloc(int future_flag)
{
	future *new_future = NULL;
	if(future_flag == FUTURE_EXCLUSIVE)
	{
		new_future = (future*)getmem(sizeof(future));
		new_future->flag = FUTURE_EXCLUSIVE;
		new_future->state = FUTURE_EMPTY;
		new_future->value = (int*)getmem(sizeof(int));
		
	}

		     else if(future_flag == FUTURE_SHARED) {
		    new_future = (future*)getmem(sizeof(future));
		    new_future->flag = future_flag;
		    new_future->state = FUTURE_EMPTY;
		    new_future->value=(int*)getmem(sizeof (int32));
		    new_future->get_queue = constructqueue();
		  } else if(future_flag == FUTURE_QUEUE) {
		    new_future = (future*)getmem(sizeof(future));
		    new_future->flag = future_flag;
		    new_future->state = FUTURE_EMPTY;
		    new_future->value=(int*)getmem(sizeof (int32));
		    new_future->get_queue = constructqueue();
		    new_future->set_queue = constructqueue();
		  }

	return new_future;
}
