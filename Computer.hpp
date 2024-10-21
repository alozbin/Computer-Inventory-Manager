#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class ComputerList
{
private:
    struct Computer
    {
        std::string name;
        std::string motherboard;
        double motherboardPrice;
        std::string cpu;
        double cpuPrice;
        std::string cpuCooler;
        double cpuCoolerPrice;
        std::string memory;
        double memoryPrice;
        std::string storage;
        double storagePrice;
        std::string gpu;
        double gpuPrice;
        std::string pcCase;
        double pcCasePrice;
        std::string psu;
        double psuPrice;
        std::string os;
        double osPrice;
        double computerPrice;
        Computer* next;
    };

    Computer* head;
    int size;
    double totalPrice;

    Computer* createNewComputer();
    double getValidPrice(const std::string& component);
    void printComputerDetails(Computer* curr) const;

public:
    ComputerList();
    ~ComputerList();

    void addEnd();
    void addStart();
    void addAtPosition();
    void deleteNode();
    void clearList();

    void printList() const;
    void searchList() const;
    void exportToFile() const;
    
    void displayCodes() const;
    double getTotalPrice() const;
    int getSize() const;
};

#endif // COMPUTER_H