Bst.h
```cpp
#pragma once
#include <bits/stdc++.h>

struct Node {
	int key;
	int value;
	Node* left;
	Node* right;
};

class BST {
private:
	Node* root = nullptr;
public:
	void Insert(int key, int value);
	int Lookup(int key);
	void Remove(int key);
	void InOrderTraversal();
	void Helper(Node* node);
};
```

Bst.cpp
```cpp
#include "Bst.h"

void BST::Insert(int key, int value)
{
	Node* NewNode = new Node{key,value,nullptr,nullptr};
	if(root==nullptr)
	{
		root=NewNode;
		return;
	}

	Node* cur = root;
	Node* par = nullptr;

	while(cur not_eq nullptr)
	{
		par=cur;
		if(key < cur->key)
		{
			cur = cur->left;
		}
		else if(key>cur->key)
		{
			cur = cur->right;
		}
		else
		{
			cur->value = value;
			delete NewNode;
			return;
		}
	}

	if(key < par->key)
	{
		par->left = NewNode;
	}
	else
	{
		par->right = NewNode;
	}
}

int BST::Lookup(int key)
{
	Node* cur = root;
    while (cur != nullptr) 
	{
        if (key < cur->key) 
		{
            cur = cur->left;
        } else if (key > cur->key) 
		{
            cur = cur->right;
        } else 
		{
            return cur->value;
        }
    }
    return -1;
}

void BST::Remove(int key)
{
	Node* par = nullptr;
    Node* cur = root;

    while (cur != nullptr and cur->key != key) 
	{
        par = cur;
        if (key < cur->key) 
		{
            cur = cur->left;
        } else 
		{
            cur = cur->right;
        }
    }

    if (cur == nullptr) 
		return;


    if (cur->left == nullptr and cur->right == nullptr) 
	{
        if (cur not_eq root) 
		{
            if (par->left == cur) 
			{
				par->left = nullptr;
			}
            else 
			{
				par->right = nullptr;
			}
        } 
		else 
		{
            root = nullptr;
        }
        delete cur;
    }

    else if (cur->left == nullptr or cur->right == nullptr) 
	{
        Node* child = (cur->left) ? cur->left : cur->right;

        if (cur not_eq root) 
		{
            if (par->left == cur) 
			{
				par->left = child;
			}
            else 
			{
				par->right = child;
			}
        } 
		else 
		{
            root = child;
        }
        delete cur;
    }

    else 
	{
        Node* sucPar = cur;
        Node* suc = cur->right;
        while (suc->left not_eq nullptr) {
            sucPar = suc;
            suc = suc->left;
        }
        cur->key = suc->key;
        cur->value = suc->value;
        
        if (sucPar->left == suc) sucPar->left = suc->right;
        else sucPar->right = suc->right;
        
        delete suc;
    }
}

void BST::InOrderTraversal()
{
	Helper(root);
	std::cout<<std::endl;
}

void BST::Helper(Node* node)
{
    if (node == nullptr) 
		return;

    Helper(node->left);
	std::cout << node->key << ' '<< node->value<< ' ';
    Helper(node->right);
}
```

Main.cpp
```cpp
#include <bits/stdc++.h>
#include "Bst.h"

int main() {
	BST bst;
	bst.Insert(5, 2);
	bst.Insert(6, 3);
	bst.Insert(4, 2);
	bst.Insert(1, 3);
	bst.Insert(4, 7);

	bst.InOrderTraversal();
	
	bst.Remove(4);
	std::cout << "키값 4인 노드 제거함\n";
	if (bst.Lookup(4) == 0)
	{
		std::cout << "키값이 4인 노드가 없음\n";
	}
	else
	{
		std::cout << "키값이 4인 노드가 있음\n";
	}

	std::cout << '\n';
	bst.InOrderTraversal();
	return 0;
}
```
