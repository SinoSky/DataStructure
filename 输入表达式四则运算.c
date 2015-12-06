#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INIT_SIZE 100//初始分配量
#define INCREMENT 10  //单次增加量
#define false 0
#define true 1

/*运算符栈*/
typedef struct {
	char * base;//用来存放栈元素的数组基址
	int size;//数组的最大容量
	int topIndex;//代表栈顶的数组下标
}OperatorStack;
	/
/*数值栈*/
typedef struct {
	double * base;
	int size;
	int topIndex;
}NumberStack;

/*函数声明*/
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
 * 初始化字符栈
 */
int initOp(OperatorStack * stack) {
	stack->size = INIT_SIZE;
	stack->base = (char *)malloc(stack->size * sizeof(char));
	if (stack->base == NULL) {
		printf("字符栈空间分配失败！\n");
		exit(-2);
	}
	stack->topIndex = -1;

	return 0;
}
	
/**
 * 初始化数字栈
 */
int init(NumberStack * stack) {
	stack->size = INIT_SIZE;
	stack->base = (double *)malloc(stack->size * sizeof(double));
	if (stack->base == NULL) {
		printf("数字栈空间分配失败！\n");
		exit(-2);
	}
	stack->topIndex = -1;

	return 0;
}

/**
 * 字符入栈操作
 */
int pushOp(OperatorStack *stack, char element) {
	
	if (stack->topIndex>=stack->size-1) {
		printf("字符栈已满，正在增加分配空间!\n");
		stack->size = stack->size + INCREMENT;
		stack->base = (char *)realloc(stack->base, (stack->size)*sizeof(char));
	}
	if (stack->base == NULL) {
		printf("增加字符栈空间失败！\n");
		exit(-2);
	}
	stack->topIndex++;
	stack->base[stack->topIndex] = element;

	return true;
}

/**
 * 数字入栈操作
 */
int push(NumberStack *stack, double element) {

	if (stack->topIndex >= stack->size - 1) {
		printf("数字栈已满,正在增加新空间！\n");
		stack->size = stack->size + INCREMENT;
		stack->base = (double *)realloc(stack->base, stack->size*sizeof(double));
	}
	if (stack->base == NULL) {
		printf("增加数字栈空间失败！\n");
		exit(-2);
	}
	stack->topIndex++;
	stack->base[stack->topIndex] = element;

	return true;
}

/**
 * 出字符栈操作
 */
int popOp(OperatorStack *stack) {
	if (stack->topIndex<0) {
		printf("字符栈中无元素可出！\n");
		return false;
	}
	stack->topIndex--;

	return true;
}
	
/**
 * 出数字栈操作
 */
int pop(NumberStack *stack) {
	if (stack->topIndex < 0) {
		printf("数字栈中无元素可出！\n");
		return false;
	}
	stack->topIndex--;

	return true;
}

/**
 * 返回字符栈顶元素
 */
char getTopOp(OperatorStack *stack) {
	if (stack->topIndex<0) {
		printf("字符栈顶为空\n");
		exit(-2);
	}
	return stack->base[stack->topIndex];
}

/**
 * 返回数字栈顶元素
 */
double getTop(NumberStack *stack) {
	if (stack->topIndex<0) {
		printf("数字栈顶为空\n");
		exit(-2);
	}
	return stack->base[stack->topIndex];
}

/**
 * 判断字符栈是否为空
 */
int isEmptyOp(OperatorStack * stack) {
	return stack->topIndex < 0;
}

/**
 * 判断数字栈是否为空
 */
int isEmpty(NumberStack * stack) {
	return stack->topIndex < 0;
}

/**
 * 判断是不是运算符
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
 * 判断是不是数字或者小数点
 */
int isDigit(char c) {
	return  (c >= '0' && c <= '9')||c=='.';
}


/**
 * 比较c1与c2的优先级
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
 * 三目运算
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
 * 对已知优先级的两个数进行运算，并从numStack中去掉这个数，从opStack中去掉这个运算符
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
	printf("请输入一段不含空格且正确的表达式：");
	scanf("%s", inputStr);

	int length = strlen(inputStr);
	int i = 0;
	while (i<length) {
		if (isDigit(inputStr[i])) {//如果是数字就入栈
			char *number=(char *)malloc(length*sizeof(char));
			int j = 0;
			while(isDigit(inputStr[i])){
				number[j] = inputStr[i];
				j++;
				i++;
			}
			push(&numStack, atof(number));
			for( ; j>0 ; j--){//清空number数组
				number[j] = ' ';
			}
		}
		else {//不是数字就比较优先级栈顶元素和正在读入的元素的优先级
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
	 * 遍历完输入的数字后运算可能没有完成
	 */
	while (!isEmptyOp(&opStack)) {
		calculate(&numStack, &opStack);
	}
	
	printf("\n%s",inputStr);
	printf(" = %.2f\n\n",numStack.base[numStack.topIndex]);

	return 0;
}