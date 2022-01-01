#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

pnode buildGraph(int num_of_nodes)
{
    node *head = NULL;
    pnode newNode, temp = NULL;
    int i;
    head = (pnode)malloc(sizeof(node));
    if (head == NULL)
    {
        perror("malloc didnt work");
        exit(0);
    }
    head->node_num = 0;
    head->next = NULL;
    head->edges = NULL;
    temp = head;

    for (i = 1; i < num_of_nodes; i++)
    {
        newNode = (pnode)malloc(sizeof(node));
        if (newNode == NULL)
        {
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

void deleteGraph_cmd(pnode *head)
{
    pnode tempNode = *head;
    while (tempNode != NULL)
    {
        pedge tempEdge = tempNode->edges;
        while (tempEdge != NULL)
        {
            pedge tempEdgefree = tempEdge;
            tempEdge = tempEdge->next;
            free(tempEdgefree);
        }
        node *tempFree = tempNode;
        tempNode = tempNode->next;
        free(tempFree);
    }
}

void print_graph(pnode head)
{ // for self debug
    pnode tempNode = head;
    while (tempNode != NULL)
    {
        printf("Node: %d {", tempNode->node_num);
        pedge tempEdge = tempNode->edges;
        while (tempEdge != NULL)
        {
            printf("dest: %d weight: %d ", tempEdge->endpoint->node_num, tempEdge->weight);
            tempEdge = tempEdge->next;
        }
        printf("}");
        tempNode = tempNode->next;
    }
}
