#include <xinu.h>
#include <prodcons.h>

void consumer(int32 count) {
  int32 i;
  for( i = 0; i <=count; i++){
    wait(consumed);
    printf("consumed : %d\n",n);
    signal(produced);
  }
}
