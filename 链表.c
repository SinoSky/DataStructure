#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
/*声明结点的结构体*/
typedef struct Node{
	struct Node *next;
	int value;
}LNode,*LinkList;

/*函数声明*/
int create(LinkList,int);
int insert(LinkList,int,int);
int delete(LinkList,int,int *);
int locate(LinkList,int);

int main() {
	LinkList head= (LinkList)malloc(sizeof(LNode));//生成头结点	
	/*初始化操作*/
	create(head,10);
	
	/*插入操作*/
	insert(head, 3,100);
	
	/*删除操作*/
	int element=0;
	delete(head,3,&element);
	printf("删除掉的结点的值是:%d\n",element);

	/*查找操作*/
	printf("查找到元素5所在位置是%d\n", locate(head, 5));
	

	printf("\n");
	return 0;
}

/**
 * 创建带有num个结点和一个头结点的链表
 */
int create(LinkList head,int num) {
	head->next = NULL;
	for (int i = num; i > 0; i--){
		LNode *node = (LinkList)malloc(sizeof(LNode));//每次在头结点后面生成一个新节点
		node->value = i;
		node->next = head->next;
		head->next = node;
	}
	printf("创建链表完毕！\n");
	
	return 0;
}

/**
 * 在头结点是head的链表中插入element元素到位置position上
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

	printf("插入完毕！\n");

	return 0;
}

/**
 * 在头结点是head的链表中删除指定位置position的结点，并用element返回其值
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
	printf("删除成功！\n");

	return 0;
}

/**
 * 在头结点是head的链表中查找与element相等的元素的位置
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