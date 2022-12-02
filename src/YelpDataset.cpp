#include "YelpDataset.h"
#include <fstream>
#include <sstream>
#include <string>
#include "../lib/json.hpp"

using json = nlohmann::json;

YelpDataset::YelpDataset() {
    loadData(data);
}


/* Takes in a reference to a YelpBusiness vector and loads it with
 * data from the yelp_academic_dataset_business.json file
 */
void YelpDataset::loadData(std::vector<YelpBusiness>& data) {
    std::ifstream file("assets/yelp_academic_dataset_business.json");
    std::string temp;
    while (getline(file, temp)) {
        json j = json::parse(temp);

        YelpBusiness business;

        // Add data about the business to the YelpBusiness object.
        business.businessID = j["business_id"];
        business.name = j["name"];
        business.address = j["address"];
        business.city = j["city"];
        business.state = j["state"];
        business.postalCode = j["postal_code"];
        business.latitude = j["latitude"];
        business.longitude = j["longitude"];
        business.stars = j["stars"];
        business.reviewCount = j["review_count"];
        business.isOpen = j["is_open"] == 1 ? true : false;
        business.makeRating(business.stars, business.reviewCount);

        for (json::iterator it = j["attributes"].begin(); it != j["attributes"].end(); it++) {
            business.attributes[(std::string) it.key()] = (std::string) it.value();
        }

        // Try-catch block is necessary in case the business has no categories.
        try {
            std::istringstream temp((std::string) j["categories"]);
            std::string category;
            while (getline(temp, category, ',')) {
                if (category[0] == ' ') {
                    category = category.substr(1);
                }
                business.categories.push_back(category);
            }
        }
        catch (...) {
        }
        for (json::iterator it = j["hours"].begin(); it != j["hours"].end(); it++) {
            business.hours[(std::string) it.key()] = (std::string) it.value();
        }
        business.print();
        data.push_back(business);
    }
}