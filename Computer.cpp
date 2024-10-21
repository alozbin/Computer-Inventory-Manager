#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Computer.hpp"

ComputerList::ComputerList() : head(nullptr), size(0), totalPrice(0.0) {}

ComputerList::~ComputerList()
{
    clearList();
}

// function only used internally to gather computer information
ComputerList::Computer* ComputerList::createNewComputer()
{
    Computer* newComputer = new Computer;
    if (newComputer == nullptr)
    {
        std::cout << "ERROR: Memory allocation failed.\n";
        return nullptr;
    }

    std::cout << "Enter the name for this computer: ";
    std::getline(std::cin, newComputer->name);

    std::cout << "Enter motherboard model: ";
    std::getline(std::cin, newComputer->motherboard);
    newComputer->motherboardPrice = getValidPrice("motherboard");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter CPU model: ";
    std::getline(std::cin, newComputer->cpu);
    newComputer->cpuPrice = getValidPrice("CPU");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter CPU cooler model: ";
    std::getline(std::cin, newComputer->cpuCooler);
    newComputer->cpuCoolerPrice = getValidPrice("CPU cooler");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter memory model: ";
    std::getline(std::cin, newComputer->memory);
    newComputer->memoryPrice = getValidPrice("memory");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter storage model: ";
    std::getline(std::cin, newComputer->storage);
    newComputer->storagePrice = getValidPrice("storage");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter graphics card model: ";
    std::getline(std::cin, newComputer->gpu);
    newComputer->gpuPrice = getValidPrice("graphics card");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter computer case model: ";
    std::getline(std::cin, newComputer->pcCase);
    newComputer->pcCasePrice = getValidPrice("computer case");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter power supply model: ";
    std::getline(std::cin, newComputer->psu);
    newComputer->psuPrice = getValidPrice("power supply");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter operating system: ";
    std::getline(std::cin, newComputer->os);
    newComputer->osPrice = getValidPrice("operating system");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    newComputer->computerPrice = newComputer->motherboardPrice + newComputer->cpuPrice + newComputer->cpuCoolerPrice +
                                 newComputer->memoryPrice + newComputer->storagePrice + newComputer->gpuPrice +
                                 newComputer->pcCasePrice + newComputer->psuPrice + newComputer->osPrice;

    return newComputer;
}

// function ensures price of component is valid
double ComputerList::getValidPrice(const std::string& component)
{
    double price;
    while (true)
    {
        std::cout << "Enter " << component << " price: $";
        std::cin >> price;
        if (std::cin.fail() || price < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
        }
        else
        {
            return price;
        }
    }
}

// function prints computer details
void ComputerList::printComputerDetails(Computer* curr) const
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "COMPUTER NAME: " << curr->name << "\nMotherboard: " << curr->motherboard << "\n\tPrice: $" << curr->motherboardPrice <<
        "\nCPU: " << curr->cpu << "\n\tPrice: $" << curr->cpuPrice << "\nCPU cooler: " << curr->cpuCooler << "\n\tPrice: $" << curr->cpuCoolerPrice <<
        "\nMemory: " << curr->memory << "\n\tPrice: $" << curr->memoryPrice << "\nStorage: " << curr->storage << "\n\tPrice: $" << curr->storagePrice <<
        "\nVideo Card: " << curr->gpu << "\n\tPrice: $" << curr->gpuPrice << "\nCase: " << curr->pcCase << "\n\tPrice: $" << curr->pcCasePrice <<
        "\nPower Supply: " << curr->psu << "\n\tPrice: $" << curr->psuPrice << "\nOperating System: " << curr->os << "\n\tPrice: $" << curr->osPrice <<
        "\nTotal Price: $" << curr->computerPrice << "\n\n";
}


// function adds computer to end of list
void ComputerList::addEnd()
{
    Computer* newComputer = createNewComputer();
    newComputer->next = nullptr;

    if (head == nullptr) // new node becomes head node if list is empty
    {
        head = newComputer;
    }
    else // otherwise new node inserted at end of list
    {
        Computer* curr = head;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = newComputer;
    }
    totalPrice += newComputer->computerPrice;
    size++;
}

// function adds computer to start of list
void ComputerList::addStart()
{
    Computer* newComputer = createNewComputer();
    newComputer->next = head;

    head = newComputer;
    totalPrice += newComputer->computerPrice;
    size++;
}

// function adds computer to specific spot in list
void ComputerList::addAtPosition()
{
    Computer* newComputer = createNewComputer();

    int position;
    std::cout << "\nEnter integer corresponding to desired placement of computer in list: ";
    std::cin >> position;

    if (position < 1 || position > size + 1)
    {
        std::cout << "ERROR: Invalid position.\n";
        delete newComputer;
        return;
    }

    // replaces head node with new node if position is 1
    if (position == 1)
    {
        newComputer->next = head;
        head = newComputer;
    }
    else // otherwise finds position and inserts new node
    {
        Computer* curr = head;
        int i = 1;
        while (i < position - 1 && curr != nullptr)
        {
            curr = curr->next;
            ++i;
        }
        if (curr == nullptr) // error if position not within list
        {
            std::cout << "ERROR: Invalid position.\n";
            delete newComputer;
            return;
        }
        newComputer->next = curr->next;
        curr->next = newComputer;
    }
    totalPrice += newComputer->computerPrice;
    size++;
}

// function deletes computer from list by name
void ComputerList::deleteNode()
{
    if (head == nullptr)
    {
        std::cout << "List is already empty.\n";
        return;
    }

    std::string deleteName;
    std::cout << "Enter name of computer to be deleted: ";
    std::getline(std::cin, deleteName);

    // delete head node if names match
    if (head->name == deleteName)
    {
        Computer* temp = head;
        head = head->next;

        totalPrice -= temp->computerPrice;
        size--;

        delete temp;

        std::cout << deleteName << " has been deleted.\n";
        return;
    }

    Computer* curr = head;
    // pointer moves down list until names match or reaches end
    while (curr->next != nullptr && curr->next->name != deleteName)
    {
        curr = curr->next;
    }

    if (curr->next == nullptr)
    {
        std::cout << "ERROR: Computer not found.\n";
        return;
    }

    Computer* temp = curr->next;
    curr->next = temp->next;

    totalPrice -= temp->computerPrice;
    size--;

    delete temp;
    std::cout << deleteName << " has been deleted.\n";
}

// function prints list to output
void ComputerList::printList() const
{
    Computer* curr = head;

    if (curr == nullptr)
    {
        std::cout << "List is empty.\n";
    }

    while (curr != nullptr) // outputs content of each node until pointer reaches end of list
    {
        printComputerDetails(curr);
        curr = curr->next;
    }
}

// function searches list for computer by name
void ComputerList::searchList() const
{
    if (head == nullptr)
    {
        std::cout << "List is empty.\n";
        return;
    }

    std::string searchName;
    std::cout << "Enter name of computer to search: ";
    std::getline(std::cin, searchName);
    std::cout << "\n\n";

    Computer* curr = head;
    while (curr != nullptr)
    {
        if (curr->name == searchName)
        {
            printComputerDetails(curr);
            return;
        }
        curr = curr->next;
    }

    // error message if pointer reaches end of list
    std::cout << "Computer not found.\n";
}

// function writes contents of list to file
void ComputerList::exportToFile() const
{
    std::string filename;
    std::cout << "Enter name of file to write to (include file extension): ";
    std::getline(std::cin, filename);

    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        std::cout << "Error opening file.\n";
        return;
    }

    outputFile << std::fixed << std::setprecision(2);

    Computer* curr = head;
    while (curr != nullptr) // outputs contents of each node to file until pointer reaches end of list
    {
        outputFile << "COMPUTER NAME: " << curr->name << "\nMotherboard: " << curr->motherboard << "\n\tPrice: $" << curr->motherboardPrice <<
                      "\nCPU: " << curr->cpu << "\n\tPrice: $" << curr->cpuPrice << "\nCPU cooler: " << curr->cpuCooler << "\n\tPrice: $" << curr->cpuCoolerPrice <<
                      "\nMemory: " << curr->memory << "\n\tPrice: $" << curr->memoryPrice << "\nStorage: " << curr->storage << "\n\tPrice: $" << curr->storagePrice <<
                      "\nVideo Card: " << curr->gpu << "\n\tPrice: $" << curr->gpuPrice << "\nCase: " << curr->pcCase << "\n\tPrice: $" << curr->pcCasePrice <<
                      "\nPower Supply: " << curr->psu << "\n\tPrice: $" << curr->psuPrice << "\nOperating System: " << curr->os << "\n\tPrice: $" << curr->osPrice <<
                      "\nTotal Price: $" << curr->computerPrice << "\n\n";

        curr = curr->next;
    }
    outputFile << "Number of computers in list: " << size << "\n";
    outputFile << "TOTAL PRICE OF ALL COMPUTERS: $" << totalPrice;

    outputFile.close();
    std::cout << "List exported to " << filename << ".\n";
}

// function clears list and deallocates memory
void ComputerList::clearList()
{
    while (head != nullptr)
    {
        Computer* temp = head;
        head = head->next;
        delete temp;
    }
}

// function displays all valid operation codes
void ComputerList::displayCodes() const
{
    std::cout << "Operation Codes:\n---------------------------------------------\n a: Add computer to end of list.\n"
                 " b: Add computer to start of list.\n c: Add computer to specific spot in list.\n"
                 " d: Delete computer from list.\n p: Print list.\n t: Display total price of entire list.\n"
                 " n: Display total number of computers in list.\n s: Search list.\n f: Export list to file.\n q: Clear list and exit program.\n"
                 " z: Display all valid operation codes again.\n---------------------------------------------";
}

double ComputerList::getTotalPrice() const
{
    return totalPrice;
}

// function returns size of list
int ComputerList::getSize() const
{
    return size;
}