#include "map.h"
#include <memory>


struct Node // структура для представления узлов дерева
{
	Data_Key key;
	Data_Value value;
	size_t height;
	Node* left;
	Node* right;
};

Node* Node_create(Data_Key key, Data_Value value)
{
	Node* node = new Node();
	node->key = key;
	node->value = value;
	node->left = node->right = 0;
	node->height = 1;
	return node;
}

size_t height(Node* p)
{
	return p ? p->height : 0;
}

const int bfactor(Node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(Node* p)
{
	size_t hl = height(p->left);
	size_t hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}


Node* rotateright(Node* p) // правый поворот вокруг p
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

Node* rotateleft(Node* q) // левый поворот вокруг q
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

Node* balance(Node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

Node* insert(Node* p, Data_Key k, Data_Value v) // вставка ключа k в дерево с корнем p
{
	if (!p) 
	{ 
		return Node_create(k, v); 
	}
	else if (p->key == k) {
		p->value = v;
		return p;
	}
	else if (k < p->key)
		p->left = insert(p->left, k, v);
	else
		p->right = insert(p->right, k, v);
	return balance(p);
}

Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

Node* removemin(Node* p) // удаление узла с минимальным ключом из дерева p
{
	if (!p->left)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

Node* remove(Node* p, Data_Key k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		Node* l = p->left;
		Node* r = p->right;
		delete p;
		if (!r) return l;
		Node* min = findmin(r);
		min->right = removemin(r);
		min->left = l;
		return balance(min);
	}
	return balance(p);
}

bool inFrame(int num) {
	return (num >= -1 && num <= 1);
}

bool isBalanced(Node* p)
{
		if (!p) return true;
		return isBalanced(p->left) && isBalanced(p->right) && inFrame(bfactor(p));
}

Data_Value find(Node* p, Data_Key key) 
{
	if (!p) {
		return Data_Value();
	}
	else if (p->key == key) {
		return p->value;
	}
	else if (key < p->key) {
		return find(p->left, key);
	}
	else {
		return find(p->right, key);
	}
}