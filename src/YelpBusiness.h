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
    double rating;  // Our own rating of the Yelp business based on the Bayesian average. 
    int reviewCount;
    bool isOpen;
    std::unordered_map<std::string, std::string> attributes;
    std::vector<std::string> categories;
    std::unordered_map<std::string, std::string> hours;

    void print();
    void makeRating(double stars, int reviewCount);
};