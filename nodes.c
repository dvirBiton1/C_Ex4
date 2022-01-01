#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

pnode getNode(int id, pnode *head)
{
    pnode temp = *head;

    while (temp != NULL)
    {
        if (temp->node_num == id)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    return NULL;
}

void insert_node_funcA_cmd(pnode *head, int src)
{

    int dest;
    int weight;
    pnode temp = getNode(src, head);
    while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
    {
        if (isalpha(dest) || isalpha(weight))
        {
            break;
        }
        add_edge(temp, dest, weight, head);
    }
}

void insert_node_cmd(pnode *head)
{
    int src;
    scanf("%d", &src);
    int dest;
    int weight;
    pnode temp = getNode(src, head);
    if (temp == NULL)
    {
        pnode inGraph = *head;
        while (inGraph->next != NULL)
        {
            inGraph = inGraph->next;
        }
        pnode newNode = (pnode)(malloc(sizeof(node)));
        if (newNode == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        newNode->node_num = src;
        newNode->edges = NULL;
        newNode->next = NULL;
        inGraph->next = newNode;
        //printf("enter dest and weight:\n");
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
        {
            if (isalpha(dest) || isalpha(weight))
            {
                break;
            }
            add_edge(newNode, dest, weight, head);
        }
    }
    else
    {
        free_edges(temp);
        temp->edges = NULL;
        //printf("enter dest and weight:\n");
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
        {
            if (isalpha(dest) || isalpha(weight))
            {
                break;
            }
            add_edge(temp, dest, weight, head);
        }
    }
}

void delete_node_cmd(pnode *head)
{
    int D = 0;
    scanf("%d", &D);
    del_edge(head, D);
    pnode tempNode = *head;
    node *p = NULL;
    if (tempNode->node_num != D)
    {
        while (tempNode->next->node_num != D)
        {
            tempNode = tempNode->next;
        }
        p = tempNode->next;
        tempNode->next = tempNode->next->next;
        free_edges(p);
        free(p);
    }
    else
    {
        p = *head;
        *head = p->next;
        free_edges(p);
        free(p);
    }
}
