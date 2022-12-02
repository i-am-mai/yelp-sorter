#include "YelpBusiness.h"

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