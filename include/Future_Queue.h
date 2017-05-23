typedef struct Node {
  pid32 val;
  struct Node* next;
} Node;

typedef struct Queue {
  Node* front;
  Node* rear;
} Queue;