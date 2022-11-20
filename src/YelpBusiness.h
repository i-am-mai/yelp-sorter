#include <string>
#include <vector>
#include <map>

struct YelpBusiness {
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

    void print();
};