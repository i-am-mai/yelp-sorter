#include "YelpBusiness.h"
#include <iomanip>
#include <cmath>

// Prints information about the business.
void YelpBusiness::print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Address: " << (address != "" ? address + ", " : "") << city << ", " << state << " " << postalCode << std::endl;
    std::cout << "Stars: " << stars << std::endl;
    std::cout << "Reviews: " << reviewCount << std::endl;
    std::cout << "Weighted Rating: " << std::fixed << std::setprecision(2) << rating << std::endl;
    std::cout << "Distance: " << std::fixed << std::setprecision(2) << distance << " miles" << std::endl;
    std::cout << "Hours: " << std::endl;

    std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (auto& day : days) {
        std::cout << "\t" << day << ": ";
        if (hours[day] != "")
            std::cout << hours[day] << std::endl;
        else
            std::cout << "No hours" << std::endl;
    }
}

// Creates a Bayesian average rating
void YelpBusiness::makeRating(double stars, int reviewCount) {
    double avgRating = 3.0;     // Yelp ratings range from 1.0 to 5.0; 3.0 is the middle value.
    int numReviewsNeeded = 7;   // 7 reviews are needed to be sure of a rating.
    
    // Bayesian average calculation
    this->rating = ((avgRating * numReviewsNeeded) + (stars * reviewCount)) / (numReviewsNeeded + reviewCount);
}

// Calculates distance of business from the user
void YelpBusiness::calculateDistance(double lat, double lng) {

    // Calculation of distance adapted from: https://www.themathdoctors.org/distances-on-earth-1-the-cosine-formula/
    double R = 3963.1;     // Earth's radius in 3963 miles.
    double pi = 3.14159265358979323846;
    double lat1 = lat * pi / 180;
    double lat2 = latitude * pi / 180;
    double lng1 = lng * pi / 180;
    double lng2 = longitude * pi / 180;

    this->distance = R * acos(sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(lng1 - lng2));
}
