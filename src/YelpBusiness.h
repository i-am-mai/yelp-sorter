#include <string>
#include <iostream>
#include <vector>
#include <map>

struct YelpBusiness {
    // Each property corresponds to the value with the same name in the yelp_academic_dataset_business json file.
    std::string businessID;
    std::string name;
    std::string address;
    std::string city;
    std::string state;
    std::string postalCode;
    double latitude;
    double longitude;
    double stars;
    int reviewCount;
    bool isOpen;
    std::map<std::string, std::string> attributes;
    std::vector<std::string> categories;
    std::map<std::string, std::string> hours;

    // Prints information about the business.
    void print() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Address: " << address << ", " << city << ", " << state << " " << postalCode << std::endl;
        std::cout << "Coordinates: " << latitude << ", " << longitude << std::endl;
        std::cout << "Stars: " << stars << std::endl;
        std::cout << "Reviews: " << reviewCount << std::endl;
    }
};