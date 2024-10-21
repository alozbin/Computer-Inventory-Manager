#include <iostream>
#include "Computer.hpp"

int main()
{
    char code;
    ComputerList computerList;

    computerList.displayCodes(); // user can continuously perform operations on list until cleared.

    while (true)
    {
        std::cout << "\n\nEnter operation code (or enter z for all valid codes): ";
        std::cin >> code;
        std::cout << "\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (code)
        {
        case 'a':
            computerList.addEnd();
            break;
        case 'b':
            computerList.addStart();
            break;
        case 'c':
            computerList.addAtPosition();
            break;
        case 'd':
            computerList.deleteNode();
            break;
        case 'p':
            computerList.printList();
            std::cout << "Number of computers in list: " << computerList.getSize() << "\n";
            std::cout << "TOTAL PRICE OF ALL COMPUTERS: $" << computerList.getTotalPrice() << "\n";
            break;
        case 't':
            std::cout << "Total price of all computers: $" << computerList.getTotalPrice() << "\n";
            break;
        case 'n':
            std::cout << "Number of computers in list: " << computerList.getSize();
            break;
        case 's':
            computerList.searchList();
            break;
        case 'f':
            computerList.exportToFile();
            break;
        case 'q':
            char c;
            std::cout << "Confirm clear list and exit program? (y/n): ";
            std::cin >> c;
            if (c == 'y')
            {
                computerList.clearList();
                std::cout << "List cleared and program ended.\n";
                return 0;
            }
            break;
        case 'z':
            computerList.displayCodes();
            break;
        default:
            std::cout << "Illegal code.\n";
        }
    }
}
