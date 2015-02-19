#ifndef REROOT_H
#define REROOT_H

typedef struct tree
{
    int num;
    char cut;
    double width;
    double height;
    //double totalHeight = 0;
    //double totalWidth = 0;
    double xCoordinate; 
    double yCoordinate; 
    struct tree *leftChild;
    struct tree *rightChild;
    struct tree *parentNode;
}tree;

typedef struct stack
{
    tree *node;
    tree *next;
}stack;

//void Push(stack currNode);
//stack Pop(stack *st);
void Push(tree * stack, tree * currNode);
tree * Pop (tree * stack[]);

tree* LoadFile(char* filename);
void MeasureCuts(tree * temp);
void GetCoordinates(tree * temp);
void FindDimensions(tree * temp, double *maxWidth, double *maxHeight);
tree* SampleTree(); 
void PrintPreorder(tree *head);
void PrintInorder(tree *head);
void PrintPostorder(tree *head);

#endif // reroot.h
