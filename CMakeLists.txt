cmake_minimum_required(VERSION 3.26)
project(test2)

set(CMAKE_CXX_STANDARD 17)

add_executable(test2 main.cpp
        SortedLinkedList/SortedLinkedList.h
        SortedLinkedList/Node.h
        Order/Order.h
        OrderBook/OrderBook.h
        ExchangeApplication/ExchangeApplication.h
        CSVManager/CSVManager.h
        CSVManager/CSVManager.cpp
        )