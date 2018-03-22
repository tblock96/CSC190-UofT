#include "queue.h"

struct Queue initQueue() {
	struct Queue q;
	q.currSize = 0;
	q.front = NULL; q.rear = NULL;
	return q;
}

void enqueue(struct Queue *qPtr, struct Data d) {
	struct Node *tmpN = malloc(sizeof(struct Node));
	tmpN->d=d;
	tmpN->next = NULL;
	if(qPtr->currSize==0) qPtr->front = tmpN;
	else qPtr->rear->next = tmpN;
	qPtr->rear = tmpN;
	qPtr->currSize++;
}

struct Data dequeue(struct Queue *qPtr) {
	if(qPtr->currSize) {
		struct Data tmpD = qPtr->front->d;
		struct Node *tmpN = qPtr->front;
		qPtr->front = tmpN->next;
		qPtr->currSize--;
		free(tmpN);
		return tmpD;
	}
}

void freeQueue(struct Queue *qPtr) {
	while(qPtr->currSize)
		dequeue(qPtr);
}
