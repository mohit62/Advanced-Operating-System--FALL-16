/* Global variable for producer consumer */
 /* The declaration */
/* Semaphore Declarations */
#include <future.h>

extern int32 n;
extern sid32 produced,consumed;

/*function Prototype*/
void consumer(int32 count);
void producer(int32 count);

uint future_prod(future *fut);
uint future_cons(future *fut);
 



