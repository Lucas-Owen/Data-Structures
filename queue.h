#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.h"

template<class Type>
class Queue{ //uses linked list implementation
    Node<Type> *head, *tail;
    int size;

public:
    Queue();
    bool push(Type);
    bool empty();
    Type top();
    bool pop();
    int len();
    
    friend std::ostream& operator<<(std::ostream& out, const Queue<Type>& q){
        Node<Type>* curr = q.head;
        out << "(head) -> ";
        while(curr != nullptr){
            out << curr->data << " -> ";
            curr = curr->next;
        }
        out << " (tail)\n";

        return out;
    }

};

template<class Type>
Queue<Type>::Queue() : head(nullptr),
    tail(nullptr),
    size(0)
    {}

template<class Type>
bool Queue<Type>::push(Type data){
    if(this->tail == nullptr){
        this->tail = new Node<Type>(data);
        this->head = this->tail;
    }
    else{
        Node<Type> *temp = new Node<Type>(data);
        this->tail->next = temp;
        this->tail = temp;
    }
    this->size++;
    return true;
}

template<class Type>
bool Queue<Type>::pop(){
    if(head != nullptr){
        Node<Type> *temp = this->head;

        this->head = this->head->next;
        if(temp == this->tail) this->tail = nullptr;
        delete temp;
        this->size--;

        return true;
    }
    return false;
}

template<class Type>
Type Queue<Type>::top(){
    if(this->head != nullptr) return this->head->data;
    return nullptr;
}

template<class Type>
int Queue<Type>::len(){
    return size;
}

template<class Type>
bool Queue<Type>::empty(){
    return this->size;
}

#endif