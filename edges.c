#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

void add_edge(pnode temp_edge, int dest, int w, pnode *head)
{

    if (temp_edge->edges == NULL)
    {
        temp_edge->edges = (pedge)malloc(sizeof(edge));
        if (temp_edge->edges == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        temp_edge->edges->weight = w;
        temp_edge->edges->next = NULL;
        node *D = getNode(dest, head);
        temp_edge->edges->endpoint = &(*D);
    }
    else
    {
        pedge second_edge = temp_edge->edges;
        while (second_edge->next != NULL)
        {
            second_edge = second_edge->next;
        }
        second_edge->next = (pedge)malloc(sizeof(edge));
        if (second_edge->next == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }
        second_edge->next->next = NULL;
        second_edge->next->weight = w;
        node *D = getNode(dest, head);
        second_edge->next->endpoint = &(*D);
    }
}

void free_edges(pnode edg)
{
    if (edg->edges != NULL)
    {
        pedge temp = edg->edges;

        while (temp != NULL)
        {
            pedge pointer = NULL;
            pointer = temp;
            temp = temp->next;
            free(pointer);
        }
    }
    else{
        free(edg->edges);
    }
}

void del_edge(pnode *head, int node_Id)
{
    pnode temp_Node = *head;

    while (temp_Node != NULL)
    {
        if (temp_Node->node_num != node_Id && temp_Node->edges != NULL)
        {

            if (temp_Node->edges->endpoint->node_num != node_Id)
            {
                pedge temp_Edge = temp_Node->edges;

                while (temp_Edge->next != NULL)
                {
                    if (temp_Edge->next->endpoint->node_num == node_Id)
                    {
                        pedge pointer = temp_Edge->next;
                        temp_Edge->next = temp_Edge->next->next;
                        free(pointer);
                        break;
                    }
                    temp_Edge = temp_Edge->next;
                }
            }
            else
            {
                if (temp_Node->edges->next == NULL)
                {
                    pedge p1 = temp_Node->edges;
                    temp_Node->edges = NULL;
                    free(p1);
                }
                else
                {
                    pedge p1 = temp_Node->edges;
                    temp_Node->edges = p1->next;
                    free(p1);
                }
            }
        }
        temp_Node = temp_Node->next;
    }
}