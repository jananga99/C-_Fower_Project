//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_ORDERBOOK_H
#define TEST2_ORDERBOOK_H


#include <iostream>
#include "../Order/Order.h"
#include "../SortedLinkedList/SortedLinkedList.h"

class OrderBook {
private:
    SortedLinkedList sellOrders;
    SortedLinkedList buyOrders;
    int numSellOrders;
    int numBuyOrders;
    std::string instrument;

public:
    explicit OrderBook(std::string instrument) : instrument(std::move(instrument)) {
        sellOrders = SortedLinkedList();
        buyOrders = SortedLinkedList();
        numSellOrders = 0;
        numBuyOrders = 0;
    }

    // only if return True, insert new node to order book
    static bool removeFillOrders(SortedLinkedList* orders, int* numOrders, Order* newOrder) {
        for (int i = 0; i < *numOrders; i++) {
            Order *currentOrder = orders->getHead()->order;
            if (newOrder->getPrice() == currentOrder->getPrice()) {
                if (newOrder->getQuantity() > currentOrder->getQuantity()) {
                    newOrder->setQuantity(newOrder->getQuantity() - currentOrder->getQuantity());
                    orders->remove(currentOrder);
                    (*numOrders)--;
                } else if (newOrder->getQuantity() < orders->getHead()->order->getQuantity()) {
                    currentOrder->setQuantity(currentOrder->getQuantity() - newOrder->getQuantity());
                    return false;
                } else {
                    orders->remove(currentOrder);
                    (*numOrders)--;
                    return false;
                }
            }
        }
        return true;
    }

    void addOrder(Order* newOrder){
        SortedLinkedList* currentOrders  = nullptr;
        SortedLinkedList* opposedOrders  = nullptr;
        int* currentCount = nullptr;
        int* opposedCount = nullptr;
        if(newOrder->getSide()==1){
            currentOrders = &buyOrders;
            opposedOrders = &sellOrders;
            currentCount = &numBuyOrders;
            opposedCount = &numSellOrders;
        }else{
            currentOrders = &sellOrders;
            opposedOrders = &buyOrders;
            currentCount = &numSellOrders;
            opposedCount = &numBuyOrders;
        }

        if(removeFillOrders(opposedOrders, opposedCount, newOrder)){
            currentOrders->insert(newOrder);
            (*currentCount)++;
        }
    }

    [[nodiscard]] SortedLinkedList getSellOrders() const {
        return sellOrders;
    }

    [[nodiscard]] SortedLinkedList getBuyOrders() const {
        return buyOrders;
    }

    [[nodiscard]] int getNumSellOrders() const {
        return numSellOrders;
    }

    [[nodiscard]] int getNumBuyOrders() const {
        return numBuyOrders;
    }

    [[nodiscard]] std::string getInstrument() const {
        return instrument;
    }

    void print() {
        std::cout << "=====================================" <<  std::endl;
        std::cout << "Order book for " << instrument << std::endl;
        std::cout << "Buy orders:" << std::endl;
        buyOrders.print();
        std::cout << "Sell orders:" << std::endl;
        sellOrders.print();
        std::cout << "=====================================" <<  std::endl;
    }
};


#endif //TEST2_ORDERBOOK_H
