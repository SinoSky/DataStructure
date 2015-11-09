#include <stdio.h>
#include <stdlib.h>
#define INIT_LENGTH 10  //初始长度
#define INCREMENT 5		//每次增加长度

/**
 * 定义队列结构体，用int *data和length构建动态长度int数组
 */
typedef struct{
	int *data;
	int head, tail, length;
}Queue;

/**
 * 函数声明
 */
int initQueue(Queue * queue, int length);
void push(Queue * queue, int element);
void output(Queue * queue);
int front(Queue * queue);
void pop(Queue * queue);
int isEmptyQueue(Queue * queue);
int isFullQueue(Queue * queue);

/**
 * 初始化队列queue的长度为length
 */
int initQueue(Queue * queue,int length) {
	queue->data = malloc(sizeof(int)*length);
	if (queue->data==NULL){
		printf("队列空间分配失败");
	}
	queue->length = length;
	queue->head = 0;
	queue->tail = -1;

	return 0;
}

/**
 * 向队列queue的队尾插入元素element
 */
void push(Queue * queue,int element) {
	if (isFullQueue(queue)) {
		printf("队列已满，正在增加新空间。。。\n");
		queue->length =queue->length+INCREMENT;
		queue->data = realloc(queue->data, sizeof(int) * queue->length);
	}
	queue->tail++;
	queue->data[queue->tail] = element;
}

/**
 * 输出队列queue的所有元素
 */
void output(Queue * queue) {
	printf("现在队列里的所有元素是：");
	for (int i = queue->head; i <= queue->tail; i++) {
		printf ("%d ", queue->data[i] );
	}
	printf("\n");
}

/**
 * 返回队列queue的队首元素
 */
int front(Queue * queue) {
	if(!isEmptyQueue(queue)){
		return queue->data[queue->head];
	}else{
		printf("队列为空队列！\n");
	}

	return 0;
}

/**
 * 队列queue的队首元素出列
 */
void pop(Queue * queue) {
	if(!isEmptyQueue(queue)){
		queue->head++;
		printf("队首元素出列！\n");
	}else{
		printf("这是个空队列！\n");
	}
}

/**
 * 判断队列queue是不是空队列
 */
int isEmptyQueue(Queue * queue) {
	return queue->head > queue->tail;
}

/**
 * 判断队列queue是不是满了
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
	printf ("现在队首元素是：%d\n", front(&queue));
	pop(&queue);
	output(&queue);
	
	return 0;
}

