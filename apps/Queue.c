#include <xinu.h>

Queue* constructqueue() 
{
	Queue *queue = (Queue*)getmem(sizeof(Queue));
  	if (queue == NULL) 
	{
    		return NULL;
  	}
  	queue->front = NULL;
  	queue->rear = NULL;
  	return queue;
}

void destructqueue(Queue *queue) 
{
	Node *node;
  	while (queue->front) 
	{
    		node = dequeuepid(queue);
    		freemem((char*)node,sizeof(Node));
  	}
  	freemem((char*)queue,sizeof(Queue));
}
int isQueueEmpty(Queue* q) {
  if(q->front == NULL) {
    return TRUE;
  }
  return FALSE;
}

void enqueuepid(Queue* q, pid32 x) {
  Node* temp = 
    (Node*)getmem(sizeof(Node));
  (*temp).val =x; 
  (*temp).next = NULL;
  if(q->front == NULL && q->rear == NULL){
    q->front = q->rear = temp;
    return;
  }
  (*q->rear).next = temp;
  q->rear = temp;
}

pid32 dequeuepid(Queue* q) {
  Node* temp = q->front;
  if(q->front == NULL) {
    return EMPTY;
  }
  if(q->front == q->rear) {
    q->front = q->rear = NULL;
  }
  else {
    q->front = (*q->front).next;
  }
  pid32 p_id = (*temp).val;
//printf("dequeing %d\n",p_id);
  freemem((char*)temp,sizeof(Node));
  return p_id;
}

