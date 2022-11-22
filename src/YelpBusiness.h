#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

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
    std::unordered_map<std::string, std::string> hours;

    void print();
};

// Prints information about the business.
void YelpBusiness::print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Address: " << address << ", " << city << ", " << state << " " << postalCode << std::endl;
    std::cout << "Stars: " << stars << std::endl;
    std::cout << "Reviews: " << reviewCount << std::endl;
    std::cout << "Hours: " << std::endl;

    std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (auto& day : days) {
        std::cout << "\t" << day << ": " << hours[day] << std::endl;
    }
}