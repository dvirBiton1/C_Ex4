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
//            if(scanf("%d",&src) != 0){
//                printf("scanf work\n");
//            }
//            printf("src :%d\n", src);
            insert_node_cmd(head);
            print_graph(*head);

        }
        if (choise == 'D') {
            // delete_node_cmd(head);
        }
        if (choise == 'S') {
            // shortsPath_cmd(*head);
        }
        if (choise == 'T') {
            // TSP_cmd(*head);
        }
        break;

    }

}
