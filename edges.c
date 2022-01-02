#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

void add_edge(pnode temp, int dest, int w, pnode *head)
{

    if (temp->edges == NULL)
    {
        temp->edges = (pedge)malloc(sizeof(edge));
        if (temp->edges == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        temp->edges->weight = w;
        temp->edges->next = NULL;
        node *D = getNode(dest, head);
        temp->edges->endpoint = &(*D);
    }
    else
    {
        pedge n = temp->edges;
        while (n->next != NULL)
        {
            n = n->next;
        }
        n->next = (pedge)malloc(sizeof(edge));
        if (n->next == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        n->next->next = NULL;
        n->next->weight = w;
        node *D = getNode(dest, head);
        n->next->endpoint = &(*D);
    }
}

void free_edges(pnode edg)
{
    if (edg->edges != NULL)
    {
        pedge temp = edg->edges;

        while (temp != NULL)
        {
            pedge p1 = NULL;
            p1 = temp;
            temp = temp->next;
            free(p1);
        }
    }
    else{
        free(edg->edges);
    }
}

void del_edge(pnode *head, int n)
{
    pnode tempNode = *head;

    while (tempNode != NULL)
    {
        if (tempNode->node_num != n && tempNode->edges != NULL)
        {

            if (tempNode->edges->endpoint->node_num != n)
            {
                pedge tempEdge = tempNode->edges;

                while (tempEdge->next != NULL)
                {
                    if (tempEdge->next->endpoint->node_num == n)
                    {
                        pedge p1 = tempEdge->next;
                        tempEdge->next = tempEdge->next->next;
                        free(p1);
                        break;
                    }
                    tempEdge = tempEdge->next;
                }
            }
            else
            {
                if (tempNode->edges->next == NULL)
                {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = NULL;
                    free(p1);
                }
                else
                {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = p1->next;
                    free(p1);
                }
            }
        }
        tempNode = tempNode->next;
    }
}
