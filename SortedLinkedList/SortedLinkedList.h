//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_SORTEDLINKEDLIST_H
#define TEST2_SORTEDLINKEDLIST_H


#include <string>
#include <iostream>
#include "Node.h"

class SortedLinkedList {
private:
    Node* head;
public:
    explicit SortedLinkedList() {
        head= nullptr;
    }

    void insert(Order* newOrder) {
        Node* newNode = new Node(newOrder);
        Node* prev = nullptr;
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current != nullptr && Order::getMinOrder(*newOrder, *(current->order)).getOrderID()!=(*newOrder).getOrderID() ) {
                prev=current;
                current = current->next;
            }
            newNode->next = current;
            if(prev!= nullptr)
                prev->next = newNode;
            else
                head = newNode;

        }
    }

    void remove(Order* removeOrder) {
        Node* current = head;
        Node* prev = nullptr;
        while(current!= nullptr && current->order!=removeOrder){
            prev = current;
            current = current->next;
        }
        if(current!= nullptr){
            if(prev== nullptr){
                head = current->next;
            }else{
                prev->next = current -> next;
            }
            delete current;
        }
    }

    void print(){
        std::cout<< "-----------------------------------------" << std::endl;
        Node* current = head;
        while(current!= nullptr){
            (*current->order).print();
            current = current->next;
        }
        std::cout<< "-----------------------------------------" << std::endl;
    }

    [[nodiscard]] Node *getHead() const {
        return head;
    }
};


#endif //TEST2_SORTEDLINKEDLIST_H
