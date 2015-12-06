#include<stdio.h>
#include<stdlib.h>				
#define ERROR 0
#define OVERFLOW -2				
#define LIST_INIT_SIZE 100	//��ʼ����ռ�����
#define LISTINCREMENT 10		//�������ӿռ�����

/*�������Ա�ṹ��*/
typedef struct {
	int * base;			//���Ա�Ĵ洢λ�õ���ʼ��ַ
	int length;			//��������Ԫ�صĸ���
	int listSize;		//�����Ա�ṹռ�õĴ洢�ռ�
}List;

/*��������*/
int init(List *);
int insert(List *list, int position, int element);
int delete(List *list, int position, int *element);
int locate(List *list,int element);
int travelList(List *list);


int main() {
	List list;
	/*��ʼ��*/
	init(&list);
	
	/*�������*/
	for (int i = 1; i <= 10; i++){
		insert(&list, i, i);
	}
	printf("��ʼֵ�ǣ�\n");
	travelList(&list);
	insert(&list, 2, 100);
	printf("�ڵڶ���λ�ò���100���ǣ�\n");
	travelList(&list);
	
	/*ɾ������*/
	int element = 0;
	delete(&list,2,&element);
	printf("\nɾ���ڶ���Ԫ��֮���ǣ�\n");
	travelList(&list);
	printf("��ɾ����ֵ��%d",element);
	
	/*����*/
	printf("\n\n���ҵ�Ԫ��3���ڵ�λ���ǣ�\n%d", locate(&list, 3));
	
	printf("\n");
	return 0;
}


/**
 * ��ʼ��һ�������Ա�list
 */
int init(List *list) {
	list->base = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (list->base==NULL){
		printf("malloc�����ڴ�ʧ�ܣ��������\n");
		exit(OVERFLOW);
	}
	list->length = 0;
	list->listSize = LIST_INIT_SIZE;
	printf("���Ա��ʼ�����\n");
	
	return 0;
}

/**
 * �����Ա�list�в���Ԫ��element��ָ��λ��positionǰ��
 */
int insert(List *list, int position, int element) {
	if (position < 1 || position > list->length + 1) {
		printf("�����λ�ò��Ϸ���\n");
		return ERROR;
	}
	if (list->length >= list->listSize) {
		int *newBase = (int *)realloc(list->base, (list->listSize + LISTINCREMENT)*sizeof(int));
		if (newBase == NULL) {
			printf("realloc�����ڴ�ʧ�ܣ��������\n");
			exit(OVERFLOW);
		}
		list->base = newBase;
		list->listSize += LISTINCREMENT;
	}

	int * insertPointer = &(list->base[position - 1]);	//���Ҫ����λ�õ�ָ��	
	/*Ҫ����λ�ü�������Ԫ��ȫ������һλ*/
	for (int * pointer = &(list->base[list->length - 1]); pointer >= insertPointer; pointer--) {
		*(pointer + 1) = *pointer;
	}
	*insertPointer = element;												
	list->length++;
	
	return 0;
}

/**
 * ɾ�����Ա�list��positionλ�õ�Ԫ�أ�����element������ֵ
 */
int delete(List *list, int position, int *element) {
	if (position<1 || position>list->length + 1) {
		printf("����λ�ò��Ϸ���");
		return ERROR;
	}
	int *detelePointer = &list->base[position - 1];
	*element = *detelePointer;
	int *pointer = &list->base[list->length - 1];
	for (detelePointer++; detelePointer <= pointer; detelePointer++) {
		*(detelePointer - 1) = *detelePointer;
	}
	list->length--;

	return 0;
}

/**
 * �������Ա�list��Ԫ��element��λ��
 */
int locate(List *list,int element) {
	for (int count = 0; count < list->length; count++) {
		if (list->base[count]==element){
			return count;
		}
	}

	return 0;
}

/**
 * �������Ա�list	
 */
int travelList(List *list) {
	if (list==NULL){
		printf("���������Ա�Ϊ��\n");
		return ERROR;
	}
	for (int i = 0; i < list->length; i++) {
		printf("%d ", list->base[i]);
	}
	printf("\n");
	return 0;
}
