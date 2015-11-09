#include <stdio.h>
#include <stdlib.h>
#define INIT_LENGTH 10  //��ʼ����
#define INCREMENT 5		//ÿ�����ӳ���

/**
 * ������нṹ�壬��int *data��length������̬����int����
 */
typedef struct{
	int *data;
	int head, tail, length;
}Queue;

/**
 * ��������
 */
int initQueue(Queue * queue, int length);
void push(Queue * queue, int element);
void output(Queue * queue);
int front(Queue * queue);
void pop(Queue * queue);
int isEmptyQueue(Queue * queue);
int isFullQueue(Queue * queue);

/**
 * ��ʼ������queue�ĳ���Ϊlength
 */
int initQueue(Queue * queue,int length) {
	queue->data = malloc(sizeof(int)*length);
	if (queue->data==NULL){
		printf("���пռ����ʧ��");
	}
	queue->length = length;
	queue->head = 0;
	queue->tail = -1;

	return 0;
}

/**
 * �����queue�Ķ�β����Ԫ��element
 */
void push(Queue * queue,int element) {
	if (isFullQueue(queue)) {
		printf("�������������������¿ռ䡣����\n");
		queue->length =queue->length+INCREMENT;
		queue->data = realloc(queue->data, sizeof(int) * queue->length);
	}
	queue->tail++;
	queue->data[queue->tail] = element;
}

/**
 * �������queue������Ԫ��
 */
void output(Queue * queue) {
	printf("���ڶ����������Ԫ���ǣ�");
	for (int i = queue->head; i <= queue->tail; i++) {
		printf ("%d ", queue->data[i] );
	}
	printf("\n");
}

/**
 * ���ض���queue�Ķ���Ԫ��
 */
int front(Queue * queue) {
	if(!isEmptyQueue(queue)){
		return queue->data[queue->head];
	}else{
		printf("����Ϊ�ն��У�\n");
	}

	return 0;
}

/**
 * ����queue�Ķ���Ԫ�س���
 */
void pop(Queue * queue) {
	if(!isEmptyQueue(queue)){
		queue->head++;
		printf("����Ԫ�س��У�\n");
	}else{
		printf("���Ǹ��ն��У�\n");
	}
}

/**
 * �ж϶���queue�ǲ��ǿն���
 */
int isEmptyQueue(Queue * queue) {
	return queue->head > queue->tail;
}

/**
 * �ж϶���queue�ǲ�������
 */
int isFullQueue(Queue * queue) {
	return queue->tail +1>= queue->length;
}

int main() {
	Queue queue;
	initQueue(&queue,INIT_LENGTH);

	for (int i = 1; i <= 10; i++) {
		push(&queue,i);
	}
	output(&queue);
	printf ("���ڶ���Ԫ���ǣ�%d\n", front(&queue));
	pop(&queue);
	output(&queue);
	
	return 0;
}

