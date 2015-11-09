#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
/*�������Ľṹ��*/
typedef struct Node{
	struct Node *next;
	int value;
}LNode,*LinkList;

/*��������*/
int create(LinkList,int);
int insert(LinkList,int,int);
int delete(LinkList,int,int *);
int locate(LinkList,int);

int main() {
	LinkList head= (LinkList)malloc(sizeof(LNode));//����ͷ���	
	/*��ʼ������*/
	create(head,10);
	
	/*�������*/
	insert(head, 3,100);
	
	/*ɾ������*/
	int element=0;
	delete(head,3,&element);
	printf("ɾ�����Ľ���ֵ��:%d\n",element);

	/*���Ҳ���*/
	printf("���ҵ�Ԫ��5����λ����%d\n", locate(head, 5));
	

	printf("\n");
	return 0;
}

/**
 * ��������num������һ��ͷ��������
 */
int create(LinkList head,int num) {
	head->next = NULL;
	for (int i = num; i > 0; i--){
		LNode *node = (LinkList)malloc(sizeof(LNode));//ÿ����ͷ����������һ���½ڵ�
		node->value = i;
		node->next = head->next;
		head->next = node;
	}
	printf("����������ϣ�\n");
	
	return 0;
}

/**
 * ��ͷ�����head�������в���elementԪ�ص�λ��position��
 */
int insert(LinkList head, int position, int element) {
	LinkList pointer = head;
	for (int i = 0; pointer!=NULL && i<position-1; i++){
		pointer = pointer->next;
	}
	LNode *newNode = (LinkList)malloc(sizeof(LNode));
	newNode->value = element;
	newNode->next = pointer->next;
	pointer->next = newNode;

	printf("������ϣ�\n");

	return 0;
}

/**
 * ��ͷ�����head��������ɾ��ָ��λ��position�Ľ�㣬����element������ֵ
 */
int delete(LinkList head,int position,int * element) {
	LinkList pointer = head;
	for (int i = 0; i < position-1 && pointer->next; i++){
		pointer = pointer->next;
	}
	LNode *deleteNode = pointer->next;
	pointer->next = deleteNode->next;
	*element=deleteNode->value;
	free(deleteNode);
	printf("ɾ���ɹ���\n");

	return 0;
}

/**
 * ��ͷ�����head�������в�����element��ȵ�Ԫ�ص�λ��
 */
int locate(LinkList head,int element) {
	LNode *pointer = head;
	for (int count= 1;pointer->next!=0; count++) {
		pointer = pointer->next;
		if (pointer->value == element){
			return count;
		}
	}
	return 0;
}