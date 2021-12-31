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

    if(head == NULL)
    {
        exit(0);
    }

    head->node_num = 0;
    head->next = NULL;
    head->edges = NULL;

    temp = head;

    for(i=1; i<num_of_nodes; i++)
    {
        newNode = (pnode)malloc(sizeof(node));

        if(newNode == NULL)
        {
            perror("Unable to allocate memory.");
            break;
        }
        newNode->node_num = i;
        newNode->next = NULL;
        newNode->edges = NULL;

        temp->next = newNode;
        temp = temp->next;
    }
    return head;
}

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

void add_adge(pnode *head,int src){

    int dest;
    int count = 0;
    int w;
    pnode temp = getNode(src,head);
    while(scanf("%d",&dest)!=0 && scanf("%d",&w)!=0)
    {
        if((dest >= 'A' && dest <= 'Z') || (w >= 'A' && w <= 'Z'))
        {
            break;
        }
        if((dest >= 'a' && dest <= 'z') || (w >= 'a' && w <= 'z'))
        {
            break;
        }
        insert_edge(temp,dest,w,head);
    }
}

void insert_edge(pnode temp,int dest,int w,pnode *head){

    if(temp->edges == NULL)
    {
        temp->edges = (pedge)malloc(sizeof(edge));
        if(temp->edges == NULL)
        {
            exit(0);
        }
        temp->edges->weight = w;
        temp->edges->next =NULL;
        node *D = getNode(dest,head);
        temp->edges->endpoint = &(*D);
    }
    else{
        pedge n = temp->edges;

        while(n->next!=NULL)
        {
            n = n->next;
        }
        n->next = (pedge)malloc(sizeof(edge));
        if(n == NULL)
        {
            exit(0);
        }
        n->next->next = NULL;
        n->next->weight = w;
        node *D = getNode(dest,head);
        n->next->endpoint = &(*D);
    }
}
void insert_node_cmd(pnode *head){
    int src;
    scanf("%d", &src);
    int dest;
    int count = 0;
    int w;
    pnode temp = getNode(src,head);
    if(temp == NULL){
        pnode inGraph = *head;
        while (inGraph->next != NULL){
            inGraph = inGraph->next;
        }
        pnode newNode = (pnode)(malloc(sizeof (node)));
        newNode->node_num = src;
        newNode->edges = NULL;
        newNode->next = NULL;
        inGraph->next = newNode;
        printf("enter dest and weight:\n");
        while (scanf("%d",&dest)!=0 && scanf("%d",&w)!=0){
            if((dest >= 'A' && dest <= 'Z') || (w >= 'A' && w <= 'Z'))
            {
                break;
            }
            if((dest >= 'a' && dest <= 'z') || (w >= 'a' && w <= 'z'))
            {
                break;
            }
            insert_edge(newNode,dest,w,head);
        }
    } else{
        free_edges(temp);
        pedge tempEdge = temp->edges;
        temp->edges = NULL;
        printf("enter dest and weight:\n");
        while (scanf("%d",&dest)!=0 && scanf("%d",&w)!=0){
            if((dest >= 'A' && dest <= 'Z') || (w >= 'A' && w <= 'Z'))
            {
                break;
            }
            if((dest >= 'a' && dest <= 'z') || (w >= 'a' && w <= 'z'))
            {
                break;
            }
            insert_edge(temp,dest,w,head);
        }
    }
}
void free_edges(pnode p)
{
    if(p->edges!=NULL)
    {
        pedge temp = p->edges;

        while(temp->next!=NULL)
        {
            pedge p1 = NULL;
            p1 = temp;
            temp = temp->next;
            free(p1);
        }
    }
}
void del_edge(pnode *head,int n)
{
    pnode tempNode = *head;

    while (tempNode!= NULL)
    {
        if(tempNode->id != n && tempNode->edges!=NULL){

            if(tempNode->edges->endpoint->id !=n)
            {
                pedge tempEdge = tempNode->edges;

                while (tempEdge->next!= NULL)
                {
                    if(tempEdge->next->endpoint->id == n){
                        pedge p1 = tempEdge->next;
                        tempEdge->next=tempEdge->next->next;
                        free(p1);
                        break;
                    }
                    tempEdge = tempEdge->next;
                }
            }
            else
            {
                if(tempNode->edges->next ==NULL)
                {
                    pedge p1 = tempNode->edges;
                    tempNode->edges = NULL;
                    free(p1);
                }
                else{
                    pedge p1 = tempNode->edges;
                    tempNode->edges = p1->next;
                    free(p1);
                }
            }
        }
        tempNode = tempNode->next;
    }
}
void delete_node_cmd(pnode *head)
{
    int D = 0;
    scanf("%d",&D);
    del_edge(head,D);
    pnode tempNode = *head;
    node *p = NULL;
    if(tempNode->node_num != D)
    {
        while (tempNode->next->node_num != D)
        {
            tempNode = tempNode->next;
        }
        p = tempNode->next;
        tempNode->next=tempNode->next->next;
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
void deleteGraph_cmd(pnode* head){
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




void print_graph(pnode head){// for self debug
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