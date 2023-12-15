#include <string>
#include <list>
#include "../Order/Order.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#ifndef TEST2_CSVREADER_H
#define TEST2_CSVREADER_H

class CSVReader {
 
    public:
        std::list<Order> readOrders(std::string filename);

};

#endif //TEST2_CSVREADER_H