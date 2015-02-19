#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "packing.h"

//function to open a file
//FILE* OpenFile(char filename[], char mode[]){
    FILE * fptr = NULL;
    fptr = fopen(filename, mode);
    if(fptr == NULL){
        printf("Error opening file %s\n", filename);
        return NULL;
    }
    else{
        return fptr;
    }
}
//makes a node on the tree
tree* make_node(int number){
    tree* node = malloc(sizeof(tree));
    node->num = number;
    node->left = NULL;
    node->right = NULL;

    return(node);
}
//deletes the entire tree
void delete_tree(tree * node){
    if(node != NULL){
        delete_tree(node->left);
        delete_tree(node->right);
        free(node);
    }
}
//loads file and makes the tree
tree* LoadFile(char *Filename){
    //mess of variable declarations
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


    if((fptr = OpenFile(Filename, "r")) == NULL){
        return NULL;
    }

    //READING FILE

    //printf("----reading file----\n");

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
//builds the tree from the input file
tree* make_tree(tree * node, int a[][4], char cuts[], double w_h[][2], int size, int node_num){
    tree * temp = NULL;
    //node intialization
    node = make_node(a[node_num-1][0]);
    node->par_num = a[node_num-1][1];
    node->l_num = a[node_num-1][2];
    node->r_num = a[node_num-1][3];
    node->cut = cuts[node_num-1];
    node->width = w_h[node_num-1][0];
    node->height = w_h[node_num-1][1];
    if(node_num == size){
        node->x_c = 0.0;
        node->y_c = 0.0;
    }
    else{
        node->x_c = -1.0;
        node->y_c = -1.0;
    }

    temp = node;
    //printf("building for %d\n", node_num);
    int i;
    for(i = 0; i < 4; i++){
        //printf("%d ", a[node_num-1][i]);
    }

    if(a[node_num-1][2] != -1){
        //printf("make left %d\n", a[node_num-1][2]);
        //temp ->left = make_node(a[node_num-1][2]);
        temp -> left = make_tree(temp ->left, a, cuts, w_h, size, a[node_num-1][2]);
        temp->left->parent = temp;
    }
    if(a[node_num-1][3] != -1){
        //printf("make right %d\n", a[node_num-1][3]);
        //temp ->right = make_node(a[node_num-1][3]);
        temp -> right = make_tree(temp ->right, a, cuts, w_h, size, a[node_num-1][3]);
        temp->right->parent = temp;
    }

    return node;
}

//prints the tree inorder
void inorder(tree * ptr){
    if(ptr != NULL){
        inorder(ptr->left);
        printf("node: %d %d %d %d %c ", ptr->num, ptr->par_num, ptr->l_num, ptr->r_num, ptr->cut);
        printf("W/H: %.3f,%.3f ", ptr->width, ptr->height);
        printf("x/y: (%.3f, %.3f)\n", ptr->x_c, ptr->y_c);
        inorder(ptr->right);
    }
}

long get_leaf_num(char * Filename){
    FILE * fptr = NULL;
    long temp;
    if((fptr = OpenFile(Filename, "r")) == NULL){
        fclose(fptr);
        return 0;
    }
    while(fscanf(fptr, "%ld", &temp) == 1){
        fclose(fptr);
        return temp;
    }
    fclose(fptr);
    return 0;
}

void SaveFile(tree * ptr, char * Filename, long leaves){
    FILE * fptr = NULL;
    long i;
    int num;
    double width, height, x_coord, y_coord;

    if((fptr = OpenFile(Filename, "w")) == NULL){
        return;
    }
    fprintf(fptr, "%ld\n", leaves);
    for(i = 1; i < leaves+1; i++){
        num = i;
        search(ptr, &num, &width, &height, &x_coord, &y_coord);
        fprintf(fptr, "%d %e %e %e %e\n", num, width, height, x_coord, y_coord);
    }
    fclose(fptr);
}

void search(tree * ptr, int * num, double * width, double * height, double * x_coord, double * y_coord){
    if(ptr != NULL){
        search(ptr->left, num, width, height, x_coord, y_coord);
        if(ptr->num == *num){
            *width = ptr->width;
            *height = ptr->height;
            *x_coord = ptr->x_c;
            *y_coord = ptr->y_c;
        }
        search(ptr->right, num, width, height, x_coord, y_coord);
    }
}

void set_size(tree * ptr){
    if(ptr->left == NULL){
        return;
    }

    if(ptr->left->height == 0.0){
        //printf("go left\n");
        set_size(ptr->left);
    }
    if(ptr->right->height == 0.0){
        //printf("go right\n");
        set_size(ptr->right);
    }

    if(ptr->cut == 'H'){
        ptr->height = ptr->left->height + ptr->right->height;
        ptr->width = max_width(ptr);
    }
    else if(ptr->cut == 'V'){
        ptr->height = max_height(ptr);
        ptr->width = ptr->left->width + ptr->right->width;
    }
    return;
}

void set_coords(tree * ptr){
    if(ptr == NULL){
        return;
    }
    if(ptr->cut == 'H'){
        ptr->left->x_c = ptr->x_c;
        ptr->left->y_c = ptr->y_c + ptr->right->height;
        ptr->right->x_c = ptr->x_c;
        ptr->right->y_c = ptr->y_c;
    }
    else if(ptr->cut == 'V'){
        ptr->left->x_c = ptr->x_c;
        ptr->left->y_c = ptr->y_c;
        ptr->right->x_c = ptr->x_c + ptr->left->width;
        ptr->right->y_c = ptr->y_c;
    }
    set_coords(ptr->left);
    set_coords(ptr->right);
    return;
}

double max_height(tree * ptr){
    double temp1 = ptr->left->height;
    double temp2 = ptr->right->height;

    return temp1 >= temp2 ? temp1 : temp2;
}

double max_width(tree * ptr){
    double temp1 = ptr->left->width;
    double temp2 = ptr->right->width;

    return temp1 >= temp2 ? temp1 : temp2;
}

// main function
int main(int argc, char* argv[]){
    tree * head = NULL;
    long num_leaves;
    clock_t start, end;

    if(argc != 3){
        printf("Usage: proj3 <input_file> <output_file>\n");
        return 1;
    }
    head = LoadFile(argv[1]);
    start = clock();
    num_leaves = get_leaf_num(argv[1]);
    if(head == NULL){
        printf("Error saving tree\n");
    }
    //printf("set_size\n");
    set_size(head);
    set_coords(head);
    end = clock();
    //printf("----printing tree inorder----\n");
    //inorder(head);


    SaveFile(head, argv[2], num_leaves);

    double time_passed = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Width: %e\n", head->width);

    printf("Height: %e\n\n", head->height);

    int num = num_leaves;
    printf("num: %d\n", num_leaves);
    double width, height, x_coord, y_coord;
    search(head, &num, &width, &height, &x_coord, &y_coord);
    printf("X-coordinate: %e\n", x_coord);
    printf("Y-coordinate: %e\n\n", y_coord);
    printf("Elapsed Time: %e\n", time_passed);

    delete_tree(head);
    return 0;
}
