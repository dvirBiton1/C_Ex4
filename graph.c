#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

pnode buildGraph(int num_of_nodes) {
    node *head = NULL;
    pnode newNode, temp = NULL;
    int i;

    head = (pnode) malloc(sizeof(node));
    if (head == NULL) {
        perror("malloc didnt work");
        exit(0);
    }
    head->node_num = 0;
    head->next = NULL;
    head->edges = NULL;
    temp = head;

    for (i = 1; i < num_of_nodes; i++) {
        newNode = (pnode) malloc(sizeof(node));
        if (newNode == NULL) {
            perror("malloc didnt work");
            exit(0);
        }
        newNode->node_num = i;
        newNode->next = NULL;
        newNode->edges = NULL;
        temp->next = newNode;
        temp = temp->next;
    }
    return head;
}

pnode getNode(int id, pnode *head) {
    pnode temp = *head;

    while (temp != NULL) {
        if (temp->node_num == id) {
            return temp;
        } else {
            temp = temp->next;
        }
    }
    return NULL;
}

void insert_node_funcA_cmd(pnode *head, int src) {

    int dest;
    int weight;
    pnode temp = getNode(src, head);
    while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0) {
        if (isalpha(dest) || isalpha(weight)) {
            break;
        }
        add_edge(temp, dest, weight, head);
    }
}

void add_edge(pnode temp, int dest, int w, pnode *head) {

    if (temp->edges == NULL) {
        temp->edges = (pedge) malloc(sizeof(edge));
        if (temp->edges == NULL) {
            perror("malloc didnt work");
            exit(0);
        }
        temp->edges->weight = w;
        temp->edges->next = NULL;
        node *D = getNode(dest, head);
        temp->edges->endpoint = &(*D);
    } else {
        pedge n = temp->edges;
        while (n->next != NULL) {
            n = n->next;
        }
        n->next = (pedge) malloc(sizeof(edge));
        if (n->next == NULL) {
            perror("malloc didnt work");
            exit(0);
        }
        n->next->next = NULL;
        n->next->weight = w;
        node *D = getNode(dest, head);
        n->next->endpoint = &(*D);
    }
}

void insert_node_cmd(pnode *head) {
    int src;
    scanf("%d", &src);
    int dest;
    int count = 0;
    int weight;
    pnode temp = getNode(src, head);
    if (temp == NULL) {
        pnode inGraph = *head;
        while (inGraph->next != NULL) {
            inGraph = inGraph->next;
        }
        pnode newNode = (pnode) (malloc(sizeof(node)));
        if (newNode == NULL) {
            perror("malloc didnt work");
            exit(0);
        }
        newNode->node_num = src;
        newNode->edges = NULL;
        newNode->next = NULL;
        inGraph->next = newNode;
        printf("enter dest and weight:\n");
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0) {
            if (isalpha(dest) || isalpha(weight)) {
                break;
            }
            add_edge(newNode, dest, weight, head);
        }
    } else {
        free_edges(temp);
        pedge tempEdge = temp->edges;
        temp->edges = NULL;
        printf("enter dest and weight:\n");
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0) {
            if (isalpha(dest) || isalpha(weight)) {
                break;
            }
            add_edge(temp, dest, weight, head);
        }
    }
}

void free_edges(pnode p) {
    if (p->edges != NULL) {
        pedge temp = p->edges;

        while (temp->next != NULL) {
            pedge p1 = NULL;
            p1 = temp;
            temp = temp->next;
            free(p1);
        }
    }
}

void del_edge(pnode *head, int n) {
    pnode tempNode = *head;

    while (tempNode != NULL) {
        if (tempNode->node_num != n && tempNode->edges != NULL) {

            if (tempNode->edges->endpoint->node_num != n) {
                pedge tempEdge = tempNode->edges;

                while (tempEdge->next != NULL) {
                    if (tempEdge->next->endpoint->node_num == n) {
                        pedge p1 = tempEdge->next;
                        tempEdge->next = tempEdge->next->next;
                        free(p1);
                        break;
                    }
                    tempEdge = tempEdge->next;
                }
            } else {
                if (tempNode->edges->next == NULL) {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = NULL;
                    free(p1);
                } else {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = p1->next;
                    free(p1);
                }
            }
        }
        tempNode = tempNode->next;
    }
}

void delete_node_cmd(pnode *head) {
    int D = 0;
    scanf("%d", &D);
    del_edge(head, D);
    pnode tempNode = *head;
    node *p = NULL;
    if (tempNode->node_num != D) {
        while (tempNode->next->node_num != D) {
            tempNode = tempNode->next;
        }
        p = tempNode->next;
        tempNode->next = tempNode->next->next;
        free_edges(p);
        free(p);
    } else {
        p = *head;
        *head = p->next;
        free_edges(p);
        free(p);
    }
}

void deleteGraph_cmd(pnode *head) {
    pnode tempNode = *head;
    while (tempNode != NULL) {
        pedge tempEdge = tempNode->edges;
        while (tempEdge != NULL) {
            pedge tempEdgefree = tempEdge;
            tempEdge = tempEdge->next;
            free(tempEdgefree);
        }
        node *tempFree = tempNode;
        tempNode = tempNode->next;
        free(tempFree);
    }
}


void print_graph(pnode head) {// for self debug
    pnode tempNode = head;
    while (tempNode != NULL) {
        printf("Node: %d {", tempNode->node_num);
        pedge tempEdge = tempNode->edges;
        while (tempEdge != NULL) {
            printf("dest: %d weight: %d ", tempEdge->endpoint->node_num, tempEdge->weight);
            tempEdge = tempEdge->next;
        }
        printf("}");
        tempNode = tempNode->next;
    }
}
    //*********TSP*********//
void deep_copy(int* fromArr,int* toArr, int fromLenght) {
        for (int i = 0; i < fromLenght; ++i) {
            toArr[i] =fromArr[i];
        }
    }
void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i]= arr[j];
    arr[j] = temp;
}
void calcPermot(pnode* graph, int* arr, int arrLength,int* weight){
    int tempWeight = 0;
    for (int i = 0; i < arrLength-1; ++i) {
        int distance = shortsPath_cmd(graph,arr[i], arr[i+1]);
        if (distance == -1){
            tempWeight = INFINITY;
            return;
        }
        tempWeight += distance;
    }
    if (tempWeight < weight){
        *weight = tempWeight;
    }
}
void permotion(pnode* graph, int start ,int* arr, int arrLength,int* weight){
    if (start == arrLength -1 ){
        calcPermot(graph,arr, arrLength, weight);
        return;
    }
    for (int i = start; i < arrLength; ++i) {
        int* arrCopy = (int *) (calloc(arrLength, sizeof(int)));
        deep_copy(arr,arrCopy,arrLength);
        swap(arrCopy,start, i);
        permotion(graph, start + 1, arrCopy, arrLength, weight);
        free(arrCopy);
    }
}
int TSP_cmd(pnode head){
    int weight = INFINITY;
    int* pweight = &weight;
    int arrlenth = -1;
    pnode graph = head;
    scanf("%d", arrlenth);
    int *arr = (int *) (calloc(arrlenth, sizeof(int)));
    for (int i = 0; i < arrlenth; i++) {
        scanf("%d", &arr[i]);
    }
    int *arrCopy = (int *) (calloc(arrlenth, sizeof(int)));
    deep_copy(arr,arrCopy,arrlenth);
    permotion(graph,0,arrCopy,arrlenth,pweight);
    free(arr);
    free(arrCopy);
    if (weight == INFINITY){
        weight = -1;
    }
    return weight;
}
