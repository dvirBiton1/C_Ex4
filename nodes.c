#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

pnode getNode(int id, pnode *head)
{
    pnode temp_node = *head;

    while (temp_node != NULL)
    {
        if (temp_node->node_num == id)
        {
            return temp_node;
        }
        else
        {
            temp_node = temp_node->next;
        }
    }
    return NULL;
}

void funcA_insert(pnode *head, int src)
{

    int dest;
    int weight;
    pnode temp_node = getNode(src, head);
    while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
    {
        if (isalpha(dest) || isalpha(weight))
        {
            break;
        }
        add_edge(temp_node, dest, weight, head);
    }
}

void insert_node_cmd(pnode *head)
{
    int src;
    scanf("%d", &src);
    int dest;
    int weight;
    pnode temp_node = getNode(src, head);
    if (temp_node == NULL)
    {
        pnode in_Graph = *head;
        while (in_Graph->next != NULL)
        {
            in_Graph = in_Graph->next;
        }
        pnode new_Node = (pnode)(malloc(sizeof(node)));
        if (new_Node == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        new_Node->node_num = src;
        new_Node->edges = NULL;
        new_Node->next = NULL;
        in_Graph->next = new_Node;
        //printf("enter dest and weight:\n");
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
        {
            if (isalpha(dest) || isalpha(weight))
            {
                break;
            }
            add_edge(new_Node, dest, weight, head);
        }
    }
    else
    {
        free_edges(temp_node);
        temp_node->edges = NULL;
        //printf("enter dest and weight:\n");
        while (scanf("%d", &dest) != 0 && scanf("%d", &weight) != 0)
        {
            if (isalpha(dest) || isalpha(weight))
            {
                break;
            }
            add_edge(temp_node, dest, weight, head);
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