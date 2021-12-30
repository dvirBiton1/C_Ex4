#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    pnode temp = NULL;
    pnode *head = &temp;
    char choise;
    char ch;
    int v = 0;
    int src = 0;

    while (scanf("%c", &choise) != EOF) {
        if (choise == 'A') {
            deleteGraph_cmd(head);
            scanf("%d", &v);
            *head = creat_graph(v);

            scanf("%c", &ch);

            while (scanf("%c", &ch) != 0) {
                if (ch == 'n') {
                    scanf("%d", &src);
                    add_adge(head, src);
                } else {
                    break;
                }
            }
            print_graph(*head);
            choise = ch;

            printf("end A func\n");
        }
        if (choise == 'B') {
            printf("start B FUNC\n");
            insert_node_cmd(head);
            print_graph(*head);
            continue;

        }
        if (choise == 'D') {
            printf("start D FUNC\n");
            delete_node_cmd(head);
            print_graph(*head);
            continue;
        }
        if (choise == 'S') {
            printf("start S FUNC\n");
            // shortsPath_cmd(*head);
            print_graph(*head);
            continue;
        }
        if (choise == 'T') {
            printf("start T FUNC\n");
            // TSP_cmd(*head);
            print_graph(*head);
            continue;
        }
        break;
    }
    deleteGraph_cmd(head);

}
