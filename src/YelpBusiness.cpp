#include "YelpBusiness.h"
#include <iomanip>
#include <cmath>

// Prints information about the business.
void YelpBusiness::print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Address: " << address << ", " << city << ", " << state << " " << postalCode << std::endl;
    std::cout << "Stars: " << stars << std::endl;
    std::cout << "Reviews: " << reviewCount << std::endl;
    std::cout << "Weighted Rating: " << std::fixed << std::setprecision(2) << rating << std::endl;
    std::cout << "Distance: " << std::fixed << std::setprecision(2) << distance << std::endl;
    std::cout << "Hours: " << std::endl;

    std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (auto& day : days) {
        std::cout << "\t" << day << ": ";
        if (hours[day] != "")
            std::cout << hours[day] << std::endl;
        else
            std::cout << "Closed" << std::endl;
    }
}

void YelpBusiness::makeRating(double stars, int reviewCount) {
    double avgRating = 3.0;     // Yelp ratings range from 1.0 to 5.0; 3.0 is the middle value.
    int numReviewsNeeded = 7;   // 7 reviews are needed to be sure of a rating.
    
    // Bayesian average calculation
    this->rating = ((avgRating * numReviewsNeeded) + (stars * reviewCount)) / (numReviewsNeeded + reviewCount);
}

void YelpBusiness::calculateDistance(double lat, double lng) { //UF is at 29.64833 -82.34944 //replace this with the better calculation
    double locLat = this->latitude;
    double locLng = this->longitude;
    this->distance = std::sqrt(std::pow(lat - locLat, 2) + std::pow(lng - locLng, 2));
}
