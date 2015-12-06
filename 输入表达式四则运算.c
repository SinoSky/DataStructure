#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INIT_SIZE 100//��ʼ������
#define INCREMENT 10  //����������
#define false 0
#define true 1

/*�����ջ*/
typedef struct {
	char * base;//�������ջԪ�ص������ַ
	int size;//������������
	int topIndex;//����ջ���������±�
}OperatorStack;
	/
/*��ֵջ*/
typedef struct {
	double * base;
	int size;
	int topIndex;
}NumberStack;

/*��������*/
int init(NumberStack *);
int isEmpty(NumberStack *);
double getTop(NumberStack *);
int push(NumberStack *, double);
int pop(NumberStack *);

int initOp(OperatorStack *);
int isEmptyOp(OperatorStack *);
char getTopOp(OperatorStack *);
int pushOp(OperatorStack *, char);
int popOp(OperatorStack *);

char compareOpr(char, char);
int isOperator(char);
int calculate(NumberStack *,OperatorStack *);
int isDigit(char);

/**
 * ��ʼ���ַ�ջ
 */
int initOp(OperatorStack * stack) {
	stack->size = INIT_SIZE;
	stack->base = (char *)malloc(stack->size * sizeof(char));
	if (stack->base == NULL) {
		printf("�ַ�ջ�ռ����ʧ�ܣ�\n");
		exit(-2);
	}
	stack->topIndex = -1;

	return 0;
}
	
/**
 * ��ʼ������ջ
 */
int init(NumberStack * stack) {
	stack->size = INIT_SIZE;
	stack->base = (double *)malloc(stack->size * sizeof(double));
	if (stack->base == NULL) {
		printf("����ջ�ռ����ʧ�ܣ�\n");
		exit(-2);
	}
	stack->topIndex = -1;

	return 0;
}

/**
 * �ַ���ջ����
 */
int pushOp(OperatorStack *stack, char element) {
	
	if (stack->topIndex>=stack->size-1) {
		printf("�ַ�ջ�������������ӷ���ռ�!\n");
		stack->size = stack->size + INCREMENT;
		stack->base = (char *)realloc(stack->base, (stack->size)*sizeof(char));
	}
	if (stack->base == NULL) {
		printf("�����ַ�ջ�ռ�ʧ�ܣ�\n");
		exit(-2);
	}
	stack->topIndex++;
	stack->base[stack->topIndex] = element;

	return true;
}

/**
 * ������ջ����
 */
int push(NumberStack *stack, double element) {

	if (stack->topIndex >= stack->size - 1) {
		printf("����ջ����,���������¿ռ䣡\n");
		stack->size = stack->size + INCREMENT;
		stack->base = (double *)realloc(stack->base, stack->size*sizeof(double));
	}
	if (stack->base == NULL) {
		printf("��������ջ�ռ�ʧ�ܣ�\n");
		exit(-2);
	}
	stack->topIndex++;
	stack->base[stack->topIndex] = element;

	return true;
}

/**
 * ���ַ�ջ����
 */
int popOp(OperatorStack *stack) {
	if (stack->topIndex<0) {
		printf("�ַ�ջ����Ԫ�ؿɳ���\n");
		return false;
	}
	stack->topIndex--;

	return true;
}
	
/**
 * ������ջ����
 */
int pop(NumberStack *stack) {
	if (stack->topIndex < 0) {
		printf("����ջ����Ԫ�ؿɳ���\n");
		return false;
	}
	stack->topIndex--;

	return true;
}

/**
 * �����ַ�ջ��Ԫ��
 */
char getTopOp(OperatorStack *stack) {
	if (stack->topIndex<0) {
		printf("�ַ�ջ��Ϊ��\n");
		exit(-2);
	}
	return stack->base[stack->topIndex];
}

/**
 * ��������ջ��Ԫ��
 */
double getTop(NumberStack *stack) {
	if (stack->topIndex<0) {
		printf("����ջ��Ϊ��\n");
		exit(-2);
	}
	return stack->base[stack->topIndex];
}

/**
 * �ж��ַ�ջ�Ƿ�Ϊ��
 */
int isEmptyOp(OperatorStack * stack) {
	return stack->topIndex < 0;
}

/**
 * �ж�����ջ�Ƿ�Ϊ��
 */
int isEmpty(NumberStack * stack) {
	return stack->topIndex < 0;
}

/**
 * �ж��ǲ��������
 */
int isOperator(char c) {
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
		return 1;
	default:
		break;
	}

	return 0;
}

/**
 * �ж��ǲ������ֻ���С����
 */
int isDigit(char c) {
	return  (c >= '0' && c <= '9')||c=='.';
}


/**
 * �Ƚ�c1��c2�����ȼ�
 */
char compareOpr(char c1, char c2) {
	char result = '>';
		switch (c1)
		{
		case '+':
		case '-':
			if (c2 == '*' || c2 == '/' || c2 == '('){
				result = '<';
			}
			break;
		case ')':
		case '*':
		case '/':
			if (c2 == '('){
				result = '<';
			}
			break;
		case '(':
			if (c2 != ')'){
				result = '<';
			}else {
				result= '=';
			}
			break;
		default:
			break;
		}
		return result;
}

/**
 * ��Ŀ����
 */
double operate(char theta, double a, double b) {
	double value = 0;
		switch (theta){
		case '+':
			value = a + b; 
			break;
		case '-':
			value = b - a; 
			break;
		case '*':
			value = a * b; 
			break;
		case '/':
			value = b / a; 
			break;
		default:
			break;
		}
		return value;
}

/**
 * ����֪���ȼ����������������㣬����numStack��ȥ�����������opStack��ȥ����������
 */
int calculate(NumberStack *numStack, OperatorStack *opStack) {
	double a = getTop(numStack);
	pop(numStack);
	double b = getTop(numStack);
	pop(numStack);
	push(numStack,operate(getTopOp(opStack), a, b));
	popOp(opStack);

	return 0;
}

int main() {

	OperatorStack opStack;
	NumberStack numStack;
	initOp(&opStack);
	init(&numStack);

	char * inputStr=(char *)malloc(INIT_SIZE*sizeof(char));
	printf("������һ�β����ո�����ȷ�ı��ʽ��");
	scanf("%s", inputStr);

	int length = strlen(inputStr);
	int i = 0;
	while (i<length) {
		if (isDigit(inputStr[i])) {//��������־���ջ
			char *number=(char *)malloc(length*sizeof(char));
			int j = 0;
			while(isDigit(inputStr[i])){
				number[j] = inputStr[i];
				j++;
				i++;
			}
			push(&numStack, atof(number));
			for( ; j>0 ; j--){//���number����
				number[j] = ' ';
			}
		}
		else {//�������־ͱȽ����ȼ�ջ��Ԫ�غ����ڶ����Ԫ�ص����ȼ�
			if (isEmptyOp(&opStack) || compareOpr(getTopOp(&opStack),inputStr[i])=='<') {
				pushOp(&opStack,inputStr[i]);
				i++;
			}
			else if (compareOpr(getTopOp(&opStack), inputStr[i])=='=') {
				popOp(&opStack);
				i++;
			}
			else {
				calculate(&numStack, &opStack);
			}
		}
	}
	/**
	 * ��������������ֺ��������û�����
	 */
	while (!isEmptyOp(&opStack)) {
		calculate(&numStack, &opStack);
	}
	
	printf("\n%s",inputStr);
	printf(" = %.2f\n\n",numStack.base[numStack.topIndex]);

	return 0;
}