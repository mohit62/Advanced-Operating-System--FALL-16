#include <xinu.h>
#include<future.h>
#include <prodcons.h>

/*definition of global variable n */
/* Now global variable will be on the heap and will be accessible to all processes i.e producer
     and the consumer */
int n;

sid32 produced, consumed;
 
//sid32 produced,consumed;
shellcmd xsh_prodcons(int32 nargs, char *args[])
{
	

	/* Arguments checking */
	if(nargs == 2 && strcmp(args[1],"-f")==0)
	{
             	//future *f1, *f2, *f3;
		future *f_exclusive, *f_shared, *f_queue;
             	/*f1 = future_alloc(FUTURE_EXCLUSIVE);
             	f2 = future_alloc(FUTURE_EXCLUSIVE);
             	f3 = future_alloc(FUTURE_EXCLUSIVE);*/
             
             	f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
             	f_shared = future_alloc(FUTURE_SHARED);
             	f_queue = future_alloc(FUTURE_QUEUE);

             
 
           	/* resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
            	resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
            	resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
            	resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
            	resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
            	resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
            	future_free(f1);
            	future_free(f2);
            	future_free(f3);*/
           
            	// Test FUTURE_EXCLUSIVE
            	resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive));
            	resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );

           	// Test FUTURE_SHARED
  	    	resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
  	    	resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
            	resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
	    	resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
	    	resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

		// Test FUTURE_QUEUE
	   	resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
	   	resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
	   	resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
	   	resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
	   	resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
	   	resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
	   	resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
           	resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
            
          
          	future_free(f_exclusive);
          	future_free(f_shared);
	  	future_free(f_queue);
	}
	else if(nargs<=2)
	{
          	int32 count = 2000;		//Local variable to hold count

          	if(nargs  == 2)
		{
	  		count = atoi(args[1]);
  
         	}

           	produced = semcreate(0);
  	   	consumed = semcreate(1);
           	resume( create(producer, 1024, 20, "producer", 1, count));
	   	resume( create(consumer, 1024, 20, "consumer", 1, count));
           
	}	
        else 
	{
        	fprintf(stderr, "Sorry! Too many arguments. \n");
	
        }

	return(0);
}
