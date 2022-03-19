#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include "queue.h"

template<class Type>
class BinaryTree{
public:
    BinaryTree();
    virtual ~BinaryTree();

private:
    class BSTNode{
        public:
        Type data;
        BSTNode *left_child, *right_child;
        BSTNode(){
            left_child = nullptr;
            right_child = nullptr;
        }
        BSTNode(Type data){
            this->data = data;
            left_child = nullptr;
            right_child = nullptr;
        }
    };

    BSTNode* insertRecursively(Type data, BSTNode* parent);
    void inorder(BSTNode *parent);
    void bft(BSTNode *parent);
    bool search(Type data, BSTNode *parent);
    bool remove(Type data, BSTNode *parent);
    BSTNode* maximum(BSTNode *parent);
    BSTNode* minimum(BSTNode *parent);
    int height(BSTNode *parent);
    void clear(BSTNode *parent);


public:
    bool insertIteratively(Type data);
    bool insertRecursively(Type data);
    void inorder();
    void bft();
    bool search(Type data);
    bool remove(Type data);
    BSTNode* maximum();
    BSTNode* minimum();
    int height();
    void clear();

private:
    BSTNode* root;
};

template<class Type>
BinaryTree<Type>::BinaryTree() : root(nullptr) {}

template<class Type>
BinaryTree<Type>::~BinaryTree(){
    clear(this->root);
}

template<class Type>
bool BinaryTree<Type>::insertIteratively(Type data){
    BSTNode *temp = new BSTNode(data);
    if(this->root == nullptr){
        this->root = temp;
        return true;
    }
    BSTNode *parent = this->root;
    while(true){
        while(temp->data <= parent->data){
            if(parent->left_child == nullptr){
                parent->left_child = temp;
                return true;
            }
            parent = parent->left_child;
        }
        while(temp->data > parent->data){
            if(parent->right_child == nullptr){
                parent->right_child = temp;
                return true;
            }
            parent = parent->right_child;
        }
    }
}

template<class Type>
bool BinaryTree<Type>::insertRecursively(Type data){
    return insertRecursively(data, this->root) != nullptr;
}

template<class Type>
typename BinaryTree<Type>::BSTNode* BinaryTree<Type>::insertRecursively(Type data, BSTNode* parent){
    if(parent == nullptr){
        return new BSTNode(data);
    }

    if(data < parent->data) return (parent->left_child = insertRecursively(data, parent->left_child));
    if(data > parent->data) return (parent->right_child = insertRecursively(data, parent->right_child));
    
    return nullptr;
}

template<class Type>
void BinaryTree<Type>::inorder(){
    inorder(this->root);
}

template<class Type>
void BinaryTree<Type>::inorder(BSTNode *parent){
    //Depth first traversal <left><root><right>
    if(parent == nullptr) return;
    inorder(parent->left_child);
    std::cout<<parent->data<<" ";
    inorder(parent->right_child);
}

template<class Type>
void BinaryTree<Type>::bft(){
    bft(this->root);
}

template<class Type>
void BinaryTree<Type>::bft(BSTNode *parent){
    //Breadth first traversal
    Queue<BinaryTree<Type>::BSTNode*> queue;
    if(parent != nullptr) 
        do{
            std::cout<<parent->data<<" ";

            if(parent->left_child != nullptr)
                queue.push(parent->left_child);
            if(parent->right_child != nullptr)
                queue.push(parent->right_child);

            parent = queue.top();

        }while(queue.pop());
}

template<class Type>
bool BinaryTree<Type>::search(Type data){
    return search(data, this->root);
}

template<class Type>
bool BinaryTree<Type>::search(Type data, BSTNode* parent){
    if(parent != nullptr){
        if(data == parent->data) return true;
        if(data < parent->data) return search(data, parent->left_child);
        else return search(data, parent->right_child);
    }
    return false;
}

template<class Type>
bool BinaryTree<Type>::remove(Type data){
    return remove(data, this->root);
}

template<class Type>
bool BinaryTree<Type>::remove(Type data, BSTNode* parent){
    if(search(data)){
        BSTNode *prev = nullptr;
        while(true){    
            if(data < parent->data){
                prev = parent;
                parent = parent->left_child;
            }
            else if(data > parent->data){
                prev = parent;
                parent = parent->right_child;
            }
            else break;
        }
        
        if(parent == root){
            root = nullptr;
            delete parent;
            return true;
        }

        BSTNode *temp = parent;
        if(parent->right_child != nullptr){
            prev = parent;
            parent = parent->right_child;
            while(parent->left_child != nullptr){
                prev = parent;
                parent = parent->left_child;
            }
        }
        if(parent->data < prev->data){
            prev->left_child = parent->right_child;
        }
        else{
            prev->right_child = parent->right_child;
        }
        temp->data = parent->data;
        delete parent;

        return true;
    }

    return false;
}

template<class Type>
typename BinaryTree<Type>::BSTNode* BinaryTree<Type>::maximum(){
    return maximum(this->root);
}

template<class Type>
typename BinaryTree<Type>::BSTNode* BinaryTree<Type>::maximum(BSTNode *parent){
    if(parent == nullptr) return nullptr;
    while(parent->right_child != nullptr){
        parent = parent->right_child;
    }
    return parent;
}

template<class Type>
typename BinaryTree<Type>::BSTNode* BinaryTree<Type>::minimum(){
    return minimum(this->root);
}

template<class Type>
typename BinaryTree<Type>::BSTNode* BinaryTree<Type>::minimum(BSTNode *parent){
    if(parent == nullptr) return nullptr;
    while(parent->left_child != nullptr){
        parent = parent->left_child;
    }
    return parent;
}

template<class Type>
int BinaryTree<Type>::height(BSTNode *parent){
    if(parent == nullptr) return -1;
    int a = height(parent->left_child);
    int b = height(parent->right_child);
    return (a > b ? a : b) + 1;
}

template<class Type>
void BinaryTree<Type>::clear(){
    clear(this->root);
}

template<class Type>
void BinaryTree<Type>::clear(BSTNode* parent){
    if(parent == nullptr) return;

    clear(parent->left_child);
    clear(parent->right_child);

    delete parent;
}

#endif