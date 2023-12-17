#include "CSVManager.h"


std::list<Order> CSVManager::readOrders(std::string filename){

    std::list<Order> orders;
    
    std::ifstream file(filename);

    // Checking the availability of the file.
    if(!file.is_open()){
        std::cout << "CSV File not found" << std::endl;
        return orders;
    }

    std::string line;
    bool isHeader = true;
    while (std::getline(file, line)) {
        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        Order order(row[0], row[1], std::stoi(row[2]), std::stoi(row[3]), std::stod(row[4]));
        order.print();
        if (order.getValidity()){
            orders.push_back(order);
        }
        
    }

    file.close();
    return orders;
};

void CSVManager::writeTransactions(std::string filename, std::list<Transaction> transactions){
    std::ofstream file(filename);

    // Checking the availability of the file.
    if(!file.is_open()){
        std::cout << "CSV File not found" << std::endl;
        return;
    }

    file << "ClientOrderID,OrderID,Instrument,Side,Price,Quantity,Status,RejectedReason,Timestamp" << std::endl;
    for(auto & i : transactions){
        file << i.getClientOrderID() << "," << i.getOrderID() << "," << i.getInstrument() << "," << i.getSide() << "," 
            << i.getPrice() << "," << i.getQuantity() << "," << i.getStatus() << "," << i.getRejectedReason() << "," 
            << i.getTimestamp() << std::endl;
    }

    file.close();
    return;
};