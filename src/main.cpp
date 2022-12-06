#include "YelpDataset.h"
#include <iomanip>
#include <thread>

int menu();
int sortChoice();
bool sortOrder();

int main() {
    std::cout << "_______________________________" << std::endl;
    std::cout << "--------- YELP SORTER ---------" << std::endl;
    std::cout << "===============================" << std::endl;

    double latitude = 0.0;
    double longitude = 0.0;

    // Gets user coordinates
    while (true) {
        std::cout << "Enter your coordinates." << std::endl;
        std::cout << "Latitude: ";

        std::string temp = "";
        std::cin >> temp;
        try {
            latitude = stod(temp);
        }
        catch (...) {
            std::cout << "Invalid Input" << std::endl;
            continue;
        }

        std::cout << "Longitude: ";
        std::cin >> temp;

        try {
            longitude = stod(temp);
        }
        catch (...) {
            std::cout << "Invalid Input" << std::endl;
            continue;
        }

        break;
    }

    std::cout << "Loading data..." << std::endl;
    YelpDataset data(latitude, longitude);

    while (true) {
        int choice = menu();
        if (choice == 4) {
            break;
        }

        int sort = sortChoice();
        bool order = sortOrder();
        
        std::cout << "Sorting..." << std::endl;
        std::vector<YelpBusiness> sorted = data.sortTimer(sort, choice, order);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int i = 0;
        std::cin.ignore();
        std::string continueChoice;
        while (i < sorted.size() && continueChoice != "q") {
            int stop = i + 10;
            for (; i < sorted.size() && i < stop; i++) {
                std::cout << "RANK: " << i + 1 << std::endl;
                std::cout << "-------------------------------" << std::endl;
                sorted[i].print();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "-------------------------------" << std::endl;
            }
            std::cout << "Enter any key to continue, or type 'q' to quit: ";
            std::getline(std::cin, continueChoice);
        }
    }
}
    // Syntax for sortTimer:
    // First slot: 1 = mergesort, 2 = quicksort
    // Second slot: 1 = stars, 2 = ratings, 3 = distance
    // Third slot: "is descending": false = ordered logically, highest stars, rating, lowest distance | true = illogically, lowest stars and ratings, highest distance

// Gets user choice of attribute to sort by
int menu() {
    std::string choice = "";
    while (true) {
        std::cout << "_______________________________" << std::endl;
        std::cout << "============ MENU =============" << std::endl;
        std::cout << "1. Sort by stars" << std::endl;
        std::cout << "2. Sort by rating" << std::endl;
        std::cout << "3. Sort by distance" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "Choice: ";

        std::cin >> choice;

        if (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
            std::cout << "Invalid choice." << std::endl;
            continue;
        }
        break;
    }

    return std::stoi(choice);
}

// Returns user choice of either merge sort or quicksort
int sortChoice() {
    std::string choice = "";
    while (true) {
        std::cout << "===============================" << std::endl;
        std::cout << "Choose a sort: " << std::endl;
        std::cout << "1. Merge sort" << std::endl;
        std::cout << "2. Quicksort" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "Choice: ";
        
        std::cin >> choice;

        if (choice != "1" && choice != "2") {
            std::cout << "Invalid choice." << std::endl;
            continue;
        }
        break;
    }

    return std::stoi(choice);
}

// Returns user choice of descending or ascending sort order
bool sortOrder() {
    std::string choice = "";
    bool order;
    while (true) {
        std::cout << "===============================" << std::endl;
        std::cout << "Choose a sort order: " << std::endl;
        std::cout << "1. Descending" << std::endl;
        std::cout << "2. Ascending" << std::endl;
        std::cout << "===============================" << std::endl;
        std::cout << "Choice: ";
        
        std::cin >> choice;

        if (choice == "1") {
            order = false;
        }
        else if (choice == "2") {
            order = true;
        }
        else {
            std::cout << "Invalid choice." << std::endl;
            continue;
        }
        break;
    }

    return order;
}