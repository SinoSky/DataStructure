#include<stdio.h>
#include<stdlib.h>				
#define ERROR 0
#define OVERFLOW -2				
#define LIST_INIT_SIZE 100	//初始分配空间容量
#define LISTINCREMENT 10		//单次增加空间容量

/*构造线性表结构体*/
typedef struct {
	int * base;			//线性表的存储位置的起始地址
	int length;			//表中已有元素的个数
	int listSize;		//该线性表结构占用的存储空间
}List;

/*函数声明*/
int init(List *);
int insert(List *list, int position, int element);
int delete(List *list, int position, int *element);
int locate(List *list,int element);
int travelList(List *list);


int main() {
	List list;
	/*初始化*/
	init(&list);
	
	/*插入操作*/
	for (int i = 1; i <= 10; i++){
		insert(&list, i, i);
	}
	printf("初始值是：\n");
	travelList(&list);
	insert(&list, 2, 100);
	printf("在第二个位置插入100后是：\n");
	travelList(&list);
	
	/*删除操作*/
	int element = 0;
	delete(&list,2,&element);
	printf("\n删除第二个元素之后是：\n");
	travelList(&list);
	printf("被删除的值是%d",element);
	
	/*查找*/
	printf("\n\n查找到元素3所在的位置是：\n%d", locate(&list, 3));
	
	printf("\n");
	return 0;
}


/**
 * 初始化一个空线性表list
 */
int init(List *list) {
	list->base = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
	if (list->base==NULL){
		printf("malloc分配内存失败，程序结束\n");
		exit(OVERFLOW);
	}
	list->length = 0;
	list->listSize = LIST_INIT_SIZE;
	printf("线性表初始化完毕\n");
	
	return 0;
}

/**
 * 向线性表list中插入元素element到指定位置position前面
 */
int insert(List *list, int position, int element) {
	if (position < 1 || position > list->length + 1) {
		printf("插入的位置不合法！\n");
		return ERROR;
	}
	if (list->length >= list->listSize) {
		int *newBase = (int *)realloc(list->base, (list->listSize + LISTINCREMENT)*sizeof(int));
		if (newBase == NULL) {
			printf("realloc分配内存失败，程序结束\n");
			exit(OVERFLOW);
		}
		list->base = newBase;
		list->listSize += LISTINCREMENT;
	}

	int * insertPointer = &(list->base[position - 1]);	//获得要插入位置的指针	
	/*要插入位置及其后面的元素全部后移一位*/
	for (int * pointer = &(list->base[list->length - 1]); pointer >= insertPointer; pointer--) {
		*(pointer + 1) = *pointer;
	}
	*insertPointer = element;												
	list->length++;
	
	return 0;
}

/**
 * 删除线性表list中position位置的元素，并用element返回其值
 */
int delete(List *list, int position, int *element) {
	if (position<1 || position>list->length + 1) {
		printf("输入位置不合法！");
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
 * 返回线性表list中元素element的位置
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
 * 遍历线性表list	
 */
int travelList(List *list) {
	if (list==NULL){
		printf("遍历的线性表为空\n");
		return ERROR;
	}
	for (int i = 0; i < list->length; i++) {
		printf("%d ", list->base[i]);
	}
	printf("\n");
	return 0;
}
