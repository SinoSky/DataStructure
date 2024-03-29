#include<stdio.h>
#include<stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW    -1

#define STACK_INIT_SIZE     100
#define STACK_INCREMENT      10
/**
 * 定义二叉树的结点
 */
typedef struct Node {
    char data;                  // 结点数据
    struct Node *lChild;        // 左孩子
    struct Node *rChild;        // 右孩子
} Node, *BinaryTree;

/**
 * 定义栈结构
 */
typedef struct {
    BinaryTree *base;
    BinaryTree *top;
    int stackSize;
} Stack;

/**
 * 函数声明
 */
int initStack(Stack *stack);

int destroyStack(Stack *stack);

int isStackEmpty(Stack stack);

int getTop(Stack stack, BinaryTree *node);

int push(Stack *stack, BinaryTree node);

int pop(Stack *stack, BinaryTree *node);

BinaryTree createBinaryTree(BinaryTree node);

int preOrderTraverse(BinaryTree tree);

int inOrderTraverse(BinaryTree tree);

int postOrderTraverse(BinaryTree tree);

int preOrderStackTraverse(BinaryTree tree);

int inOrderStackTraverse(BinaryTree tree);

int postOrderStackTraverse(BinaryTree tree);

int visit(char e);


/**
 * 用先序遍历的方式输入元素构造二叉树
 */
BinaryTree createBinaryTree(BinaryTree node) {
    char e;
    scanf("%c", &e);
    if (e == '#') {
        node = NULL;
    } else {
        if (!(node = (Node *) malloc(sizeof(Node)))) {
            exit(OVERFLOW);
        }
        node->data = e;                                   // 生成根节点
        node->lChild = createBinaryTree(node->lChild);    // 构造左子树
        node->rChild = createBinaryTree(node->rChild);    // 构造右子树
    }
    return node;
}

/**
 * 先序遍历递归算法
 */
int preOrderTraverse(BinaryTree tree) {
    if (tree) {
        if (!visit(tree->data)) { return ERROR; }
        preOrderTraverse(tree->lChild);
        preOrderTraverse(tree->rChild);
    }
    return OK;
}

/**
 * 中序遍历递归算法
 */
int inOrderTraverse(BinaryTree tree) {
    if (tree) {
        inOrderTraverse(tree->lChild);
        if (!visit(tree->data)) { return ERROR; };
        inOrderTraverse(tree->rChild);
    }
    return OK;

}

/**
 * 后序遍历递归算法
 */
int postOrderTraverse(BinaryTree tree) {
    if (tree) {
        postOrderTraverse(tree->lChild);
        postOrderTraverse(tree->rChild);
        if (!visit(tree->data)) { return ERROR; };
    }
    return OK;
}

/**
 * 先序遍历非递归算法
 */
int preOrderStackTraverse(BinaryTree tree) {
    Stack stack;
    BinaryTree topNode;//从栈顶弹出的节点
    initStack(&stack);
    push(&stack, tree); // 根指针入栈
    while (!isStackEmpty(stack)) {
        pop(&stack, &topNode);    //访问根节点
        if (!visit(topNode->data)) { return ERROR; }
        if (topNode->rChild) {
            push(&stack, topNode->rChild);
        }
        if (topNode->lChild) {
            push(&stack, topNode->lChild);
        }
    }
    destroyStack(&stack);
    return OK;
}

/**
 * 中序遍历非递归算法
 */
int inOrderStackTraverse(BinaryTree tree) {
    Stack stack;
    BinaryTree topNode;
    initStack(&stack);
    topNode = tree;
    while (topNode || !isStackEmpty(stack)) {
        if (topNode) {
            push(&stack, topNode);
            topNode = topNode->lChild;    //根指针进栈，遍历左子树
        }
        else {//根指针退栈，访问根节点，遍历右子树
            pop(&stack, &topNode);
            if (!visit(topNode->data)) { return ERROR; }
            topNode = topNode->rChild;
        }
    }
    destroyStack(&stack);
    return OK;
}

/**
 * 后序遍历非递归算法
 */
int postOrderStackTraverse(BinaryTree tree) {
    Stack S;
    BinaryTree p, q;
    initStack(&S);
    push(&S, tree); // 根指针入栈
    while (!isStackEmpty(S)) {
        while (getTop(S, &p) && p && (p->lChild || p->rChild)) {
            push(&S, p->rChild);        // 右子树入栈
            push(&S, p->lChild);        // 左子树入栈
        }//注意栈中存在空指针，表示某个结点的右子树为空
        if (!isStackEmpty(S)) {//访问结点
            pop(&S, &p);
            if (p) {
                if (!visit(p->data)) { return ERROR; }
            }
            else {// 存在右子树为空的结点，继续向上返回
                pop(&S, &p);
                if (!visit(p->data)) { return ERROR; }
            }
            while (getTop(S, &q) && q && p == q->rChild) {//若当前为右子树，则继续出栈
                pop(&S, &p);
                if (!visit(p->data)) { return ERROR; }
                getTop(S, &q);
            }
        }
    }
    destroyStack(&S);
    return OK;
}

/**
 * 输出当前访问的元素e
 */
int visit(char e) {
    if (e == '\0') {
        return ERROR;
    } else {
        printf("%c", e);
    }
    return OK;
}

/**
 * 初始化栈：构造一个空栈s
 */
int initStack(Stack *stack) {
    stack->base = (BinaryTree *) malloc(STACK_INIT_SIZE * sizeof(BinaryTree));
    if (!stack->base) {
        printf("分配内存失败.\n");
        exit(0);
    }
    stack->top = stack->base;
    stack->stackSize = STACK_INIT_SIZE;
    return OK;
}

/**
 * 销毁栈s
 */
int destroyStack(Stack *stack) {
    if (!stack) {
        printf("指针为空，释放失败.\n");
        exit(0);
    }
    free(stack->base);
    return OK;
}

/**
 * 判断栈是否为空
 */
int isStackEmpty(Stack stack) {
    if (stack.top == stack.base) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * 获得栈顶元素e
 */
int getTop(Stack stack, BinaryTree *node) {
    if (stack.top == stack.base) {
        return FALSE;
    } else {
        *node = *(stack.top - 1);
        return OK;
    }
}

/**
 * 插入元素e为新的栈顶元素
 */
int push(Stack *stack, BinaryTree node) {
    if (stack->top - stack->base >= stack->stackSize) {//如果栈已满，追加存储空间
        stack->base = (BinaryTree *) realloc(stack->base, (stack->stackSize + STACK_INCREMENT) * sizeof(BinaryTree));
        if (!stack->base) {
            printf("重新申请空间失败.\n");
            exit(0);
        }
        stack->top = stack->base + stack->stackSize;//更改栈顶指针
        stack->stackSize += STACK_INCREMENT;
    }
    *stack->top++ = node;
    return OK;
}

/**
 * 删除栈顶元素，并把被删除的元素赋值给e
 */
int pop(Stack *stack, BinaryTree *node) {
    if (stack->top == stack->base) {//如果栈顶元素为空
        return ERROR;
    }
    *node = *(--stack->top);
    return OK;
}

/**
 * 程序入口
 */
int main() {
    BinaryTree tree = NULL;
    printf("请按先序遍历的顺序输入一个二叉树，#代表结点为空（如：124##5##3##）：");
    tree = createBinaryTree(tree);//把创建好的树的根节点指针赋给tree
    printf("\n递归先序遍历：\n");
    preOrderTraverse(tree);
    printf("\n递归中序遍历：\n");
    inOrderTraverse(tree);
    printf("\n递归后序遍历：\n");
    postOrderTraverse(tree);
    printf("\n非递归先序遍历：\n");
    preOrderStackTraverse(tree);
    printf("\n非递归中序遍历：\n");
    inOrderStackTraverse(tree);
    printf("\n非递归后序遍历：\n");
    postOrderStackTraverse(tree);

    printf("\n");
    return 0;
}
