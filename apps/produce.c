#include <xinu.h>
#include <prodcons.h>

void producer(int32 count) {
  int32 i;
  for(i = 1; i <= count; i++){
    wait(produced);
    n=i;
    printf("produced : %d\n",n);
    signal(consumed);
	}
}





