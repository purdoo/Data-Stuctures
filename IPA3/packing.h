#ifndef PACKING_H
#define PACKING_H

typedef struct tree{
    int num;
    int par_num;
    int l_num;
    int r_num;
    char cut;
    double width;
    double height;
    double x_c; //x coordinate
    double y_c; //y coordinate
    struct tree *left;
    struct tree *right;
    struct tree *parent;
}tree;

struct Depth{
    tree * tree;
    int level;
};

FILE* OpenFile(char filename[], char mode[]);
tree* make_node(int num);
tree* LoadFile(char *Filename);
tree* make_tree(tree * node, int a[][4], char cuts[], double w_h[][2], int size, int node_num);
void inorder(tree * ptr);
long get_leaf_num(char * Filename);
void SaveFile(tree * ptr, char * Filename, long leaves);
void search(tree * ptr, int * num, double * width, double * height, double * x_coord, double * y_coord);
double max_height(tree * ptr);
double max_width(tree * ptr);
void set_size(tree * ptr);
void set_coords(tree * ptr);
#endif // packing.h
