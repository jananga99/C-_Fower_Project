//
// Created by jananga on 10/28/23.
//

#ifndef TEST2_ORDERBOOK_H
#define TEST2_ORDERBOOK_H


#include <iostream>
#include "../Order/Order.h"
#include "../SortedLinkedList/SortedLinkedList.h"
#include <list>
#include "../Transaction/Transaction.h"
#include "../CSVManager/CSVManager.h"

class OrderBook {
private:
    SortedLinkedList sellOrders;
    SortedLinkedList buyOrders;
    int numSellOrders;
    int numBuyOrders;
    std::string instrument;
    static inline std::list<Transaction> transactions;

    void addTransaction(Order* order, int quantity, int status){
        Transaction transaction(order->getClientOrderID(),
                                order->getOrderID(),
                                order->getInstrument(),
                                order->getSide(), 
                                order->getPrice(), 
                                quantity,
                                status,
                                order->getRejectedReason());
        transactions.push_back(transaction);
    }

public:
    explicit OrderBook(std::string instrument) : instrument(std::move(instrument)) {
        sellOrders = SortedLinkedList();
        buyOrders = SortedLinkedList();
        numSellOrders = 0;
        numBuyOrders = 0;
    }

    OrderBook() = default;

    // only if return True, insert new node to order book
    // return 0 if new order is not filled
    // return 1 if new order is filled
    // return 2 if new order is not touched
    int processFillOrders(SortedLinkedList* orders, int* numOrders, Order* newOrder) {
        bool notTouched = true;
        while ( *numOrders > 0) {
            Order *currentOrder = orders->getHead()->order;
            if (newOrder->getQuantity() > currentOrder->getQuantity()) {
                newOrder->setQuantity(newOrder->getQuantity() - currentOrder->getQuantity());
                orders->remove(currentOrder);
                (*numOrders)--;
                addTransaction(newOrder, currentOrder->getQuantity(), Status::Pfill);
                addTransaction(currentOrder, currentOrder->getQuantity(), Status::Fill);
                notTouched=false;
            } else if (newOrder->getQuantity() < currentOrder->getQuantity()) {
                currentOrder->setQuantity(currentOrder->getQuantity() - newOrder->getQuantity());
                addTransaction(newOrder, newOrder->getQuantity(), Status::Fill);
                addTransaction(currentOrder, newOrder->getQuantity(), Status::Pfill);
                return 0;
            } else {
                orders->remove(currentOrder);
                (*numOrders)--;
                addTransaction(newOrder, newOrder->getQuantity(), Status::Fill);
                addTransaction(currentOrder, currentOrder->getQuantity(), Status::Fill);
                return 0;
            }
        }
        return notTouched ? 2 : 1;
    }

    void addOrder(Order* newOrder){
        SortedLinkedList* currentOrders  = nullptr;
        int* currentCount = nullptr;
        if(newOrder->getSide()==1){
            currentOrders = &buyOrders;
            currentCount = &numBuyOrders;
        }else{
            currentOrders = &sellOrders;
            currentCount = &numSellOrders;
        }

        if(newOrder->getValidity()){
            int temp = processFillOrders(currentOrders, currentCount, newOrder);
            if(temp==1 || temp==2){
                currentOrders->insert(newOrder);
                (*currentCount)++;
                if(temp==2)
                    addTransaction(newOrder, newOrder->getQuantity(), Status::New);
            }
        
        }else{
                addTransaction(newOrder, newOrder->getQuantity(), Status::Rejected);
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

    void printTransactions(){
        std::cout << "=====================================" <<  std::endl
                    << "Transactions for " << instrument << std::endl;
                    
        for(auto & i : transactions){
            i.print();
        }
        std::cout << "=====================================" <<  std::endl;
    }

    static std::list<Transaction> getTransactions(){
        return transactions;
    }

    static void clearTransactions(){
        transactions.clear();
    }
};


#endif //TEST2_ORDERBOOK_H
