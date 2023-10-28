//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_NODE_H
#define TEST2_NODE_H


#include "../Order/Order.h"

class Node {
public:
    Order* order;
    Node* next;

    explicit Node(Order* order) : order(order) {
        next = nullptr;
    }


};


#endif //TEST2_NODE_H
