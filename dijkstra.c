#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

pdijkstra buildDijkstra(pnode start, int src)
{
    pdijkstra head = NULL;
    pdijkstra *index = &head;
    while (start != NULL)
    {
        (*index) = (pdijkstra)malloc(sizeof(dijkstra));
        if ((*index) == NULL)
        {
            perror("malloc didnt work");
            exit(0);
        }

        (*index)->node = start;
        if (start->node_num == src)
        {
            (*index)->weight = 0;
        }
        else
        {
            (*index)->weight = INFINITY;
        }
        (*index)->tag = 0;
        (*index)->next = NULL;
        index = &((*index)->next);
        start = start->next;
    }
    return head;
}

void deletateDijkstra(pdijkstra dijkstra)
{
    while (dijkstra != NULL)
    {
        pdijkstra temp = dijkstra;
        dijkstra = dijkstra->next;
        free(temp);
    }
}

pdijkstra getPdijkstra(pdijkstra head, int id)
{
    while (head != NULL)
    {
        if (head->node->node_num == id)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

pdijkstra minVertical(pdijkstra head)
{
    pdijkstra ver = NULL;
    while (head != NULL)
    {
        if (!head->tag && head->weight < INFINITY && (ver == NULL || ver->weight < head->weight))
        {
            ver = head;
        }
        head = head->next;
    }
    if (ver != NULL)
    {
        ver->tag = 1;
    }
    return ver;
}

int shortsPath_cmd(pnode head, int src, int dest)
{
    pdijkstra dijkstraHead = buildDijkstra(head, src);
    pdijkstra u = minVertical(dijkstraHead);
    while (u != NULL)
    {
        pedge edgeIndex = u->node->edges;
        while (edgeIndex != NULL)
        {
            // relax
            pdijkstra v = getPdijkstra(dijkstraHead, edgeIndex->endpoint->node_num);
            int newDist = u->weight + edgeIndex->weight;
            if (v->weight > newDist)
            {
                v->weight = newDist;
            }
            edgeIndex = edgeIndex->next;
        }
        u = minVertical(dijkstraHead);
    }
    int distance = getPdijkstra(dijkstraHead, dest)->weight;
    if (distance == INFINITY)
    {
        distance = -1;
    }
    deletateDijkstra(dijkstraHead);
    return distance;
}