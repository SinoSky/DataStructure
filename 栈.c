#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OVERFLOW -2
#define ERROR 0

/*����ջ�ṹ��*/
typedef struct {
	char * base;//ջ�Ļ�ַ
	char * top;//ջ��ָ��
	int size;//ջ����
}OperatorStack;


/*��������*/
int init(OperatorStack *);
char getTop(OperatorStack *);
int push(OperatorStack *, char);
int pop(OperatorStack *, char *);


int main() {
	//vc6.0������Ҫ�ѱ������������ں���ǰ�档����
	OperatorStack operatorStack;//����ջ
	char element1 = ' ';//����һ��Ԫ��������Ŵ�ջ��ȡ������Ԫ��
	char *str = (char *)malloc(STACK_INIT_SIZE*sizeof(char));//����һ�������洢������ַ����������ָ��
	int length;//�ַ�����ʵ���е�Ԫ�ظ���
	int i;//ѭ������


	init(&operatorStack);
	printf("������һ��100λ���ڵ��ַ���\n");
	scanf("%s",str);
	length = strlen(str);
	for (i = 0;i<length;i++) {
		push(&operatorStack, str[i]);
	}
	printf("���δ�ջ�������ַ���\n");
	while (getTop(&operatorStack)) {
		pop(&operatorStack, &element1);
		printf("%c  ", element1);
	}
	printf("\n");
	return 0;
}

/**
* ��ʼ��ջ
*/
int init(OperatorStack * stack) {
	stack->base = (char *)malloc(STACK_INIT_SIZE * sizeof(char));
	if (stack->base == NULL) {
		printf("�ռ����ʧ�ܣ�\n");
		exit(OVERFLOW);
	}
	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;
	printf("��ʼ����ϣ�\n");

	return 0;
}

/**
* ����ջ��Ԫ��
*/
char getTop(OperatorStack *stack) {
	if (stack->base == stack->top) {
		return ERROR;
	}

	return *(stack->top - 1);
}

/**
* ��ջ����
*/
int push(OperatorStack *stack, char element) {
	if (stack->top - stack->base >= stack->size) {
		printf("�Ѿ������¿ռ䣡\n");
		stack->size = stack->size + STACKINCREMENT;
		stack->base = (char *)realloc(stack->base, (stack->size)*sizeof(int));
	}
	if (stack->base == NULL) {
		printf("���ӿռ�ʧ�ܣ�\n");
		exit(OVERFLOW);
	}
	*stack->top = element;
	stack->top++;

	return 0;
}

/**
* ��ջ����
*/
int pop(OperatorStack *stack, char * element) {
	if (stack->top == stack->base) {
		printf("ջ����Ԫ�ؿɳ���\n");
		return ERROR;
	}
	*element = *(stack->top - 1);
	stack->top--;

	return 0;
}

