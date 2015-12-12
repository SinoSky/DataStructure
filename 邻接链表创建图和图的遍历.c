#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define LIST_HEAD_NUM 20        //存储邻接表的表头数组的长度

int visited[LIST_HEAD_NUM];    //用于记录遍历状态

/*
 * 邻接表的边结点，存储一条依赖vi的边（在有向图中是以Vi为尾的弧）
 */
typedef struct EdgeNode {
    int adjvexNum;          //该边指向的结点（Vj）在图中的位置序号
    struct EdgeNode *next; //指向下一条边
} EdgeNode;

/**
 * 邻接表的表头结点，存储顶点Vi
 */
typedef struct VexNode {
    char data;              //顶点的数据
    EdgeNode *firstEdge;    //指向第一条依附该顶点的边结点（或以该顶点为尾的弧结点）
} AdjHead;

/**
 * 使用邻接表结构存储的图
 */
typedef struct {
    AdjHead adjList[LIST_HEAD_NUM];    //用数组顺序存储邻接表的表头结点
    int vexNum, edgeNum,flag;     //图中所含的顶点数和边数以及是有向图还是无向图
} Graph;

/*
 * 用于构成队列结构的结点
 */
typedef struct QueueNode {
    int data;                   //结点数据
    struct QueueNode *next;    //指向下一个结点
} QueueNode;


typedef struct {
    QueueNode *front;    //队头指针
    QueueNode *rear;     //队尾指针
} LinkQueue;

/**
 * 函数声明
 */


int initQueue(LinkQueue *queue);

int isEmpty(LinkQueue queue);

int enQueue(LinkQueue *queue, int element);

int deQueue(LinkQueue *queue, int *element);

int createGraph(Graph *graph);

void DFS(Graph graph, int i);

int dfsTraverse(Graph graph);

int bfsTraverse(Graph graph);
void insertEdge(Graph *graph, int adjvex1, int adjvex2);

/**
 * 初始化队列
 */
int initQueue(LinkQueue *queue) {
    queue->front = queue->rear = (QueueNode *) malloc(sizeof(QueueNode));
    if (!queue->front) {
        exit(OVERFLOW);
    }
    queue->front->next = NULL;
    return OK;
}

/**
 * 队列判空
 */
int isEmpty(LinkQueue queue) {
    if (queue.front->next == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/**
 * 入队列
 */
int enQueue(LinkQueue *queue, int element) {
    QueueNode*queueNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (!queueNode) {
        exit(OVERFLOW);
    }
    queueNode->data = element;
    queueNode->next = NULL;
    queue->rear->next = queueNode;
    queue->rear = queueNode;
    return OK;
}

/**
 * 出队列
 */
int deQueue(LinkQueue *queue, int *element) {
    QueueNode*queueNode;
    if (queue->front == queue->rear) {
        return ERROR;
    }
    queueNode = queue->front->next;
    *element = queueNode->data;
    queue->front->next = queueNode->next;
    if (queue->rear == queueNode) {
        queue->rear = queue->front;
    }
    free(queueNode);
    return OK;
}


/**
 * 根据构造邻接链表来构造图
 */
int createGraph(Graph *graph) {
    EdgeNode *node;
    int vi, vj, k;
    printf("请输入是有向图还是无向图（1代表无向图,其他数字为有向图）:\n");
    scanf("%d",&graph->flag);
    printf("请输入要创建的图的顶点数目和边数目:\n");
    scanf("%d %d", &graph->vexNum, &graph->edgeNum);
    getchar();//用于接收上一个scanf确定后按下的回车键
    //初始化顶点
    for (k = 0; k < graph->vexNum; k++) {
        graph->adjList[k].firstEdge = NULL;     //初始化时先让邻接表的每个表头结点都指向空
        printf("请输入第%d个顶点的数据:\n", k);
        scanf("%c", &graph->adjList[k].data);   //再输入顶点数据
        getchar();//用于接收上一个scanf确定后按下的回车键
    }

    //初始化边
    printf("请按照0-%d的序号输入邻接矩阵中的边（Vi，Vj）如0->[2]->[1]->[3]即输入\n0 3\n0 1\n0 2\n请输入你的邻接链表:\n",graph->vexNum-1);
    for (k = 0; k < graph->edgeNum; k++) {
        scanf("%d %d", &vi, &vj);
        //把指向Vj的边插入到Vi后面
        insertEdge(graph, vi, vj);
        if (graph->flag==1){//把指向Vi的边插入到Vj后面(构造无向图)
            insertEdge(graph, vj, vi);
        }
    }

    printf("你输入的邻接链表如下：\n");
    for (k = 0; k < graph->vexNum; k++) {
        printf("%d[%c]",k,graph->adjList[k].data);
        node=graph->adjList[k].firstEdge;
        while ( node) {
            printf("->[%d]",node->adjvexNum);
            node=node->next;
        }
        printf("\n");
    }
    return OK;
}

/**
 *  把指向adjvex2的边插入到adjvex1后面
 */
void insertEdge(Graph *graph, int adjvex1, int adjvex2) {
    EdgeNode *edgeNode = (EdgeNode *) malloc(sizeof(EdgeNode));//生成一条边
    edgeNode->adjvexNum = adjvex2;
    edgeNode->next = graph->adjList[adjvex1].firstEdge;
    graph->adjList[adjvex1].firstEdge = edgeNode;

}

/**
 * 深度遍历
 */
int dfsTraverse(Graph graph) {
    int i;
    for (i = 0; i < LIST_HEAD_NUM; i++) {//遍历前所有元素都没有访问过
        visited[i] = FALSE;
    }
    for (i = 0; i < graph.vexNum; i++) {
        if (!visited[i]) {
            DFS(graph, i);
        }
    }
    return OK;
}

/**
 * 深度遍历的递归
 */
void DFS(Graph graph, int i) {
    EdgeNode *edgeNode;
    visited[i] = TRUE;
    printf("%c ", graph.adjList[i].data);
    edgeNode = graph.adjList[i].firstEdge;
    while (edgeNode) {
        if (!visited[edgeNode->adjvexNum]) {
            DFS(graph, edgeNode->adjvexNum);
        }
        edgeNode = edgeNode->next;
    }
}

/**
 * 广度遍历
 */
int bfsTraverse(Graph graph) {
    int i;
    EdgeNode *edgeNode;
    LinkQueue queue;
    initQueue(&queue);
    for (i = 0; i < LIST_HEAD_NUM; i++) {
        visited[i] = FALSE;
    }
    for (i = 0; i < graph.vexNum; i++) {
        if (!visited[i]) {
            visited[i] = TRUE;
            printf("%c ", graph.adjList[i].data);
            enQueue(&queue, i);
            while (!isEmpty(queue)) {//用辅助队列是否为空来判断与同一个结点连接的其它点是否遍历完成
                deQueue(&queue, &i);
                edgeNode = graph.adjList[i].firstEdge;
                while (edgeNode) {
                    if (!visited[edgeNode->adjvexNum]) {
                        visited[edgeNode->adjvexNum] = TRUE;
                        printf("%c ", graph.adjList[edgeNode->adjvexNum].data);
                        enQueue(&queue, edgeNode->adjvexNum);
                    }
                    edgeNode = edgeNode->next;
                }
            }
        }
    }
    return OK;
}

int main() {
    Graph graph;
    createGraph(&graph);
    printf("深度优先遍历:");
    dfsTraverse(graph);
    printf("\n广度优先遍历:");
    bfsTraverse(graph);
    printf("\n");
}