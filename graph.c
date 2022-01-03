#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

pnode build_Graph(int verticals)
{
    node *head = NULL;
    pnode new_node, temp = NULL;
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

    for (i = 1; i < verticals; i++)
    {
        new_node = (pnode)malloc(sizeof(node));
        if (new_node == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        new_node->node_num = i;
        new_node->next = NULL;
        new_node->edges = NULL;
        temp->next = new_node;
        temp = temp->next;
    }
    return head;
}

void deleteGraph_cmd(pnode *head)
{
    pnode temp_node = *head;
    while (temp_node != NULL)
    {
        pedge temp_edge = temp_node->edges;
        while (temp_edge != NULL)
        {
            pedge tempEdge_free = temp_edge;
            temp_edge = temp_edge->next;
            free(tempEdge_free);
        }
        node *temp_Free = temp_node;
        temp_node = temp_node->next;
        free(temp_Free);
    }
    free(temp_node);
}

void print_graph(pnode head)
{ // for self debug
    pnode temp_node = head;
    while (temp_node != NULL)
    {
        printf("Node: %d {", temp_node->node_num);
        pedge temp_edge = temp_node->edges;
        while (temp_edge != NULL)
        {
            printf("dest: %d weight: %d ", temp_edge->endpoint->node_num, temp_edge->weight);
            temp_edge = temp_edge->next;
        }
        printf("}");
        temp_node = temp_node->next;
    }
}