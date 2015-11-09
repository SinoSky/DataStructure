#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OVERFLOW -2
#define ERROR 0

/*定义栈结构体*/
typedef struct{
	char * base;//栈的基址
	char * top;//栈顶指针
	int size;//栈容量
}OperatorStack;


/*函数声明*/
int init(OperatorStack *);
char getTop(OperatorStack *);
int push(OperatorStack *,char);
int pop(OperatorStack *,char *);


int main() {
	OperatorStack operatorStack;

	init(&operatorStack);
	push(&operatorStack, '#');


	char element1 = ' ';
	printf("请输入一串字符，以#结束：\n");
	char character = getchar();
	while (character!='#'||getTop(&operatorStack)!='#'){
				push(&operatorStack, character);
				character = getchar();
				printf("%c ", getTop(&operatorStack));
				pop(&operatorStack, &element1);
				printf("%c \n", element1);
	}

	printf("\n");
	return 0;
}

/**
 * 初始化栈
 */
int init(OperatorStack * stack) {
	stack->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if (stack->base == NULL){
		printf("空间分配失败！\n");
		exit(OVERFLOW);
	}
	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;
	printf("初始化完毕！\n");
	
	return 0;
}

/**
 * 返回栈顶元素
 */
char getTop(OperatorStack *stack) {
	if (stack->base == stack->top){
		printf("不能从空栈中取元素");
		return ERROR;
	}

	return *(stack->top - 1);
}

/**
 * 入栈操作
 */
int push(OperatorStack *stack,char element) {
	if (stack->top - stack->base >= stack->size) {
		printf("已经增加新空间！\n");
		stack->size = stack->size + STACKINCREMENT;
		stack->base = (char *)realloc(stack->base, (stack->size)*sizeof(int));
	}
	if (stack->base == NULL) {
		printf("增加空间失败！\n");
		exit(OVERFLOW);
	}
	*stack->top = element;
	stack->top++;

	return 0;
}

/**
 * 出栈操作
 */
int pop(OperatorStack *stack,char * element) {
	if (stack->top==stack->base){
		printf("栈中无元素可出！\n");
		return ERROR;
	}
	*element = *(stack->top-1);
	stack->top--;
	
	return 0;
}

