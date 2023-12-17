#include <string>
#include <list>
#include "../Order/Order.h"
#include "../Transaction/Transaction.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#ifndef TEST2_CSVManager_H
#define TEST2_CSVManager_H

class CSVManager {
 
    public:
        static std::list<Order> readOrders(const std::string& filename);
        static void writeTransactions(const std::string& filename, std::list<Transaction> transactions);
};

#endif //TEST2_CSVManager_H