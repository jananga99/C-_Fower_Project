#include <string>
#include <list>
#include "../Order/Order.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#ifndef TEST2_CSVManager_H
#define TEST2_CSVManager_H

class CSVManager {
 
    public:
        std::list<Order> readOrders(std::string filename);

};

#endif //TEST2_CSVManager_H