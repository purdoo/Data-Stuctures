#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "packing.h"

tree* LoadFile(char *Filename)
{
    tree * head = NULL;
    FILE * fptr = NULL; //file pointer
    char * line = NULL; //line read from file
    char * temp_str = NULL; //tokenized string
    size_t len = 0; //length used for getline()
    ssize_t read; //used for getline()
    int line_count = 1; //keeps track of line count
    int num_nodes = 0; //number of nodes in tree
    char ** str_nodes = NULL; //an array of strings to store lines
    char * cuts = NULL; //cuts for each node
    int node_count = 0;
    int i, j;

    FILE * fptr = NULL;
    fptr = fopen(Filename, "r");
    if(fptr == NULL)
    {
        return NULL;
    }
    //READING FILE

    while((read = getline(&line, &len, fptr)) != -1){
        //printf("line %d: %s", line_count, line);
        if(line_count == 2){
            //printf("number of nodes is: %d\n", atoi(line));
            num_nodes = atoi(line);

            //allocate memory to store node numbers and names
            str_nodes = malloc(num_nodes * sizeof(char*));

            //allocate memory to store the cut type
            cuts = malloc(num_nodes * sizeof(char));
            for(i = 0; i < num_nodes; i++){
                str_nodes[i] = malloc(100 * sizeof(char));
            }
        }
        if(line_count > 2){
            //printf("line %d size(%d): %s", line_count, strlen(line), line);
            strcpy(str_nodes[node_count], line);
            node_count += 1;
        }
        line_count += 1;
    }


    int temp = 0;
    int node_arr[num_nodes][4]; //array to hold node number, parent and children
    double w_h_arr[num_nodes][2]; //array to hold width and height
    i = 0;
    j = 0;

    //TOKENIZING STRING FROM FILE

    //printf("----tokenizing string----\n\n");
    while(i < num_nodes){
        temp_str = strtok(str_nodes[i], " ");
        while(temp_str != NULL){
            //saves node number, parent number and children numbers into 2d array
            if(j < 4){
                node_arr[temp][j] = atoi(temp_str);
            }
            //saves cut type into char array
            if(j == 4){
                cuts[temp] = temp_str[0];
            }
            //saving width and height
            if(j == 5){
                w_h_arr[temp][0] = atof(temp_str);
            }
            if(j == 6){
                w_h_arr[temp][1] = atof(temp_str);
            }
            j += 1;
            temp_str = strtok(NULL, " ");
        }
        i += 1;
        temp += 1;
        j = 0;
    }

    //BUILDING TREE

    //printf("----building tree----\n");
    head = make_tree(head, node_arr, cuts, w_h_arr, num_nodes, num_nodes);
    //printf("\n");
    //inorder(head);


    if(line){
        free(line);
    }
    for(i=0; i < node_count; i++){
        free(str_nodes[i]);
    }
    free(str_nodes);
    free(cuts);
    fclose(fptr);

    return head;
}

int main(int argc, char* argv[])
{
	

}
