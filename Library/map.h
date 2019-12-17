#ifndef MAP_H
#define MAP_H

typedef int Data_Key;
typedef int Data_Value;

struct Node;


Node* Node_create(Data_Key key, Data_Value value);

size_t height(Node* p);

const int bfactor(Node* p);

void fixheight(Node* p);

Node* rotateright(Node* p);

Node* rotateleft(Node* q);

Node* balance(Node* p);

Node* insert(Node* p, Data_Key k, Data_Value v);

Node* findmin(Node* p);

Node* removemin(Node* p);

Node* remove(Node* p, Data_Key k); 

bool inFrame(int num);

bool isBalanced(Node* p);

Data_Value find(Node* p, Data_Key key);

#endif